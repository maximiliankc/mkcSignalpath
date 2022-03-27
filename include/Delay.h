#ifndef DELAY_H
#define DELAY_H

#include "CircularBuffer.h"

typedef struct SimpleDelay {
    int n;
    CircularBuffer * x;
    CircularBuffer * y;
    unsigned int xChannels;
    unsigned int yChannels;

} SimpleDelay;

void delay_init(SimpleDelay * self, int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out);
void delay_step(SimpleDelay * self);
#endif
