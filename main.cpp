#include <iostream>
#include <string>

// should read/print an audio file in [channels, len, fs, [channel 1 in PCM float [0,1]], ... , [channel n in PCM float [0,1]]]

int main(int argc, char** argv){
    float fs = 0;
    unsigned int channels = 0;
    unsigned int length = 0;
    unsigned int i;
    unsigned int j;
    float ** sound;
    std::string input;

    if(std::cin >> input){
        channels = std::stoul(input);
    } else {
        return 1;
    }

    if(std::cin >> input){
        length = std::stoul(input);
    } else {
        return 1;
    }

    if(std::cin >> input){
        fs = std::stof(input);
    } else {
        return 1;
    }

    sound = new float*[channels];

    // populate the list of channels
    for(i=0; i < channels; i++) {
        sound[i] = new float[length];
        for(j=0; j < length; j++) {
            if(std::cin >> input){
                sound[i][j] = std::stof(input);
            } else {
                return 1;
            }
        }
    }
    // any sound processing should happen here to sound

    // printing everything out
    std::cout << channels << " ";
    std::cout << length << " ";
    std::cout << fs << " ";
    
    for(i=0; i < channels; i++) {
        for(j=0; j < length; j++) {
            std::cout << sound[i][j] << " ";
        }
        // delete the array
        delete[] sound[i];
    }
    delete[] sound;

    return 0;
}