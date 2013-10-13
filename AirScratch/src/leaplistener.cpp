#include <iostream>

#include "leaplistener.h"
#include <QDebug>
#include <QTimer>

#include "Scratcher.h"

using namespace Leap;

LeapListener::LeapListener(QObject* parent)
    : QObject(parent), Listener()
{
    mListener = NULL;
    mScrolling = false;
}

void LeapListener::addControlListener(LeapCtrlListener* listener)
{
    qDebug() << __PRETTY_FUNCTION__ << (long int)listener;
    mListener = listener;
}

void LeapListener::onInit(const Controller &)
{
    qDebug() << __PRETTY_FUNCTION__ << "onInit";
}

void LeapListener::onConnect(const Controller& controller)
{
    qDebug() << __PRETTY_FUNCTION__ << "Connected";
    //controller.enableGesture(Gesture::TYPE_CIRCLE);
    //controller.enableGesture(Gesture::TYPE_KEY_TAP);
    //controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    //controller.enableGesture(Gesture::TYPE_SWIPE);
}

void LeapListener::onDisconnect(const Controller& controller)
{
    //Note: not dispatched when running in a debugger.
    qDebug() << __PRETTY_FUNCTION__ << "Disconnected";
}

void LeapListener::onExit(const Controller& controller)
{
    qDebug() << __PRETTY_FUNCTION__ << "Exited";
}

bool beginScratch = true;
bool beginFader = true;

void LeapListener::onFrame(const Controller& controller)
{
    // Get the most recent frame and report some basic information
    const Frame frame = controller.frame();
    /*qDebug() << __PRETTY_FUNCTION__ << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", fingers: " << frame.fingers().count()
            << ", tools: " << frame.tools().count()
            << ", gestures: " << frame.gestures().count();*/

    if (!frame.hands().empty())
    {
        //qDebug() << "HANDS COUNT " << frame.hands().count();

        // Get the first hand
        Hand scratchHand = frame.hands().leftmost();

        /***** Scratch gestures *****/

        // Check if the hand has any fingers
        const FingerList fingers = scratchHand.fingers();
        // Calculate the hand's average finger tip position
        Vector avgPos;
        Vector tipSpeed;
        if (!fingers.empty() && fingers.count() < 3)
        {

            for (int i = 0; i < fingers.count(); ++i)
            {
                avgPos += fingers[i].tipPosition();
                tipSpeed += fingers[i].tipVelocity();
            }

            avgPos /= (float)fingers.count();
            tipSpeed /= (float)fingers.count();


            //qDebug() << __PRETTY_FUNCTION__ << "Hand has " << fingers.count() << " fingers, average finger tip position" << avgPos.toString().c_str();

            if (beginScratch)
            {
                beginScratch = false;
                qDebug() << "Starting scratch at " << avgPos.x << ", " << (unsigned long)mListener;
                mListener->leapScratchStart(avgPos.x, avgPos.y);
            }
            else
            {
                mListener->leapScratchMove(avgPos.x, avgPos.y);
            }
        }
        else
        {
            beginScratch = true;
            mListener->leapScratchEnd(0);
        }

    }
}




void LeapListener::onFocusGained(const Controller& controller) {
  qDebug() << __PRETTY_FUNCTION__ << "Focus Gained";
}

void LeapListener::onFocusLost(const Controller& controller) {
  qDebug() << __PRETTY_FUNCTION__ << "Focus Lost";
}
