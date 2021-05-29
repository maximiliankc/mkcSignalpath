#include "SoundUnit.hpp"

SoundUnit::SoundUnit() {
    xChannels = 0;
    yChannels = 0;
    x = 0;
    y = 0;
}

SoundUnit::SoundUnit(unsigned int xc, unsigned int yc, CircularBuffer * in, CircularBuffer * out) {
    init(xc, yc, in, out);
}

void SoundUnit::init(unsigned int xc, unsigned int yc, CircularBuffer * in, CircularBuffer * out) {
    xChannels = xc;
    yChannels = yc;
    x = in;
    y = out;
}

unsigned int SoundUnit::get_x_channels(void) {
    return xChannels;
}

unsigned int SoundUnit::get_y_channels(void) {
    return yChannels;
}

CircularBuffer * SoundUnit::get_x(void) {
    return x;
}

CircularBuffer * SoundUnit::get_y(void) {
    return y;
}
