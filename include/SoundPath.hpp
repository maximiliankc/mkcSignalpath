#ifndef SOUND_PATH_HPP
#define SOUND_PATH_HPP

#include "Delay.hpp"

#define IN_CHANNELS 2
#define OUT_CHANNELS 2

#define DELAY_SAMPLES 200
#define DELAY_CHANNELS 2

#define SOUND_UNITS 1

class SoundPath {
    float x[IN_CHANNELS];
    float y[OUT_CHANNELS];
    SoundUnit * Units[SOUND_UNITS];

    // this is where the sound units and their memory is setup

    //delay
    float delayInMemory[DELAY_CHANNELS][DELAY_SAMPLES+1];
    CircularBuffer delayIn[DELAY_CHANNELS];
    float delayOutMemory[DELAY_CHANNELS][1];
    CircularBuffer delayOut[DELAY_CHANNELS];
    SimpleDelay delay;

    public:
    SoundPath();
    void step(void);
    float * getX(void);
    float * getY(void);

};

#endif