#include <vector>
#include <cmath>

typedef double double4_t __attribute__ ((vector_size (4 * sizeof(double))));

double4_t double_to_double4(double x1, double x2, double x3, double x4) {
    return (double4_t){(double)x1, (double)x2, (double)x3, (double)x4};
}

void pad(int ny, int nx, int nxp, std::vector<double>& normalized, std::vector<double>& pdata) {
    for (int i=0; i<ny; i+=1) {
        for (int j=0; j<nx; j += 1) {
            pdata[j + i*nxp] = normalized[j + i*nx];
        }
    }

}

void convert_dtype(int ny, int nx, int m, std::vector<double>& pdata, std::vector<double4_t>& vdata) {
    // pdata is required to represent an ny x nx matrix where nx (column length) is divisible by 4

    for (int i=0; i<ny; i+=1) {
        for (int j=0; j<nx; j += 4) {
            vdata[j/4 + m*i] = double_to_double4(
                pdata[j + nx*i],
                pdata[1 + j + nx*i],
                pdata[2 + j + nx*i],
                pdata[3 + j + nx*i]
            );
        }
    }
}


void normalize_rows(int a, int nx, const float *data, std::vector<double>& normalized) {
    double mean = 0;
    double len = 0;
    for (int k=0; k<nx; k++) {
        mean += data[k + a*nx];
    }
    mean = mean / nx;
    for (int k=0; k<nx; k++) {
        normalized[k+ a*nx] = data[k + a*nx] - mean;
   }
    for (int k=0; k<nx; k++) {
        len += normalized[k + a*nx]*normalized[k + a*nx];
    }
    len = sqrt(len);
    // std::cout << "stdev:" << std::endl;
    // std::cout << len << std::endl;
    for (int k=0; k<nx; k++) {
        normalized[k + a*nx] = normalized[k + a*nx]/len;
    }
}


float correlate_rows(int a, int b, int m, std::vector<double4_t>& vdata) {
    double4_t correlation = {0.0, 0.0, 0.0, 0.0};
    for (int i=0; i<m; i++) {
        correlation += vdata[i+m*a]*vdata[i+m*b];
    }
    return correlation[0]+correlation[1]+correlation[2]+correlation[3];
}

/*
This is the function you need to implement. Quick reference:
- input rows: 0 <= y < ny
- input columns: 0 <= x < nx
- element at row y and column x is stored in data[x + y*nx]
- correlation between rows i and row j has to be stored in result[i + j*ny]
- only parts with 0 <= j <= i < ny need to be filled
*/
void correlate(int ny, int nx, const float *data, float *result) {
    std::vector<double> normalized(ny * nx);
    for (int i=0; i<ny; i++) {
        normalize_rows(i, nx, data, normalized);
    }
    const int m = ceil(nx / 4.0);
    const int nxp = m * 4;
    std::vector<double> pdata(ny*nxp);
    pad(ny, nx, nxp, normalized, pdata);
    std::vector<double4_t> vdata(ny*m);
    convert_dtype(ny, nxp, m, pdata, vdata);
    for (int i=0; i<ny; i++) {
        for (int j=0; j<=i; j++) {
            result[i+j*ny] = correlate_rows(i, j, m, vdata);
        }
    }
}
