#include "SoundPath.hpp"
    
SoundPath::SoundPath() {
    // initialise sound units
    // set up delay
    int i;
    for(i = 0; i < DELAY_CHANNELS; i++) {
        delayIn[i].init(DELAY_SAMPLES+1, delayInMemory[i]);
        delayOut[i].init(1, delayOutMemory[i]);
    }
    delay.init(DELAY_SAMPLES, DELAY_CHANNELS, delayIn, delayOut);
    // set delay to be the first (and for now only) unit to be used
    Units[0] = &delay;
}

// this is where the sequence is set

void SoundPath::step(void) {

    // feed the inputs into the first unit
    
    int i;
    for(i = 0; i < IN_CHANNELS; i++) {
        Units[0]->get_x()[i].next(x[i]);
    }

    // run all the sound path elements
    for(i = 0; i < SOUND_UNITS; i++) {
        Units[i]->step();

    }
    // fill the output buffer with the outputs of the final effect
    for(i = 0; i < OUT_CHANNELS; i++) {
        y[i] = Units[SOUND_UNITS-1]->get_y()[i].now(0);
    }
}

float * SoundPath::getX(void) {
    return x;
}

float * SoundPath::getY(void) {
    return y;
}
