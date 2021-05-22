#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(unsigned int _length, float * _buffer) {
    length = _length;
    buffer = _buffer;
    current = 0;
    // fill the buffer with zeros
    for(int i = 0; i < length; i++) {
        buffer[i] = 0.0;
    }
}

float CircularBuffer::now(unsigned int offset){
    int index = current + offset;
    index %= length;
    return buffer[index];
}

void CircularBuffer::next(float next){
    if(current == 0) {
        current = length;
    }
    current--;
    buffer[current] = next;
}

int CircularBuffer::get_len(void){
    return length;
}
