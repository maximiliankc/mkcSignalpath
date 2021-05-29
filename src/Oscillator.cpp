#include "Oscillator.hpp"
#include <cmath>
// will likely need to ifdef this import if putting in an embedded system
#include <iostream>

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
    real = c*y[0].now(0) - s*y[1].now(0) + x[0].now(0);
    // next the sine
    imaginary = s*y[0].now(0) + c*y[1].now(0) + x[1].now(0);
    y[0].next(real);
    y[1].next(imaginary);
}

void Oscillator::stop(void) {
    y[0].next(0);
    y[1].next(0);
}

void Oscillator::setF(float f) {
    c = cosf(2*M_PI*f);
    s = sinf(2*M_PI*f);
}