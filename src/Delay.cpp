#include "Delay.hpp"


void delay_init(SimpleDelay * self, int _n, unsigned int c, CircularBuffer * in, CircularBuffer * out) {
    self->xChannels = c;
    self->yChannels = c;
    self->x = in;
    self->y = out;
    self->n = _n;
}

void delay_step(SimpleDelay * self) {
    float intermediate;
    for(unsigned int i = 0; i < self->xChannels; i++) {
        intermediate = circular_buffer_now(&(self->x[i]), self->n);
        circular_buffer_next(&(self->y[i]), intermediate);
    }
}
