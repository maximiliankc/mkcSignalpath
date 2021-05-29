#include "SoundUnit.hpp"

// a[0]y[n] + ... + a[N]y[n-N] = b[0]x[0] + ... + b[M]x[n-M]
// y[n] = (b[0]x[0] + ... + b[M]x[n-M] - (a[1]y[n-1] + ... + a[N]y[n-N]))/a[0]
// H(z) = (b[0]z^-0 + ... + b[0]z^-M)/(a[0]z^-0 + ... + a[M]z^-N) 

class Filter: public SoundUnit {
protected:
    unsigned int denLength;
    float * a;
    unsigned int numLength;
    float * b;

public:
    Filter();
    Filter(unsigned int xc, unsigned int yc, CircularBuffer * in, CircularBuffer * out, unsigned int numLength, float * a, unsigned int denLength, float * b); 
    void init(unsigned int xc, unsigned int yc, CircularBuffer * in, CircularBuffer * out, unsigned int numLength, float * a, unsigned int denLength, float * b);
    void updateNumerator(unsigned int length, float * coefficients);
    void updateDenominator(unsigned int length, float * coefficients);
};

class DFIFilter: public Filter {
    public:
    DFIFilter();
    DFIFilter(unsigned int xc, unsigned int yc, CircularBuffer * in, CircularBuffer * out, unsigned int numLength, float * a, unsigned int denLength, float * b);
    void step(void);
};