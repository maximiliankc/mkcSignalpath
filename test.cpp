#include <iostream>
#include "CircularBuffer.hpp"
#include "Delay.hpp"
#include "Filter.hpp"

#define DELAY_TEST_LENGTH 15
#define TEST_DELAY 15
#define DELAY_CHANNELS 2

#define FIR_LENGTH 8
#define IIR_LENGTH 2
#define IIR_TEST_LENGTH 10
#define FILTER_CHANNELS 2

int test_circ_buf(void);
int test_delay(void);
int test_filter(void);

int main(int argc, char ** argv) {

    std::cout << "CircularBuffer\n";
    if(test_circ_buf()) {
        std::cout << "FAIL\n";
    } else {
        std::cout << "PASS\n";
    }

    std::cout << "SimpleDelay\n";
    if(test_delay()) {
        std::cout <<"FAIL\n";
    } else {
        std::cout<<"PASS\n";
    }

    std::cout << "Filter\n";
    if(test_filter()) {
        std::cout <<"FAIL\n";
    } else {
        std::cout<<"PASS\n";
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
    buffer.init(8, buf_mem2);
    //
    for(i = 16; i < 32; i++) {
        buffer.next(i);
        for(int k = 0; k < 8; k++) {
            n = buffer.now(k);
            if (n != testVector[i][k]) {
                retval = 1;
            }
        }
    }

    return retval;
}

int test_delay(void) {
    float testVector[DELAY_TEST_LENGTH + TEST_DELAY];
    float outVector[DELAY_CHANNELS][DELAY_TEST_LENGTH];
    int i;
    int j;
    int retval = 0;

    float in_memory[DELAY_CHANNELS][DELAY_TEST_LENGTH];
    float out_memory[DELAY_CHANNELS][1];
    CircularBuffer inputs[DELAY_CHANNELS];
    CircularBuffer outputs[DELAY_CHANNELS];

    for(i = 0; i < DELAY_CHANNELS; i++) {
        inputs[i].init(DELAY_TEST_LENGTH, in_memory[i]);
        outputs[i].init(DELAY_TEST_LENGTH, out_memory[i]);
    }

    SimpleDelay delayUnit(TEST_DELAY, DELAY_CHANNELS, inputs, outputs);
    // pre-filling the test vector
    for(i = 0; i < TEST_DELAY; i++) {
        testVector[i] = 0;
    }

    // for each channel, get the delay value (different values for different channels)
    for(i = 0; i < DELAY_TEST_LENGTH; i++) {
        testVector[i+TEST_DELAY] = i;
        for(j = 0; j < DELAY_CHANNELS; j++) {
            inputs[j].next(i+j);
        }
        delayUnit.step();
        for(j = 0; j < DELAY_CHANNELS; j++) {
            outVector[j][i] = outputs[j].now(0);
        }
    }
    // check the delays are correct
    for(i = 0; i < DELAY_TEST_LENGTH; i++) {
        for(j = 0; j < DELAY_CHANNELS; j++) {
            retval += (testVector[i] == (outVector[j][i] - j));
        }
    }
    return 0;
}

int test_filter(void) {
    int i;
    float b[FIR_LENGTH] = {1, 0.5, 0.4, 0.7, 0.2, -0.5, 0.9, 0.5};
    float a[IIR_LENGTH] = {1, -0.5};
    float iirb[] = {1};
    float fira[] = {1};

    float inMemory[FILTER_CHANNELS][FIR_LENGTH];
    float outMemory[FILTER_CHANNELS][IIR_LENGTH];
    CircularBuffer in[FILTER_CHANNELS];
    CircularBuffer out[FILTER_CHANNELS];

    for(i = 0; i < FILTER_CHANNELS; i++) {
        in[i].init(FIR_LENGTH, inMemory[i]);
        out[i].init(IIR_LENGTH, outMemory[i]);
    }


    // configure as a fir filter
    DFIFilter filter(FILTER_CHANNELS, in, out, 1, fira, FIR_LENGTH, b);
    // test fir filter

    in[0].next(1);
    in[1].next(2);

    for(i = 0; i < FIR_LENGTH; i++) {
        filter.step();
        if (out[0].now(0) != b[i]) {
            return 1;
        }
        if (out[1].now(0) != 2*b[i]) {
            return 1;
        }
        in[0].next(0);
        in[1].next(0);
    }
    filter.step(); // clearing the last value

    // configure as an iir filter
    filter.updateDenominator(IIR_LENGTH, a);
    filter.updateNumerator(1, iirb);

    in[0].next(1);
    in[1].next(2);
    float check = 1;
    for(i = 0; i < IIR_TEST_LENGTH; i++) {
        filter.step();
        if (out[0].now(0) != check) {
            return 1;
        }
        if (out[1].now(0) != 2*check) {
            return 1;
        }
        check *= 0.5;
        in[0].next(0);
        in[1].next(0);
    }

    //test iir filter
    return 0;
}