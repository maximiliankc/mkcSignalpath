#include <stdio.h>
#include "CircularBuffer.h"
#include "Delay.h"
#include "Filter.h"
#include "Oscillator.h"

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
int test_oscillator(void);

int main(int argc, char ** argv) {

    printf("CircularBuffer\n");
    if(test_circ_buf()) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    printf("SimpleDelay\n");
    if(test_delay()) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    printf("Filter\n");
    if(test_filter()) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    printf("Oscillator\n");
    if(test_oscillator()) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
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
    CircularBuffer buffer;
    int i;
    int n;
    
    circular_buffer_init(&buffer, 4, buf_mem);

    for(i = 0; i < 16; i++) {
        circular_buffer_next(&buffer, i);
        for(int k = 0; k < 8; k++) {
            n = circular_buffer_now(&buffer, k);
            if (n != testVector[i][k]) {
                retval = 1;
            }
        }
    }

    float buf_mem2[8];
    circular_buffer_init(&buffer, 8, buf_mem2);

    for(i = 16; i < 32; i++) {
        circular_buffer_next(&buffer, i);
        for(int k = 0; k < 8; k++) {
            n = circular_buffer_now(&buffer, k);
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
        circular_buffer_init(&inputs[i], DELAY_TEST_LENGTH, in_memory[i]);
        circular_buffer_init(&outputs[i], DELAY_TEST_LENGTH, out_memory[i]);
    }

    SimpleDelay delayUnit;
    delay_init(&delayUnit, TEST_DELAY, DELAY_CHANNELS, inputs, outputs);
    // pre-filling the test vector
    for(i = 0; i < TEST_DELAY; i++) {
        testVector[i] = 0;
    }

    // for each channel, get the delay value (different values for different channels)
    for(i = 0; i < DELAY_TEST_LENGTH; i++) {
        testVector[i+TEST_DELAY] = i;
        for(j = 0; j < DELAY_CHANNELS; j++) {
            circular_buffer_next(&inputs[j], i + j);
        }
        delay_step(&delayUnit);
        for(j = 0; j < DELAY_CHANNELS; j++) {
            outVector[j][i] = circular_buffer_now(&outputs[j], 0);
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
        circular_buffer_init(&in[i], FIR_LENGTH, inMemory[i]);
        circular_buffer_init(&out[i], IIR_LENGTH, outMemory[i]);
    }

    // configure as a fir filter
    Filter filter;
    filter_init(&filter, FILTER_CHANNELS, in, out, 1, fira, FIR_LENGTH, b);
    // test fir filter

    circular_buffer_next(&in[0], 1);
    circular_buffer_next(&in[1], 2);

    for(i = 0; i < FIR_LENGTH; i++) {
        filter_step(&filter);
        if (circular_buffer_now(&out[0], 0) != b[i]) {
            return 1;
        }
        if (circular_buffer_now(&out[1], 0) != 2*b[i]) {
            return 1;
        }
        circular_buffer_next(&in[0], 0);
        circular_buffer_next(&in[1], 0);
    }
    filter_step(&filter); // clearing the last value

    // configure as an iir filter
    filter.aLen = IIR_LENGTH;
    filter.a = a;
    filter.bLen = 1;
    filter.b = iirb;

    circular_buffer_next(&in[0], 1);
    circular_buffer_next(&in[1], 2);
    float check = 1;
    for(i = 0; i < IIR_TEST_LENGTH; i++) {
        filter_step(&filter);
        if (circular_buffer_now(&out[0], 0) != check) {
            return 1;
        }
        if (circular_buffer_now(&out[1], 0) != 2*check) {
            return 1;
        }
        check *= 0.5;
        circular_buffer_next(&in[0], 0);
        circular_buffer_next(&in[1], 0);
    }

    //test iir filter
    return 0;
}


int test_oscillator(void) {
    float inMemory[OSC_CHANNELS][1];
    CircularBuffer in[OSC_CHANNELS];
    float outMemory[OSC_CHANNELS][OSC_MEMORY];
    CircularBuffer out[OSC_CHANNELS];
    int i;

    for(i = 0; i < OSC_CHANNELS; i++) {
        circular_buffer_init(&in[i], 1, inMemory[i]);
        circular_buffer_init(&out[i], OSC_MEMORY, outMemory[i]);
    }
    Oscillator osc;
    osc_init(&osc, in, out, 0.5);

    circular_buffer_next(&in[0], 1);
    for(i = 0; i < 10; i++) {
        osc_step(&osc);
        circular_buffer_next(&in[0], 0);
        if (i%2) {
            // if odd, output should be 1
            if (circular_buffer_now(&out[0], 0) != -1) {
                return 1;
            }
        } else {
            // otherwise, output should be -1
            if (circular_buffer_now(&out[0], 0) != 1) {
                return 1;
            }
        }
        // // should be zero (or close to it) always
        if (circular_buffer_now(&out[1], 0)*circular_buffer_now(&out[1], 0) > 1e-8) {
            return 1;
        }
    }

    osc_stop(&osc);
    
    circular_buffer_next(&in[1], 1);
    for(i = 0; i < 10; i++) {
        osc_step(&osc);
        circular_buffer_next(&in[1], 0);
        if (i%2) {
            // if odd, output should be 1
            if (circular_buffer_now(&out[1], 0) != -1) {
                return 1;
            }
        } else {
            // otherwise, output should be -1
            if (circular_buffer_now(&out[1], 0) != 1) {
                return 1;
            }
        }
        // should be zero (or close to it) always
        if (circular_buffer_now(&out[0],0)*circular_buffer_now(&out[0], 0) > 1e-7) {
            return 1;
        }
    }

    return 0;
}