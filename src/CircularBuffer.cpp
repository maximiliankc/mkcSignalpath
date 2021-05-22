#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(){
    initialised = false;
    length = 0;
    current = 0;
    buffer = 0;
}

CircularBuffer::CircularBuffer(unsigned int _length, float * _buffer) {
    init(_length, _buffer);
}

void CircularBuffer::init(unsigned int _length, float * _buffer) {
    length = _length;
    buffer = _buffer;
    current = 0;
    // fill the buffer with zeros
    for(int i = 0; i < length; i++) {
        buffer[i] = 0.0;
    }
    initialised=true;
}

float CircularBuffer::now(unsigned int offset){
    if(initialised) {
        int index = current + offset;
        index %= length;
        return buffer[index];
    } else {
        return 0;
    }
}

void CircularBuffer::next(float next){
    if(initialised) {
        if(current == 0) {
            current = length;
        }
        current--;
        buffer[current] = next;
    }
}

int CircularBuffer::get_len(void){
    return length;
}
