#include "Delay.hpp"

SimpleDelay::SimpleDelay(int _n, CircularBuffer * in): SoundUnit(in, _n + 1, 1) {
    n = _n;
}

void SimpleDelay::step(void) {
    y->next(x->now(-n));
}
