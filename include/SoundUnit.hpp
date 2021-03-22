#ifndef SOUND_UNIT_HPP
#define SOUND_UNIT_HPP

#include "CircularBuffer.hpp"

//each sound unit "owns" its input

class SoundUnit{
    protected:
    CircularBuffer * x;
    CircularBuffer * y;
    public:
    SoundUnit(CircularBuffer _x, CircularBuffer _y);
    virtual void step(void) = 0;
};

#endif