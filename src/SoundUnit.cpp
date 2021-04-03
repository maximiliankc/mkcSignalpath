#include "SoundUnit.hpp"

SoundUnit::SoundUnit(CircularBuffer * in, int inLength, int outLength) {
    in->extend(inLength);
    x = in;
    y = new CircularBuffer(outLength);
}

SoundUnit::~SoundUnit() {
    delete y;
}

CircularBuffer * SoundUnit::get_x(void) {
    return x;
}

CircularBuffer * SoundUnit::get_y(void) {
    return y;
}