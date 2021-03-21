#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

// a pretty simple Circular buffer, with a float at its core

class CircularBuffer {
    int current;
    int length;
    float * buffer;

    public:
    CircularBuffer(int);
    ~CircularBuffer();
    float now(int offset); // gets the current index + the offset
    void next(float next); // 
    int get_len(void); // length of the buffer

};

#endif