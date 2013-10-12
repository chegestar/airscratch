#ifndef RIAAFILTER_H
#define RIAAFILTER_H

#include "bass.h"

class RIAAFilter
{
public:
    RIAAFilter();

    static void RecordingFilter(float* buf, DWORD bufSize);
    static void PlaybackFilter(float* buf, DWORD bufSize);

};

#endif // RIAAFILTER_H
