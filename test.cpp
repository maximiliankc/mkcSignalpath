#include <iostream>
#include "CircularBuffer.hpp"
#include "Delay.hpp"

#define DELAY_TEST_LENGTH 50
#define TEST_DELAY 15

int test_circ_buf(void);
int test_delay(void);

int main(int argc, char ** argv) {

    std::cout << "CircularBuffer\n";
    if(test_circ_buf()) {
        std::cout << "FAIL\n";
    } else {
        std::cout << "PASS\n";
    }
/*
    std::cout << "SimpleDelay\n";
    if(test_delay()) {
        std::cout <<"FAIL\n";
    } else {
        std::cout<<"PASS\n";
    }
*/
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
                               {16, 0,  0,  0,  0,  0,  0, 0},
                               {17, 16, 0, 0, 0, 0, 0, 0},
                               {18, 17, 16, 0, 0, 0, 0, 0},
                               {19, 18, 17, 16, 0, 0, 0, 0},
                               {20, 19, 18, 17, 16, 0, 0, 0},
                               {21, 20, 19, 18, 17, 16, 0, 0},
                               {22, 21, 20, 19, 18, 17, 16, 0},
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
    float buf_mem[4];
    CircularBuffer buffer(4, buf_mem);
    int i;
    int n;

    for(i = 0; i < 16; i++) {
        buffer.next(i);
        for(int k = 0; k < 8; k++) {
            n = buffer.now(k);
            if (n != testVector[i][k]) {
                retval = 1;
            }
        }
    }

    float buf_mem2[8];
    CircularBuffer buffer2(8, buf_mem2);
    //
    for(i = 16; i < 32; i++) {
        buffer2.next(i);
        for(int k = 0; k < 8; k++) {
            n = buffer2.now(k);
            if (n != testVector[i][k]) {
                retval = 1;
            }
        }
    }

    return retval;
}
/*
int test_delay(void) {
    float testVector[DELAY_TEST_LENGTH + TEST_DELAY];
    float outVector[DELAY_TEST_LENGTH];
    int i;
    int delay = TEST_DELAY;
    int retval = 0;
    CircularBuffer in(1);
    SimpleDelay delayUnit(delay, &in);
    CircularBuffer * out = delayUnit.get_y();
    for(i = 0; i < TEST_DELAY; i++) {
        testVector[i] = 0;
    }
    for(i = 0; i < DELAY_TEST_LENGTH; i++) {
        testVector[i+TEST_DELAY] = i;
        in.next(i);
        delayUnit.step();
        outVector[i] = out->now(0);
    }
    for(i = 0; i < DELAY_TEST_LENGTH; i++) {
        retval += (testVector[i] == outVector[i]);
    }
    return 0;
}
*/