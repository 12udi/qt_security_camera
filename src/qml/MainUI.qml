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

    Row {

        anchors.fill: parent

        Rectangle {
            id: controls
            width: 300 ; height: parent.height
            border.color: "black"

            Controls {
                anchors.fill: parent
            }
        }

        Rectangle {
            id: camera
            border.color: "black"
            width: parent.width - controls.width - rightBar.width ; height: parent.height

            LiveView {
                anchors.fill: parent
            }
        }

        Rectangle {
            id: rightBar
            width: 200; height: parent.height
            border.color: "black"

            RightBar {
                anchors.fill: parent
            }
        }
    }

    Component.onCompleted: {
        main.showFullScreen();
    }
}



