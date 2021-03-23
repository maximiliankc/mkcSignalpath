#include "SoundUnit.hpp"

SoundUnit::SoundUnit(CircularBuffer * in, int inChannels, int inLength, int outChannels, int outLength) {
    xChannels = inChannels;
    for(int i = 0; i < inChannels; i++) {
        in[i].extend(inLength);
    }
    yChannels = outChannels;
    y = new CircularBuffer[outChannels];
    for(int j = 0; j < outChannels; j++) {
        y[j].init(outLength);
    }
}

SoundUnit::~SoundUnit() {
    delete[] y;
}

CircularBuffer * SoundUnit::get_x(void) {
    return x;
}

CircularBuffer * SoundUnit::get_y(void) {
    return y;
}

int SoundUnit::get_x_channels(void) {
    return xChannels;
}

int SoundUnit::get_y_channels(void) {
    return yChannels;
}