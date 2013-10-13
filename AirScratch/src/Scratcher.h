#ifndef __SCRATCHER_HH__
#define __SCRATCHER_HH__

/*
 *  Scratcher.h
 *  RadballsPP
 *
 *  Created by Jan Kalis on 5/14/10.
 *  Copyright 2010 Glow Interactive. All rights reserved.
 *
 */

#include "bass.h"



static const unsigned int smoothBufferSize = 3000;

class Scratcher
{

public:
    Scratcher();
    ~Scratcher();

    void Update(float dt);

    void SetBuffer(float* buffer, int size);

    void SetByteOffset(float byteOffset);
    float GetByteOffset() const;

    void setScratchOffset(float offset) { scratchingPositionOffset_ = offset;}

    void BeganScratching();
    void EndedScratching();

    static float getPosOffset() { return scratchingPositionOffset_; }

private:
    static DWORD CALLBACK WriteScratchStream(HSTREAM handle, void* writeBuffer, DWORD length, void* user);

    HSTREAM soundTrackScratchStreamHandle_;

    bool isScratching_;

    float* buffer_;
    int size_;

    static float scratchingPositionOffset_;

    float scratchingPositionSmoothedVelocity_;
    float scratchingPositionVelocity_;

    float smoothBuffer_[smoothBufferSize];
    int smoothBufferPosition_;

    float previousTime_;

    float positionOffset_;
    float previousPositionOffset_;
};

#endif
