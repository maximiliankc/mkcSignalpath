#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer() {
    initialised = false;
}

CircularBuffer::CircularBuffer(int _length) {
    init(_length);
}

CircularBuffer::~CircularBuffer() {
    if(initialised) {
        delete[] buffer;
    }
}

void CircularBuffer::init(int _length) {
    length = _length;
    buffer = new float[length];
    current = 0;
    // fill the buffer with zero
    for(int i = 0; i < length; i++) {
        buffer[i] = 0.0;
    }
    initialised = true;
}

float CircularBuffer::now(int offset){
    if(initialised) {
        int index = current + offset;

        index %= length;
        // if index is negative, need to add the length
        if(index < 0) {
            index += length;
        }
        return buffer[index];
    } else {
        return 0.0;
    }
}

void CircularBuffer::next(float next){
    if(initialised) {
        current++;
        current %= length;
        buffer[current] = next;
    }
}

int CircularBuffer::get_len(void){
    if(initialised) {
        return length;
    } else {
        return 0;
    }
}

void CircularBuffer::extend(int newLength) {
    if(initialised) {
        float * newBuffer;
        int i;
        if(newLength > length) {
            // only need to extend the buffer if the new length is longer than the existing one
            // preserves looking back, not forward
            newBuffer = new float[newLength];

            for(i = 0; i < newLength; i++) {
                newBuffer[i] = 0.0;
            }
            for(i = 0; i > -length; i--) {
                newBuffer[length + i - 1] = now(i);
            }
            
            current = length - 1;
            length = newLength;
            delete[] buffer;
            buffer = newBuffer;
        }
    }
}