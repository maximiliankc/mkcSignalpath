#ifndef SOUND_UNIT_HPP
#define SOUND_UNIT_HPP

#include "CircularBuffer.hpp"

//each sound unit "owns" its input

class SoundUnit{
    protected:
    CircularBuffer * x;
    int xChannels;
    CircularBuffer * y;
    int yChannels;

    public:
    SoundUnit(CircularBuffer * in, int inChannels, int inLength, int outChannels, int outLength);
    ~SoundUnit();
    virtual void step(void) = 0;
    CircularBuffer * get_x(void);
    CircularBuffer * get_y(void);
    int get_x_channels(void);
    int get_y_channels(void);
};

#endif