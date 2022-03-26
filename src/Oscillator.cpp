#include "Oscillator.hpp"
#include <cmath>
// will likely need to ifdef this import if putting in an embedded system

Oscillator::Oscillator(): SoundUnit() {
    c = 0;
    s = 0;
}

Oscillator::Oscillator(CircularBuffer * in, CircularBuffer * out, float f):
    SoundUnit(OSC_CHANNELS, OSC_CHANNELS, in, out) {
    setF(f);
}

void Oscillator::init(CircularBuffer * in, CircularBuffer * out, float f) {
    SoundUnit::init(OSC_CHANNELS, OSC_CHANNELS, in, out);
    setF(f);
}

void Oscillator::step(void) {
    // thinking of it as a complex exponential
    float real;
    float imaginary;
    // do the cosine first
    real = c*circular_buffer_now(&y[0], 0) - s*circular_buffer_now(&y[1], 0) + circular_buffer_now(&x[0], 0);
    // next the sine
    imaginary = s*circular_buffer_now(&y[0], 0) + c*circular_buffer_now(&y[1], 0) + circular_buffer_now(&x[1], 0);
    // save the result
    circular_buffer_next(&y[0], real);
    circular_buffer_next(&y[1], imaginary);
}

void Oscillator::stop(void) {
    // set the current state 
    circular_buffer_next(&y[0], 0);
    circular_buffer_next(&y[1], 0);
}

void Oscillator::setF(float f) {
    c = cosf(2*M_PI*f);
    s = sinf(2*M_PI*f);
}