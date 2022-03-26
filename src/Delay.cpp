#include "Delay.hpp"
#include <iostream>


SimpleDelay::SimpleDelay(): SoundUnit() {
    n = 0;
}

SimpleDelay::SimpleDelay(int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out):
                SoundUnit(c, c, in, out) {
    // the size of CircularBuffer must be at least n+1
    n = _n;
}

void SimpleDelay::init(int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out) {
    xChannels = c;
    yChannels = c;
    x = in;
    y = out;
    n = _n;
}

void SimpleDelay::step(void) {
    float intermediate;
    for(unsigned int i = 0; i < xChannels; i++) {
        intermediate = circular_buffer_now(&x[i], n);
        circular_buffer_next(&y[i], intermediate);
    }
}
