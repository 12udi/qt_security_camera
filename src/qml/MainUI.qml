import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

import "." // adding all qmls in qml folder to project

Window {
    id: main
    visible: true
    title: qsTr("DAT CAM")

    //needed for desktop build!
    width: 1280
    height: 720

    readonly property int default_width: 200
    readonly property int default_height: 100

    Item {
        id: topBar
        anchors { top: parent.top; left: controls.right; right: parent.right }
        height: default_height / 4

        TopBar {
            anchors.fill: parent
        }
    }

    Rectangle {
        id: controls
        anchors { top: parent.top; left: parent.left; bottom: parent.bottom }
        width: parent.width - camera.width
        border.color: "black"

        Controls {
            anchors.fill: parent
        }
    }

    Rectangle {
        id: camera
        anchors { top: topBar.bottom; right: parent.right}
        border.color: "black"
        width: 960; height: 540

        LiveView {
            anchors.fill: parent
        }
    }
}



