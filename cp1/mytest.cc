#include <iostream>
#include <iomanip>
#include <cmath>

// Compile: g++ -std=c++17 -o mytest mytest.cc cp.cc

// Your correlate function
void correlate(int ny, int nx, const float *data, float *result);

void print_matrix(const char* name, int rows, int cols, const float* data) {
    std::cout << name << " (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4)
                      << data[j + i * cols] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Test case 1: Simple 2x2 matrix
    std::cout << "=== Test 1: 2x2 matrix ===\n";
    {
        int ny = 2, nx = 2;
        float data[] = {
            1.0f, 1.0f,   // row 0
            -1.0f, 1.0f    // row 1
        };
        float result[4] = {0};  // ny * ny = 2 * 2 = 4

        print_matrix("Input", ny, nx, data);

        correlate(ny, nx, data, result);

        print_matrix("Result (correlation matrix)", ny, ny, result);
    }

    // Test case 2: Different 2x2 matrix
    // std::cout << "=== Test 2: 2x2 matrix (different) ===\n";
    // {
    //     int ny = 2, nx = 2;
    //     float data[] = {
    //         -1.0f, 1.0f,   // row 0
    //          1.0f, -1.0f   // row 1
    //     };
    //     float result[4] = {0};

    //     print_matrix("Input", ny, nx, data);

    //     correlate(ny, nx, data, result);

    //     print_matrix("Result (correlation matrix)", ny, ny, result);
    // }

    // // Test case 3: 3x2 matrix
    // std::cout << "=== Test 3: 3x2 matrix ===\n";
    // {
    //     int ny = 3, nx = 2;
    //     float data[] = {
    //         -1.0f, 1.0f,   // row 0
    //          1.0f, -1.0f,  // row 1
    //         -1.0f, 1.0f    // row 2
    //     };
    //     float result[9] = {0};  // ny * ny = 3 * 3 = 9

    //     print_matrix("Input", ny, nx, data);

    //     correlate(ny, nx, data, result);

    //     print_matrix("Result (correlation matrix)", ny, ny, result);
    // }

    return 0;
}
