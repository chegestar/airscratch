import QtQuick 2.0
import QtAudioEngine 1.0
import QtMultimedia 5.0

import com.sandst1.components 1.0

Rectangle {
    width: 1000
    height: 500


    AudioGraph {
        anchors.fill: parent
    }

    Rectangle {
        anchors.centerIn: parent
        height: parent.height
        width: 75;
        color: "#80ff0000"
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    Audio {
        id: drumBeat
        source: "../../../AirScratch/audio/drumloop.wav"
        volume: 1.5

        onPlaybackStateChanged: {
            if (!playing()) {
                play();
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onMouseXChanged: {

            var min = width/4;
            var max = 3*width/4;

            var x = mouseX;

            x = (mouseX - min)/(max - min);
            if (x < 0.0) x = 0.0;
            if (x > 1.0) x = 1.0;

            ScratchCtrl.setFader(x);

        }
    }


    Component.onCompleted: {
        drumBeat.play();
    }




}
