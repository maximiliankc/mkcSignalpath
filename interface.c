#include "SoundPath.h"


void run(int samples, float ** in, float ** out);

void run(int samples, float ** in, float ** out) {
    int m;
    SoundPath soundpath;

    soundpath_init(&soundpath);

    for(int n=0; n < samples; n++) {
        for(m=0; m < IN_CHANNELS; m++) {
            out[m][n] = in[m][n];
        }
    }
}
