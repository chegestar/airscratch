#include "scratchcontroller.h"

#define BYTE_POSITION_TO_PIXELS 0.0025f
#include <QFile>
#include <QTimer>

#include <QDebug>


#include <sys/mman.h>
#include "Sys.h"

#include <unistd.h>

//#define AUDIO_FILE "30secloop.wav"
//#define AUDIO_FILE "edison.wav"
#define AUDIO_FILE "king_nonviolence.wav"


namespace
{
    struct Info
    {
        HSTREAM decoder;
        void* data;
    } info;

    /*
    float GetBestAngleDiff(float a)
    {
        float a1 = a - 2.0f * M_PI;
        float a2 = a + 2.0f * M_PI;

        if (fabsf(a) < fabsf(a1))
        {
            if (fabsf(a) < fabsf(a2))
                return a;

            return a2;
        }

        if (fabsf(a2) < fabsf(a1))
            return a2;

        return a1;
    }*/

    void* Unpack(void* arg)
    {
        HSTREAM decoder = info.decoder;
        char* output = (char*)info.data;

        // buffer size per step for normalization
        float buf[10000];

        BASS_ChannelSetPosition(decoder, 0, BASS_POS_BYTE);

        int pos = 0;

        while (BASS_ChannelIsActive(decoder))
        {
            DWORD c = BASS_ChannelGetData(decoder, buf, sizeof(buf)|BASS_DATA_FLOAT);

            memcpy(output + pos, buf, c);
            pos += c;
        }

        BASS_StreamFree(decoder);

        return NULL;
    }
}


ScratchController::ScratchController(QObject *parent) :
    QObject(parent)
{
    initBass();
}

ScratchController::~ScratchController()
{
    fclose(mMappedFile);
    munmap(mMappedMemory, mMappedMemorySize);
}


void ScratchController::timerTick()
{


    const double now = Sys::GetSeconds();

    static double lastTime = 0.0;

    if (lastTime < 0.0001)
    {
        lastTime = now;
    }

    const double dt = now - lastTime;
    lastTime = now;

    mScratcher->Update(dt);
    /*float offset = BYTE_POSITION_TO_PIXELS * scratcher_->GetByteOffset();

    CGAffineTransform t = CGAffineTransformIdentity;

    t = CGAffineTransformTranslate(t, -256.0f, -256.0f);
    t = CGAffineTransformTranslate(t, 160.0f, 240.0f);
    t = CGAffineTransformRotate(t, offset);*/

}

void ScratchController::initBass()
{
    BASS_Init(-1, 44100, 0, 0, NULL);

    BASS_SetConfig(BASS_CONFIG_BUFFER, 5);
    BASS_SetConfig(BASS_CONFIG_UPDATETHREADS, 1);
    BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 5);

    //std::string fpath = "/home/topisa/proj/hackfest2013/airscratch/AirScratch/audio/30secloop.wav";
    //mHandle = BASS_StreamCreateFile(false, fpath.c_str(), 0, 0, BASS_SAMPLE_FLOAT|BASS_SAMPLE_LOOP|BASS_STREAM_PRESCAN);


    //std::string fpath = "/home/topisa/proj/hackfest2013/airscratch/AirScratch/audio/30secloop.wav";

    std::string fpath = "/home/topisa/proj/hackfest2013/airscratch/AirScratch/audio/" AUDIO_FILE;

    mDecoder = BASS_StreamCreateFile(FALSE, fpath.c_str(), 0, 0, BASS_SAMPLE_FLOAT|BASS_STREAM_PRESCAN|BASS_STREAM_DECODE);
    mMappedMemorySize = BASS_ChannelGetLength(mDecoder, BASS_POS_BYTE);

    mMappedFile = tmpfile();
    int fd = fileno(mMappedFile);

    ftruncate(fd, mMappedMemorySize);

    mMappedMemory = mmap(
                        NULL,                    /* No preferred address. */
                        mMappedMemorySize,                /* Size of mapped space. */
                        PROT_READ | PROT_WRITE,  /* Read/write access. */
                        MAP_FILE | MAP_SHARED,   /* Map from file (default) and map as shared (see above.) */
                        fd,                      /* The file descriptor. */
                        0                        /* Offset from start of file. */
                        );



    mScratcher = new Scratcher();
    mScratcher->SetBuffer((float*)mMappedMemory, mMappedMemorySize);


    info.decoder = mDecoder;
    info.data = mMappedMemory;

    pthread_t thread;
    pthread_create(&thread, NULL, Unpack, (void*)&info);















    mUpdateTimer = new QTimer(this);
    mUpdateTimer->setInterval(1000/60);
    connect(mUpdateTimer, SIGNAL(timeout()), this, SLOT(timerTick()));
    mScratching = false;

    BASS_ChannelPlay(mHandle, true);

    mUpdateTimer->start();


}


void ScratchController::scratchStart(int x, int y)
{

    mScratching = true;

        //mStartScratchPosition = x;
        //mDragOffset = mStartScratchPosition; // -x

    //prevAngle_ = NAN;
    mInitScratchPos = mScratcher->GetByteOffset();

    mScratchPosDiff = 0;

 qDebug() << "ScratchStart " << x << ", pos: " << mInitScratchPos;
    //angleAccum_ = 0.0f;

    mScratcher->SetByteOffset(mInitScratchPos + mScratchPosDiff);

    mScratcher->BeganScratching();

    mPrevScratchPos = x;

}

void ScratchController::scratchMove(int x, int y)
{
    //qDebug() << "ScratchMove " << x << ", " << y;
    if (mScratching)
    {
        /*const float offset = x + mDragOffset - mStartScratchPosition;
        mScratcher->SetByteOffset(offset / BYTE_POSITION_TO_PIXELS);

        qDebug() << "setting offset to " << offset << ", byteoff: " << offset/BYTE_POSITION_TO_PIXELS;*/


        float diff = ((float)x - mPrevScratchPos)/BYTE_POSITION_TO_PIXELS;
        mScratchPosDiff += diff;

        qDebug() << "scratch offset " << (x-mPrevScratchPos) << ", in bytes: " << mScratchPosDiff
                 << ", setting offset to " << (mInitScratchPos+mScratchPosDiff);

        mScratcher->SetByteOffset(mInitScratchPos + mScratchPosDiff);

        mPrevScratchPos = x;


    }

}

void ScratchController::scratchEnd(int x, int y)
{
    qDebug() << "ScratchEnd " << x << ", " << y;

    if (mScratching)
    {
        mScratching = false;
        mScratcher->EndedScratching();
    }
}
