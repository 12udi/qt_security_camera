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
        anchors { top: exit.bottom; left: parent.left; right: parent.right }
        height: 100
        color: videoStreamer.recognized ? "green" : "red"
    }

    Rectangle
    {
        id: frameRect
        anchors { top: detectRect.bottom; left: parent.left; right: parent.right }
        height: 30

        Label {
            anchors.centerIn: parent
            font.pixelSize: 0.5 * frameRect.height
            text: videoStreamer.averageFps
        }

        color: videoStreamer.recognized ? "green" : "red"
    }
}
