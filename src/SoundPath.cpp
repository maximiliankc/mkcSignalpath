
#include "SoundPath.hpp"

void soundpath_init(SoundPath * self) {
    // initialise sound units
    int i;

    // set up filter
    // memory
    for(i = 0; i < DELAY_CHANNELS; i++) {
        circular_buffer_init(&(self->filterIn[i]), FILTER_LENGTH, self->filterInMemory[i]);
        circular_buffer_init(&(self->filterOut[i]), FILTER_LENGTH, self->filterOutMemory[i]);
    }
    // set coefficients
    self->a[0] = 1;
    self->a[1] = -0.5;
    self->a[2] = 0;
    self->b[0] = 0.5;
    self->b[1] = 0;
    self->b[2] = 0;
    filter_init(&(self->filter), DELAY_CHANNELS, self->filterIn, self->filterOut, FILTER_LENGTH, self->a, FILTER_LENGTH, self->b);

    // set up delay
    for(i = 0; i < DELAY_CHANNELS; i++) {
        circular_buffer_init(&(self->delayIn[i]), DELAY_SAMPLES+1, self->delayInMemory[i]);
    }
    delay_init(&(self->delay), DELAY_SAMPLES, DELAY_CHANNELS, self->delayIn, self->filterIn);
    // set delay to be the first (and for now only) unit to be used
}

// this is where the sequence is set

void soundpath_step(SoundPath * self) {

    // feed the inputs into the first unit
    int i;
    for(i = 0; i < IN_CHANNELS; i++) {
        circular_buffer_next(&(self->delay.x[i]), self->x[i]);
    }

    // run all the sound path elements
    delay_step(&(self->delay));
    filter_step(&(self->filter));

    // fill the output buffer with the outputs of the final block
    for(i = 0; i < OUT_CHANNELS; i++) {
        self->y[i] = circular_buffer_now(&(self->filter.y[i]), 0);
    }
}

