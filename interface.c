#include "SoundPath.h"
#include <stdio.h>

void run(int samples, float * in1, float * in2, float * out1, float * out2);

void run(int samples, float * in1, float * in2, float * out1, float * out2) {
    SoundPath soundpath;

    soundpath_init(&soundpath);

    for(int n=0; n < samples; n++) {
        out1[n] = in1[n];
        out2[n] = in2[n];
        printf("%g, %g\n", in1[n], in2[n]);
        printf("%g, %g\n", out1[n], out2[n]);
    }
}
