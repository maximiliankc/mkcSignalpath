#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "CircularBuffer.h"
#define OSC_CHANNELS 2
#define OSC_MEMORY 2

// Two channels in and out, only control over phase/magnitude is through starting impulse
typedef struct Oscillator {
    CircularBuffer * x;
    CircularBuffer * y;
    float c;
    float s;
} Oscillator;

void osc_init(Oscillator * self, CircularBuffer * in, CircularBuffer * out, float f);
void osc_setF(Oscillator * self, float f);
void osc_step(Oscillator * self);
void osc_stop(Oscillator * self);

#endif
