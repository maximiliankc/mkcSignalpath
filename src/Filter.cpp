#include "Filter.h"


void filter_init(Filter * self, unsigned int c, CircularBuffer * in, CircularBuffer * out, unsigned int _aLen, float * _a, unsigned int _bLen, float * _b) {
    self->channels= c;
    self->x = in;
    self->y = out;
    self->bLen = _bLen;
    self->b = _b;
    self->aLen = _aLen;
    self->a = _a;
}

void filter_step(Filter * self) {
    float out;
    int i;
    int c;

    float bcoeff;
    float xnum;


    for(c = 0; c < self->channels; c++) {
        out = 0;
        // out = <x_in, b>, the feedforward part of the filter
        for(i = 0; i < self->bLen; i++) {
            bcoeff = self->b[i];
            xnum = circular_buffer_now(&(self->x[c]), i);
            out += bcoeff*xnum;
        }
        // now the feedback part, y[n] = <x_in, b> - <y, a> (except a0 and y[n] ofc)
        for(i = 1; i < self->aLen; i++) {
            out -= (self->a[i])*circular_buffer_now(&(self->y[c]), i-1);
        }
        // incorporate a0 and save
        circular_buffer_next(&(self->y[c]), out/(self->a[0]));
    }
}