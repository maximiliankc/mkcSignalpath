#include <stdio.h>

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
    float input;
    float * in;
    float * out;

    soundpath_init(&soundPath);

    //point in and out to the right spots
    in = soundPath.x;
    out = soundPath.y;

    // extract the sampling frequency, length, channels
    if(!scanf("%d", &channels)) {
        return 1;
    }

    if(!scanf("%d", &length)){
        return 1;
    }

    if(!scanf("%g", &fs)) {
        return 1;
    }

    soundIn = new float*[channels];
    soundOut = new float*[channels];

    // populate the list of channels
    for(i=0; i < channels; i++) {
        soundIn[i] = new float[length];
        soundOut[i] = new float[length];
        for(j=0; j < length; j++) {
            if(!scanf("%g", &input)) {
                return 1;
            }
        }
    }

    // any sound processing should happen here to 
    for(j = 0; j < length; j++) {
        for(i = 0; i < channels; i++) {
            in[i] = soundIn[i][j];
        }
        soundpath_step(&soundPath);
        for(i = 0; i < channels; i++) {
            soundOut[i][j] = out[i];
        }
    }

    // printing everything out
    printf("%d ", channels);
    printf("%d ", length);
    printf("%g ", fs);
    
    for(i=0; i < channels; i++) {
        for(j=0; j < length; j++) {
           printf("%g ", soundOut[i][j]);
        }
        // delete the array
        delete[] soundIn[i];
        delete[] soundOut[i];
    }
    delete[] soundIn;
    delete[] soundOut;

    return 0;
}