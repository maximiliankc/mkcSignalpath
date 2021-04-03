#ifndef SOUND_UNIT_HPP
#define SOUND_UNIT_HPP

#include "CircularBuffer.hpp"

//each sound unit "owns" its output (i.e. is responsible for freeing etc.)

// this is a mono unit, will make a 'mult channel' unit eventually
class SoundUnit{
    protected:
    CircularBuffer * x;
    CircularBuffer * y;

    public:
    SoundUnit(CircularBuffer * in, int inLength, int outLength);
    ~SoundUnit();
    virtual void step(void) = 0;
    CircularBuffer * get_x(void);
    CircularBuffer * get_y(void);
};

#endif