#include <iostream>
#include <string>

int main(int argc, char** argv){
    std::string input;

    while (std::cin >> input) {
        std::cout << input << " ";
    }

    return 0;
}