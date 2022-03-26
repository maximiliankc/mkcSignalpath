#include "SoundUnit.hpp"
#define OSC_CHANNELS 2
#define OSC_MEMORY 2

// Two channels in and out, only control over phase/magnitude is through starting impulse
class Oscillator: SoundUnit {
    float c;
    float s;

    public:
    Oscillator();
    Oscillator(CircularBuffer * in, CircularBuffer * out, float f);
    void init(CircularBuffer * in, CircularBuffer * out, float f);
    void step(void);
    void stop(void);
    void setF(float f);
};

class Square: SoundUnit{
    Oscillator osc;
    float s[OSC_CHANNELS][OSC_MEMORY];
    CircularBuffer s;

    public:
    Square();
    Square(CircularBuffer * in, CircularBuffer * out, float f);
    void init(CircularBuffer * in, CircularBuffer * out, float f);
    void step(void);
    void stop(void);
    void setF(float f);
};