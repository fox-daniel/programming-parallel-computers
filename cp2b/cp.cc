#include <vector>
#include <cmath>
// #include </opt/homebrew/opt/libomp/include/omp.h>

void normalize_rows(int a, int nx, const float *data, std::vector<double>& normalized) {
    double mean = 0;
    double len = 0;
    asm("# begin mean");
    for (int k=0; k<nx; k++) {
        mean += data[k + a*nx];
    }
    mean = mean / nx;
    asm("# end mean");
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


float correlate_rows(int a, int b, int nx, std::vector<double>& normalized) {
    double correlation = 0;
    for (int i=0; i<nx; i++) {
        correlation += normalized[i+nx*a]*normalized[i+nx*b];
    }
    return correlation;
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
    std::vector<double> normalized(ny*nx);
    for (int i=0; i<ny; i++) {
        normalize_rows(i, nx, data, normalized);
    }
    #pragma omp parallel for schedule(static, 1)
    // schedule(static, 1) is likely important here because the inner for loop is
    // bounded by the outer for loop index, creating uneven work loads without
    // proper scheduling.
    for (int i=0; i<ny; i++) {
        for (int j=0; j<=i; j++) {
            result[i+j*ny] = correlate_rows(i, j, nx, normalized);
        }
    }
}
