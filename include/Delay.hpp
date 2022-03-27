#ifndef DELAY_HPP
#define DELAY_HPP

#include "CircularBuffer.hpp"

typedef struct _SimpleDelay {
    int n;
    CircularBuffer * x;
    CircularBuffer * y;
    unsigned int xChannels;
    unsigned int yChannels;

} SimpleDelay;

void delay_init(SimpleDelay * self, int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out);
void delay_step(SimpleDelay * self);
#endif
