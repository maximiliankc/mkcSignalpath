#include <iostream>
#include <string>

#include "SoundPath.hpp"

// should read/print an audio file in [channels, len, fs, [channel 1 in PCM float [0,1]], ... , [channel n in PCM float [0,1]]]

int main(int argc, char** argv){
    float fs = 0;
    unsigned int channels = 0;
    unsigned int length = 0;
    unsigned int i;
    unsigned int j;
    float ** soundIn;
    float ** soundOut;

    SoundPath soundPath;
    std::string input;
    float * in;
    float * out;

    //point in and out to the right spots
    in = soundPath.getX();
    out = soundPath.getY();

    // extract the sampling frequency, length, channels

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

    soundIn = new float*[channels];
    soundOut = new float*[channels];

    // populate the list of channels
    for(i=0; i < channels; i++) {
        soundIn[i] = new float[length];
        soundOut[i] = new float[length];
        for(j=0; j < length; j++) {
            if(std::cin >> input){
                soundIn[i][j] = std::stof(input);
            } else {
                return 1;
            }
        }
    }

    // any sound processing should happen here to 
    for(j = 0; j < length; j++) {
        for(i = 0; i < channels; i++) {
            in[i] = soundIn[i][j];
        }
        soundPath.step();
        for(i = 0; i < channels; i++) {
            soundOut[i][j] = out[i];
        }
    }

    // printing everything out
    std::cout << channels << " ";
    std::cout << length << " ";
    std::cout << fs << " ";
    
    for(i=0; i < channels; i++) {
        for(j=0; j < length; j++) {
            std::cout << soundOut[i][j] << " ";
        }
        // delete the array
        delete[] soundIn[i];
        delete[] soundOut[i];
    }
    delete[] soundIn;
    delete[] soundOut;

    return 0;
}