#include <iostream>

struct Result {
    float avg[3];
};

/*
This is the function you need to implement. Quick reference:
- x coordinates: 0 <= x < nx
- y coordinates: 0 <= y < ny
- horizontal position: 0 <= x0 < x1 <= nx
- vertical position: 0 <= y0 < y1 <= ny
- color components: 0 <= c < 3
- input: data[c + 3 * x + 3 * nx * y]
- output: avg[c]
*/


Result calculate(int ny, int nx, const float *data, int y0, int x0, int y1, int x1) {
    Result result{{0.0f, 0.0f, 0.0f}};
    int width = x1 - x0;
    int height = y1 - y0;
    int num_vals = width * height;
    int red_sum = 0;
    int blue_sum = 0;
    int green_sum = 0;
    for (int x = x0; x < x1; ++x) {
        for (int y = y0; y< y1; ++y) {
            red_sum += data[0 + 3*x + 3*nx*y];
            blue_sum += data[1 + 3*x + 3*nx*y];
            green_sum += data[2 + 3*x + 3*nx*y];
        }
    }
    result.avg[0] = static_cast<float>(red_sum) / num_vals;
    result.avg[1] = static_cast<float>(blue_sum) / num_vals;
    result.avg[2] = static_cast<float>(green_sum) / num_vals;
    return result;
}

int main() {
    const int data{{1, 1, 1}};
    Result res = calculate(1, 1, data, 0, 0, 1, 1);

    return 0;
}
