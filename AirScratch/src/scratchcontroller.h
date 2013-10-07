#ifndef SCRATCHCONTROLLER_H
#define SCRATCHCONTROLLER_H

#include <QObject>
#include <QTimer>

#include "bass.h"
#include "Scratcher.h"

class ScratchController : public QObject
{
    Q_OBJECT
public:
    explicit ScratchController(QObject *parent = 0);
    ~ScratchController();

signals:

public slots:
    void timerTick();

    void scratchStart(int x, int y);
    void scratchMove(int x, int y);
    void scratchEnd(int x, int y);

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

};

#endif // SCRATCHCONTROLLER_H
