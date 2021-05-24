#ifndef DELAY_HPP
#define DELAY_HPP

#include "SoundUnit.hpp"

class SimpleDelay: public SoundUnit {
    int n;

    public:
    SimpleDelay();
    SimpleDelay(int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out);
    void init(int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out);
    void step(void);
};

#endif