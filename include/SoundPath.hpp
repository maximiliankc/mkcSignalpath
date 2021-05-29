#ifndef SOUND_PATH_HPP
#define SOUND_PATH_HPP

#include "Delay.hpp"
#include "Filter.hpp"

#define IN_CHANNELS 2
#define OUT_CHANNELS 2

#define DELAY_SAMPLES 0
#define DELAY_CHANNELS 2

#define FILTER_CHANNELS 2
#define FILTER_LENGTH 3

#define SOUND_UNITS 2

class SoundPath {
    float x[IN_CHANNELS];
    float y[OUT_CHANNELS];
    SoundUnit * Units[SOUND_UNITS];

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
    DFIFilter filter;
    

    public:
    SoundPath();
    void step(void);
    float * getX(void);
    float * getY(void);

};

#endif