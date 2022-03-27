#ifndef SOUND_PATH_H
#define SOUND_PATH_H

#include "Delay.h"
#include "Filter.h"

#define IN_CHANNELS 2
#define OUT_CHANNELS 2

#define DELAY_SAMPLES 0
#define DELAY_CHANNELS 2

#define FILTER_CHANNELS 2
#define FILTER_LENGTH 3

#define SOUND_UNITS 2

typedef struct SoundPath {
    float x[IN_CHANNELS];
    float y[OUT_CHANNELS];

    // this is where the sound units and their memory is setup

    // delay
    // memory
    float delayInMemory[DELAY_CHANNELS][DELAY_SAMPLES+1];
    CircularBuffer delayIn[DELAY_CHANNELS];
    // delay out will use filter in
    // unit
    SimpleDelay delay;

    // filter
    // memory
    float filterInMemory[FILTER_CHANNELS][FILTER_LENGTH];
    CircularBuffer filterIn[FILTER_CHANNELS];
    float filterOutMemory[FILTER_CHANNELS][FILTER_LENGTH];
    CircularBuffer filterOut[FILTER_CHANNELS];
    // coefficients
    float a[FILTER_LENGTH];
    float b[FILTER_LENGTH];
    // unit
    Filter filter;
} SoundPath;

void soundpath_init(SoundPath * self);
void soundpath_step(SoundPath * self);


#endif