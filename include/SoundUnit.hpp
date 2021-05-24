#ifndef SOUND_UNIT_HPP
#define SOUND_UNIT_HPP

#include "CircularBuffer.hpp"

class SoundUnit{
    protected:
    CircularBuffer * x;
    CircularBuffer * y;
    unsigned int xChannels;
    unsigned int yChannels;

    public:
    SoundUnit(unsigned int xc, unsigned int yc, CircularBuffer * in, CircularBuffer * out);
    virtual void step(void) = 0;
    unsigned int get_x_channels(void);
    unsigned int get_y_channels(void);
    CircularBuffer * get_x(void);
    CircularBuffer * get_y(void);
};

#endif