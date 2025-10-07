#include <cstdio>

int main() {
    int nx = 7;
    int w = 2;
    int m = nx / w;
    int r = nx % w;
    int start = 0;
    int finish = m;
    int result;
    if (w*m+r == nx) {
        printf("it worked\n");
        printf("m=%d, r=%d", m, r);
    } else {
        printf("wrong\n");
    }
    return 0;
}
