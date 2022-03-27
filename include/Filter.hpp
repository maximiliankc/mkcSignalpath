#include "SoundUnit.hpp"

// a[0]y[n] + ... + a[N]y[n-N] = b[0]x[0] + ... + b[M]x[n-M]
// y[n] = (b[0]x[0] + ... + b[M]x[n-M] - (a[1]y[n-1] + ... + a[N]y[n-N]))/a[0]
// H(z) = (b[0]z^-0 + ... + b[0]z^-M)/(a[0]z^-0 + ... + a[M]z^-N) 

struct Filter{
    CircularBuffer * x;
    CircularBuffer * y;
    unsigned int channels;
    unsigned int aLen;
    float * a;
    unsigned int bLen;
    float * b;
};

void filter_init(Filter * self, unsigned int c, CircularBuffer * in, CircularBuffer * out, unsigned int _aLen, float * _a, unsigned int _bLen, float * _b);
void filter_step(Filter * self);