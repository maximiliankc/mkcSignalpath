#include "Oscillator.hpp"
#include <cmath>
// will likely need to ifdef this import if putting in an embedded system


void osc_init(Oscillator * self, CircularBuffer * in, CircularBuffer * out, float f) {
    self->x = in;
    self->y = out;
    osc_setF(self, f);
}

void osc_step(Oscillator * self) {
    // thinking of it as a complex exponential
    float real;
    float imaginary;
    // do the cosine first
    real = self->c*circular_buffer_now(&(self->y[0]), 0) - self->s*circular_buffer_now(&(self->y[1]), 0) + circular_buffer_now(&(self->x[0]), 0);
    // next the sine
    imaginary = self->s*circular_buffer_now(&(self->y[0]), 0) + self->c*circular_buffer_now(&(self->y[1]), 0) + circular_buffer_now(&(self->x[1]), 0);
    // save the result
    circular_buffer_next(&(self->y[0]), real);
    circular_buffer_next(&(self->y[1]), imaginary);
}

void osc_stop(Oscillator * self) {
    // set the current state 
    circular_buffer_next(&(self->y[0]), 0);
    circular_buffer_next(&(self->y[1]), 0);
}

void osc_setF(Oscillator * self, float f) {
    self->c = cosf(2*M_PI*f);
    self->s = sinf(2*M_PI*f);
}