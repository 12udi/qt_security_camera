import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    anchors.fill: parent

    Button {
        id: exit
        anchors { top: parent.top; left: parent.left; right: parent.right }
        height: 100
        onClicked: Qt.quit()
        text: qsTr("EXIT")
    }

    Rectangle
    {
        id: detectRect
        anchors { top: exit.bottom; left: parent.left; right: parent.right; bottom: parent.bottom }
        color: "red"
    }

    Connections {
        target: videoStreamer

        function onRecognizedChanged(yesno) {
            if(true === yesno) {
                detectRect.color = "green"
                videoStreamer.takeScreenshot()
            } else {
                detectRect.color = "red"
            }
        }
    }
}
