import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    anchors.fill: parent

    Rectangle
    {
        id: detectRect
        anchors {
            top: parent.top;
            left: parent.left; leftMargin: 20;
            right: exit.left; rightMargin: 20;
            bottom: parent.bottom
        }
        color: VideoStreamer.recognized ? "green" : "red"
    }

    Button {
        id: exit
        anchors { top: parent.top; right: parent.right; bottom: parent.bottom}
        onClicked: Qt.quit()
        text: qsTr("EXIT")
    }
}
