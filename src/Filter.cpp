#include "Filter.hpp"
#include <iostream>

Filter::Filter(): SoundUnit() {
    numLength = 0;
    b = 0;
    denLength = 0;
    a = 0;
}

Filter::Filter(unsigned int c, CircularBuffer * in, CircularBuffer * out, unsigned int _numLength, float * _a, unsigned int _denLength, float * _b):
    SoundUnit(c, c, in, out) {
    numLength = _numLength;
    b = _b;
    denLength = _denLength;
    a = _a;
}

void Filter::init(unsigned int c, CircularBuffer * in, CircularBuffer * out, unsigned int _denLength, float * _a, unsigned int _numLength, float * _b) {
    SoundUnit::init(c, c, in, out);
    updateDenominator(_denLength, _a);
    updateNumerator(_numLength, _b);
}

void Filter::updateNumerator(unsigned int length, float * coefficients) {
    numLength = length;
    b = coefficients;
}

void Filter::updateDenominator(unsigned int length, float * coefficients) {
    denLength = length;
    a = coefficients;
}

DFIFilter::DFIFilter():Filter() {
    // everything we need is in the parent constructor
}

DFIFilter::DFIFilter(unsigned int c, CircularBuffer * in, CircularBuffer * out, unsigned int _denLength, float * _a, unsigned int _numLength, float * _b):
    Filter(c, in, out, _numLength, _a, _denLength, _b) {
    // everyting we need is in the parent constructor
}

void DFIFilter::step(void) {
    float out;
    int i;
    int c;

    float bcoeff;
    float xnum;


    for(c = 0; c < xChannels; c++) {
        out = 0;
        for(i = 0; i < numLength; i++) {
            bcoeff = b[i];
            xnum = x[c].now(i);
            out += bcoeff*xnum;
            //out += b[i]*x[c].now(i);
        }
        for(i = 1; i < denLength; i++) {
            out -= a[i]*y[c].now(i-1);
        }
        y[c].next(out/a[0]);
    }
}