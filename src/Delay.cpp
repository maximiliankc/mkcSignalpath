#include "Delay.hpp"

SimpleDelay::SimpleDelay(int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out):
                SoundUnit(c, c, in, out) {
    // the size of CircularBuffer must be at least n
    n = _n;
}

void SimpleDelay::step(void) {
    for(unsigned int i = 0; i < xChannels; i++) {
        y[i].next(x[i].now(n));
    }
}
