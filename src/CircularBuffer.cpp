#include "CircularBuffer.hpp"


void circular_buffer_init(CircularBuffer * self, unsigned int _length, float * _buffer) {
    self->length = _length;
    self->buffer = _buffer;
    self->current = 0;
    // fill the buffer with zeros
    for(int i = 0; i < self->length; i++) {
        self->buffer[i] = 0.0;
    }
}

float circular_buffer_now(CircularBuffer * self, unsigned int offset){
    int index = self->current + offset;
    index %= self->length;
    return self->buffer[index];
}

void circular_buffer_next(CircularBuffer * self, float next){
    if(self->current == 0) {
        self->current = self->length;
    }
    self->current--;
    self->buffer[self->current] = next;
}
