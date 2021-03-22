#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

// a pretty simple Circular buffer, with a float at its core
// the intended use is to look back in time, not forward, and functions are defined as such

class CircularBuffer {
    int current;
    int length;
    float * buffer;

    public:
    CircularBuffer(int);
    ~CircularBuffer();
    float now(int offset); // gets the current index + the offset
    void next(float next); // takes in a new input
    int get_len(void); // length of the buffer
    void extend(int newLength);

};

#endif