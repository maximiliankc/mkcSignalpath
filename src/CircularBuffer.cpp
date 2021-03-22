#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(int _length) {
    length = _length;
    buffer = new float[length];
    current = 0;
    // fill the buffer with zero
    for(int i = 0; i < length; i++) {
        buffer[i] = 0.0;
    }
}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
}

float CircularBuffer::now(int offset){
    int index = current + offset;

    index %= length;
    // if index is negative, need to add the length
    if(index < 0) {
        index += length;
    }
    return buffer[index];
}

void CircularBuffer::next(float next){
    current++;
    current %= length;
    buffer[current] = next;
}

int CircularBuffer::get_len(void){
    return length;
}