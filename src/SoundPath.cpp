#include "SoundPath.hpp"

SoundPath::SoundPath() {
    // initialise sound units
    int i;

    // set up filter
    // memory
    for(i = 0; i < DELAY_CHANNELS; i++) {
        circular_buffer_init(&filterIn[i], FILTER_LENGTH, filterInMemory[i]);
        circular_buffer_init(&filterOut[i], FILTER_LENGTH, filterOutMemory[i]);
    }
    // set coefficients
    a[0] = 1;
    a[1] = -0.5;
    a[2] = 0;
    b[0] = 0.5;
    b[1] = 0;
    b[2] = 0;
    filter_init(&filter, DELAY_CHANNELS, filterIn, filterOut, FILTER_LENGTH, a, FILTER_LENGTH, b);

    // set up delay
    for(i = 0; i < DELAY_CHANNELS; i++) {
        circular_buffer_init(&delayIn[i], DELAY_SAMPLES+1, delayInMemory[i]);
    }
    delay_init(&delay, DELAY_SAMPLES, DELAY_CHANNELS, delayIn, filterIn);
    // set delay to be the first (and for now only) unit to be used
}

// this is where the sequence is set

void SoundPath::step(void) {

    // feed the inputs into the first unit
    int i;
    for(i = 0; i < IN_CHANNELS; i++) {
        circular_buffer_next(&(delay.x[i]), x[i]);
    }

    // run all the sound path elements
    delay_step(&delay);
    filter_step(&filter);

    // fill the output buffer with the outputs of the final block
    for(i = 0; i < OUT_CHANNELS; i++) {
        y[i] = circular_buffer_now(&(filter.y[i]), 0);
    }
}

float * SoundPath::getX(void) {
    return x;
}

float * SoundPath::getY(void) {
    return y;
}
