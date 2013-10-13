import QtQuick 2.0

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
    /*MouseArea {
        anchors.fill: parent


        onMouseXChanged: {
            console.log("CHANGE X " + mouseX );

            ScratchCtrl.faderMove(1.0 - mouseX / width);
        }

    }*/

    /*Rectangle {
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 100;

        color: "#0000ff"

        MouseArea {
            anchors.fill: parent


            onMouseXChanged: {
                console.log("CHANGE X " + mouseX );

                ScratchCtrl.faderMove(1.0 - mouseX / width);
            }
        }

    }*/
}
