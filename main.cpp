#include <iostream>
#include "CircularBuffer.hpp"

void test_circ_buf(void);

int main(int argc, char ** argv) {

    test_circ_buf();
    return 0;
}

void test_circ_buf(void) {
    CircularBuffer buffer(4);
    int i;

    for(i = 0; i < 16; i++) {
        buffer.next(i);
        for(int k = 0; k < 8; k++) {
            std::cout << buffer.now(-k) << " ";
        }
        std::cout << "\n";
    }
    buffer.extend(8);
    for(; i < 32; i++) {
        buffer.next(i);
        for(int k = 0; k < 8; k++) {
            std::cout << buffer.now(-k) << " ";
        }
        std::cout << "\n";
    }

}