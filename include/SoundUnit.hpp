#ifndef SOUND_UNIT_HPP
#define SOUND_UNIT_HPP

#include "CircularBuffer.hpp"

class SoundUnit{
    protected:
    CircularBuffer * x;
    CircularBuffer * y;
    unsigned int channels;

    public:
    SoundUnit(unsigned int c, CircularBuffer * in, CircularBuffer * out);
    virtual void step(void) = 0;
    unsigned int get_channels(void);
    CircularBuffer * get_x(void);
    CircularBuffer * get_y(void);
};

#endif