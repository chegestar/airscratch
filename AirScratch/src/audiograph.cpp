#include "audiograph.h"
#include "Scratcher.h"
#include <QPainter>

#include <QTimer>

#define BUF_SIZE (256*1024)

float* AudioGraph::mBuf;
int AudioGraph::mBufSize = BUF_SIZE;
int AudioGraph::bufDensity = 50;

bool AudioGraph::initialized = false;

void AudioGraph::initBuf()
{

    if (!initialized)
    {
        initialized = true;
        qDebug() << __PRETTY_FUNCTION__;
         mBuf = (float*)malloc(sizeof(float)*BUF_SIZE);
         mBufSize = BUF_SIZE;
         qDebug() << __PRETTY_FUNCTION__ << "exit";
    }
}

AudioGraph::AudioGraph(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
    setRenderTarget(QQuickPaintedItem::FramebufferObject);

    mTimer = new QTimer(this);
    mTimer->setInterval(15);
    mTimer->setTimerType(Qt::PreciseTimer);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(update()));
    mTimer->start();
    qDebug() << __PRETTY_FUNCTION__ << "exit";
}

AudioGraph::~AudioGraph()
{
    free(mBuf);
}

float bufAvg(float* buf)
{
    float sum = 0.0;
    for (int i = -10; i < 10; i++)
    {
        sum += buf[2*i];
    }
    return sum /= 20;

}

static QPointF points[1000];

int drawSamples = 44100 / AudioGraph::bufDensity;

void AudioGraph::paint(QPainter *painter)
{
    QBrush brush(QColor("#0000ff"));
    QPen pen(QColor("#0000ff"));
    painter->setBrush(brush);
    painter->setPen(pen);


    int step = 1;
    int hoff= height()/2;



    int w = width();

    float curOffset = Scratcher::getPosOffset();
    int bufStart = 2*curOffset/(AudioGraph::bufDensity) - w/2;
    //qDebug() << "curoff: " << curOffset << ", bufstart: " << bufStart;
    float* buf= &mBuf[bufStart];

    float prevVal = 0;

    for (unsigned i = 0; i < w; i++ )
    {

        float curVal = buf[i];

        painter->drawLine(i, prevVal + hoff, i+1, curVal + hoff);

        //float curVal = bufAvg(&buf[step*i]);
        //float curVal = buf[step*i];

        //points[i] = QPointF(i, curVal*1000 + offset);

        //painter->drawLine(i, (prevVal)*1000 + offset, i+1, (curVal)*1000 + offset);
        //painter->drawPoint(i, (curVal)*1000 + offset);



        //painter->drawLine(i, offset, i, offset + curVal*1000);



        prevVal = curVal;

        //x++;
    }

   // painter->drawPolyline(points, w);
//

    //painter->endNativePainting();

    //qDebug() << "paint end";

}
