#ifndef DELAY_HPP
#define DELAY_HPP

#include "CircularBuffer.hpp"

struct SimpleDelay {
    int n;
    CircularBuffer * x;
    CircularBuffer * y;
    unsigned int xChannels;
    unsigned int yChannels;

};

void delay_init(SimpleDelay * self, int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out);
void delay_step(SimpleDelay * self);
#endif
