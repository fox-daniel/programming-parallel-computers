
void normalize_row(int a, int nx, const float *data, double *row) {
    double sum = 0;
    for (int k=0; k<nx; k++) {
        sum += data[k + a*nx];
    }
    for (int k=0; k<nx; k++) {
        row[k] = data[k+ a*nx] - sum;
    }
}


float correlate_rows(int a, int b, int nx, const float *data) {
    double correlation = 0;
    double row1[nx];
    double row2[nx];
    normalize_row(a, nx, data, row1);
    normalize_row(b, nx, data, row2);

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
