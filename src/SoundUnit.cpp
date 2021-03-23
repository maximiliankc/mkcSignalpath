#include "SoundUnit.hpp"

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