#ifndef AUDIOGRAPH_H
#define AUDIOGRAPH_H

#include <QQuickPaintedItem>
#include "bass.h"

class QTimer;
class AudioGraph : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit AudioGraph(QQuickItem *parent = 0);
    ~AudioGraph();

    void paint(QPainter *painter);

    static void initBuf();
    static float* mBuf;
    static int mBufSize;
    static bool initialized;
    static int bufDensity;

signals:

public slots:

private:


    QTimer* mTimer;

};

#endif // AUDIOGRAPH_H
