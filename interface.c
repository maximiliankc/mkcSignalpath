#include "SoundPath.h"
#include <stdio.h>

void run(int samples, float * in1, float * in2, float * out1, float * out2);

void run(int samples, float * in1, float * in2, float * out1, float * out2) {
    SoundPath soundpath;

    soundpath_init(&soundpath);

    for(int n=1; n < samples; n++) {
        soundpath.x[0] = in1[n];
        soundpath.x[1] = in2[n];
        soundpath_step(&soundpath);
        out1[n] = soundpath.y[0];
        out2[n] = soundpath.y[1];
    }
}
