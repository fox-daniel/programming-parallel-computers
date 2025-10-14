#include <vector>
#include <cmath>
#include <chrono>
/*
 * Prior to optimization the benchmarks were:
 * benchmarks/1.txt                  0.308s  pass
 * benchmarks/2.txt                  4.893s  pass
 *
 * With unwinding factor of 8, the benchmarks are:
 *
 * benchmarks/1.txt                  0.061s  pass
 * benchmarks/2.txt                  0.968s  pass
 *
 * The increase of unwinding from 4 to 8 has a
 * bigger impact on my Mac than the Linux machines used in the online grader.
 *
 *
 * Modifications:
 * - pass the correlation vector to correlate_rows instead of initializing in each loop: no significant difference
 * - use double *normalized[] instead of std::vector: small improvement in speed
 * - using for loop with update of i += unwind like Joseph does actually made it slower: 4:00 -> 4:20
 */

void normalize_rows(int a, int nx, const float *data, double *normalized) {
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


float correlate_rows(int a, int b, int nx, double *normalized) {
    double total_correlation = 0;
    const int unwind = 8;
    std::vector<double> correlation(unwind+1);
    // unwinding factor of 8 is slightly better than 4 in the online eval (4'13" vs 4'24")
    int nxw = floor(nx / unwind);
    // initialize the chunks of the correlation
    for (int j=0; j<unwind; j++) {
        correlation[j] = 0;
    }

    // calculate chunks of correlation
    for (int i=0; i<nxw; i++) {
        for (int j=0; j<unwind; j++) {
            correlation[j] += normalized[i*unwind + j + nx*a]*normalized[i*unwind + j + nx*b];
        }
    }
    // calculate remaining chunk of correlation
    int start = unwind*nxw;
    int finish = nx;
    for (int i=start; i<finish; i++) {
        correlation[unwind] += normalized[i+nx*a]*normalized[i+nx*b];
    }
    // combine chunks
    for (int j=0; j<=unwind; j++) {
        total_correlation += correlation[j];
    }
    return (float)total_correlation;
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
    // std::vector<double> normalized(ny*nx);
    double *normalized = new double[ny*nx]{};
    for (int i=0; i<ny; i++) {
        normalize_rows(i, nx, data, normalized);
    }
    // complexity: ny*nx
    for (int i=0; i<ny; i++) {
        for (int j=0; j<=i; j++) {
            result[i+j*ny] = correlate_rows(i, j, nx, normalized);
        }
    }
    delete[] normalized;
}
