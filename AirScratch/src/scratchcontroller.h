#ifndef SCRATCHCONTROLLER_H
#define SCRATCHCONTROLLER_H

#include <QObject>
#include <QTimer>

#include "bass.h"
#include "Scratcher.h"

#include "leaplistener.h"
#include "Leap.h"

class ScratchController : public QObject, public LeapCtrlListener
{
    Q_OBJECT
public:
    explicit ScratchController(QObject *parent = 0);
    ~ScratchController();

    void leapScratchStart(float pos, float ypos);
    void leapScratchMove(float pos, float ypos);
    void leapScratchEnd(float pos);



    static float FaderVolume;
signals:

public slots:
    void timerTick();

    void setFader(double volume);

    void scratchStart(int x, int y);
    void scratchMove(int x, int y);
    void scratchEnd(int x, int y);

    void gotoStart();

private:
    void initBass();

    HSTREAM mHandle;
    Scratcher* mScratcher;

    QTimer* mUpdateTimer;

    bool mScratching;

    float mInitScratchPos;
    float mScratchPosDiff;
    float mPrevScratchPos;

    float mDragOffset;


    HSTREAM mDecoder;

    FILE* mMappedFile;

    void* mMappedMemory;
    int mMappedMemorySize;

    Leap::Controller* mLeapCtrl;
    LeapListener* mLeapListener;
};

#endif // SCRATCHCONTROLLER_H
