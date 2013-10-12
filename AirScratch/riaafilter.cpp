#include "riaafilter.h"
#include <stdio.h>
#include <string.h>

#include <math.h>

RIAAFilter::RIAAFilter()
{
}

// The Recording side of RIAA Equalization
static float recA[3] = { 1.0000000000, -0.7218922000, -0.1860520545 };
static float recB[3] = { 1.0000000000, -1.7007240000, 0.7029381524 };

static float playA[3] = { 1.0000000000, -1.7007240000, 0.7029381524 };
static float playB[3] = { 1.0000000000, -0.7218922000, -0.1860520545 };

static float rectmp[10000];
static float playtmp[10000];

void RIAAFilter::RecordingFilter(float* buf, DWORD bufSize)
{
    float* a = &recA[0];
    float* b = &recB[0];

    memset(rectmp, 0.0, 10000);
    memcpy(rectmp, buf, bufSize);

    static float ly0 = 0.0;
    static float ly1 = 0.0;
    static float ly2 = 0.0;
    static float lx0 = 0.0;
    static float lx1 = 0.0;
    static float lx2 = 0.0;

    static float ry0 = 0.0;
    static float ry1 = 0.0;
    static float ry2 = 0.0;
    static float rx0 = 0.0;
    static float rx1 = 0.0;
    static float rx2 = 0.0;

    for (unsigned int i = 0; i < bufSize/4; i+=2)
    {
        if (i >= 4)
        {
            lx0 = rectmp[i];
            lx1 = rectmp[i-2];
            lx2 = rectmp[i-4];
            rx0 = rectmp[i+1];
            rx1 = rectmp[i-1];
            rx2 = rectmp[i-3];
        }

        // b(z^-1)/a(z^-1)
        // Filter the left channel
        ly0 = b[0]*lx0 + b[1]*lx1 + b[2]*lx2 - a[1]*ly1 -a[2]*ly2;
        ry0 = b[0]*rx0 + b[1]*rx1 + b[2]*rx2 - a[1]*ry1 -a[2]*ry2;

        // Set the value to the output buffer
        *buf++ = ly0;
        *buf++ = ry0;

        ly2 = ly1;
        ly1 = ly0;

        ry2 = ry1;
        ry1 = ry0;
    }
}

void RIAAFilter::PlaybackFilter(float* buf, DWORD bufSize)
{
    float* a = &playA[0];
    float* b = &playB[0];

    memset(playtmp, 0.0, 10000);
    memcpy(playtmp, buf, bufSize);

    static float ly0 = 0.0;
    static float ly1 = 0.0;
    static float ly2 = 0.0;
    static float lx0 = 0.0;
    static float lx1 = 0.0;
    static float lx2 = 0.0;

    static float ry0 = 0.0;
    static float ry1 = 0.0;
    static float ry2 = 0.0;
    static float rx0 = 0.0;
    static float rx1 = 0.0;
    static float rx2 = 0.0;

    for (unsigned int i = 0; i < bufSize/4; i+=2)
    {
        if (i >= 4)
        {
            lx0 = playtmp[i];
            lx1 = playtmp[i-2];
            lx2 = playtmp[i-4];
            rx0 = playtmp[i+1];
            rx1 = playtmp[i-1];
            rx2 = playtmp[i-3];
        }

        // b(z^-1)/a(z^-1)
        // Filter the left channel
        ly0 = b[0]*lx0 + b[1]*lx1 + b[2]*lx2 - a[1]*ly1 -a[2]*ly2;
        ry0 = b[0]*rx0 + b[1]*rx1 + b[2]*rx2 - a[1]*ry1 -a[2]*ry2;

        // Set the value to the output buffer
        *buf++ = tanh(ly0);
        *buf++ = tanh(ry0);

        //*buf++ = ly0;
        //*buf++ = ry0;

        ly2 = ly1;
        ly1 = ly0;

        ry2 = ry1;
        ry1 = ry0;
    }
}
