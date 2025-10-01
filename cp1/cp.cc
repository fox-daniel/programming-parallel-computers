#include <vector>
#include <cmath>


void normalize_row(int a, int nx, const float *data, std::vector<double>& row) {
    double mean = 0;
    double len = 0;
    for (int k=0; k<nx; k++) {
        mean += data[k + a*nx];
    }
    mean = mean / nx;
    for (int k=0; k<nx; k++) {
        row[k] = data[k+ a*nx] - mean;
   }
    for (int k=0; k<nx; k++) {
        len += row[k]*row[k];
    }
    len = sqrt(len);
    // std::cout << "stdev:" << std::endl;
    // std::cout << len << std::endl;
    for (int k=0; k<nx; k++) {
        row[k] = row[k]/len;
    }
}


float correlate_rows(int a, int b, int nx, const float *data) {
    double correlation = 0;
    std::vector<double> row1(nx);
    std::vector<double> row2(nx);
    normalize_row(a, nx, data, row1);
    normalize_row(b, nx, data, row2);
    // print_vector("row1", row1);
    // print_vector("row2", row2);
    for (int i=0; i<nx; i++) {
        correlation += row1[i]*row2[i];
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
    for (int i=0; i<ny; i++) {
        for (int j=0; j<=i; j++) {
            result[i+j*ny] = correlate_rows(i, j, nx, data);
        }
    }
}
