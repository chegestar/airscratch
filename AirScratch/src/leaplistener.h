#ifndef LEAPLISTENER_H
#define LEAPLISTENER_H

#include "Leap.h"
#include <QObject>


class LeapCtrlListener
{
public:
    virtual void leapScratchStart(float pos, float ypos) = 0;
    virtual void leapScratchMove(float pos, float ypos) = 0;
    virtual void leapScratchEnd(float pos) = 0;
};


class QTimer;


class LeapListener : public QObject, public Leap::Listener
{
    Q_OBJECT
public:
  LeapListener(QObject* parent);

  void addControlListener(LeapCtrlListener* listener);

  virtual void onInit(const Leap::Controller&);
  virtual void onConnect(const Leap::Controller&);
  virtual void onDisconnect(const Leap::Controller&);
  virtual void onExit(const Leap::Controller&);
  virtual void onFrame(const Leap::Controller&);
  virtual void onFocusGained(const Leap::Controller&);
  virtual void onFocusLost(const Leap::Controller&);

public slots:


private:
  LeapCtrlListener* mListener;
  QTimer* mScrollTimer;
  bool mScrolling;
};

#endif // LEAPLISTENER_H
