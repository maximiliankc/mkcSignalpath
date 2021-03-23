#include <iostream>
#include "CircularBuffer.hpp"

int test_circ_buf(void);

int main(int argc, char ** argv) {

    if(test_circ_buf()) {
        std::cout << "FAIL\n";
    } else {
        std::cout << "PASS\n";
    }
    return 0;
}

int test_circ_buf(void) {
    float testVector[32][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                               {1, 0, 0, 0, 1, 0, 0, 0},
                               {2, 1, 0, 0, 2, 1, 0, 0},
                               {3, 2, 1, 0, 3, 2, 1, 0},
                               {4, 3, 2, 1, 4, 3, 2, 1},
                               {5, 4, 3, 2, 5, 4, 3, 2},
                               {6, 5, 4, 3, 6, 5, 4, 3},
                               {7, 6, 5, 4, 7, 6, 5, 4},
                               {8, 7, 6, 5, 8, 7, 6, 5},
                               {9, 8, 7, 6, 9, 8, 7, 6},
                               {10, 9, 8, 7, 10, 9, 8, 7},
                               {11, 10, 9, 8, 11, 10, 9, 8},
                               {12, 11, 10, 9, 12, 11, 10, 9},
                               {13, 12, 11, 10, 13, 12, 11, 10},
                               {14, 13, 12, 11, 14, 13, 12, 11},
                               {15, 14, 13, 12, 15, 14, 13, 12},
                               {16, 15, 14, 13, 12, 0, 0, 0},
                               {17, 16, 15, 14, 13, 12, 0, 0},
                               {18, 17, 16, 15, 14, 13, 12, 0},
                               {19, 18, 17, 16, 15, 14, 13, 12},
                               {20, 19, 18, 17, 16, 15, 14, 13},
                               {21, 20, 19, 18, 17, 16, 15, 14},
                               {22, 21, 20, 19, 18, 17, 16, 15},
                               {23, 22, 21, 20, 19, 18, 17, 16},
                               {24, 23, 22, 21, 20, 19, 18, 17},
                               {25, 24, 23, 22, 21, 20, 19, 18},
                               {26, 25, 24, 23, 22, 21, 20, 19},
                               {27, 26, 25, 24, 23, 22, 21, 20},
                               {28, 27, 26, 25, 24, 23, 22, 21},
                               {29, 28, 27, 26, 25, 24, 23, 22},
                               {30, 29, 28, 27, 26, 25, 24, 23},
                               {31, 30, 29, 28, 27, 26, 25, 24}};
    int retval = 0;
    CircularBuffer buffer(4);
    int i;
    int n;

    for(i = 0; i < 16; i++) {
        buffer.next(i);
        for(int k = 0; k < 8; k++) {
            n = buffer.now(-k);
            if (n != testVector[i][k]) {
                retval = 1;
                std::cout << testVector << "|";
            }
            std::cout << n << " ";
        }
        std::cout << "\n";
    }
    buffer.extend(8);
    for(; i < 32; i++) {
        buffer.next(i);
        for(int k = 0; k < 8; k++) {
            n = buffer.now(-k);
            if (n != testVector[i][k]) {
                retval = 1;
                std::cout << testVector << "|";
            }
            std::cout << n << " ";
        }
        std::cout << "\n";
    }

    // check that the unitialised state works

    CircularBuffer x;

    x.next(0.1);
    if(x.now(-1) != 0) {
        retval = 0;
    }
    return retval;
}