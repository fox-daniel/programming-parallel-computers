/*
This is the function you need to implement. Quick reference:
- input rows: 0 <= y < ny
- input columns: 0 <= x < nx
- element at row y and column x is stored in data[x + y*nx]
- correlation between rows i and row j has to be stored in result[i + j*ny]
- only parts with 0 <= j <= i < ny need to be filled
*/

#define ILP 6

#include <cmath>
void correlate(int ny, int nx, const float *data, float *result) {
  // normalization
  int nx_p = ceil((double)nx / ILP) * ILP;
  double *norm = new double[nx_p * ny]{};

  for (int y = 0; y < ny; y++) {
    double sum = 0;
    for (int x = 0; x < nx; x++)
      sum += data[x + y * nx];

    double mean = sum / (double)nx;
    double sum_of_squares = 0;
    for (int x = 0; x < nx; x++) {
      double demeaned = data[x + y * nx] - mean;
      norm[x + y * nx_p] = demeaned;
      sum_of_squares += demeaned * demeaned;
    }

    double root_sos = std::sqrt(sum_of_squares);
    for (int x = 0; x < nx; x++)
      norm[x + y * nx_p] = norm[x + y * nx_p] / root_sos;
  }

  // correlation
  for (int yi = 0; yi < ny; yi++) {
    for (int yj = 0; yj <= yi; yj++) {
      double sum[ILP] = {};

      for (int x = 0; x < nx_p; x += ILP) {
        for (int k = 0; k < ILP; k++) {
          sum[k] += norm[x + k + yi * nx_p] * norm[x + k + yj * nx_p];
        }
      }

      double total = 0;
      for (int k = 0; k < ILP; k++)
        total += sum[k];

      result[yi + yj * ny] = total;
    }
  }

  delete[] norm;
}
