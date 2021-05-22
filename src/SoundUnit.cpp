#include "SoundUnit.hpp"

SoundUnit::SoundUnit(unsigned int c, CircularBuffer * in, CircularBuffer * out){
    channels = c;
    x = in;
    y = out;
}

unsigned int SoundUnit::get_channels(void) {
    return channels;
}

CircularBuffer * SoundUnit::get_x(void) {
    return x;
}

CircularBuffer * SoundUnit::get_y(void) {
    return y;
}