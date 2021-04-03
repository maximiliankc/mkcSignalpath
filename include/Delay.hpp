#ifndef DELAY_HPP
#define DELAY_HPP

#include "SoundUnit.hpp"

class SimpleDelay: public SoundUnit {
    int n;

    public:
    SimpleDelay(int _n, CircularBuffer * in);
    void step(void);
};

#endif