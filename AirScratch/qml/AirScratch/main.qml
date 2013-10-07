import QtQuick 2.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        /*onClicked: {
            Qt.quit();
        }*/

        onPressed: {
            ScratchCtrl.scratchStart(mouseX, mouseY);
        }

        onPositionChanged: {
            ScratchCtrl.scratchMove(mouseX, mouseY);
        }

        onReleased: {
            ScratchCtrl.scratchEnd(mouseX, mouseY);
        }
    }
}
