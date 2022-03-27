#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

// a pretty simple Circular buffer, with a float at its core
// the intended use is to look back in time, not forward, and functions are defined as such

typedef struct _CircularBuffer {
    unsigned int current;
    unsigned int length;
    float * buffer;
} CircularBuffer;

void circular_buffer_init(CircularBuffer * self, unsigned int _length, float * _buffer);
float circular_buffer_now(CircularBuffer * self, unsigned int offset); // gets the current index + the offset
void circular_buffer_next(CircularBuffer * self, float next); // takes in a new input

#endif