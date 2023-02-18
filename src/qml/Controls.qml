import QtQuick 2.0
import QtQuick.Controls 2.0

import "." // adding all qmls in qml folder to project

Item {
    anchors.fill: parent

    readonly property int default_width: 200
    readonly property int default_height: 100

    Item {
        id: videoPath
        anchors { top: parent.top; left: parent.left }
        width: parent.width / 2; height: default_height / 2

        TextField { anchors.centerIn: parent; text: videoStreamer.devPath; cursorVisible: true }
    }

    Item {
        id: screenshotPath
        anchors { top: parent.top; right: parent.right }
        width: parent.width / 2; height: default_height / 2

        TextField { anchors.centerIn: parent; text: videoStreamer.screenshotFolder; cursorVisible: true; enabled: false }
    }

    Item {
        id: detectHeader
        anchors { top: screenshotPath.bottom; left: parent.left; right: parent.right }
        height: 10

        Label { anchors.left: parent.left; anchors.leftMargin: 20; text: qsTr("MOTION DETECTION:") }
    }

    Item {
        id: detectSwitch
        anchors { top: detectHeader.bottom; left: parent.left; right: parent.right }
        width: default_width; height: default_height * 3/4

        CustomSwitch {
            anchors {top: parent.top; topMargin: 10; left: parent.left; leftMargin: 20 }
            property bool backend: false
            textLeft: 'OFF'; textRight: 'ON'
            checked: backend

            onClicked: {
                backend = checked
                videoStreamer.toggleMotion(backend)
            }
        }
    }

    Item {
        id: hardwareHeader
        anchors { top: detectSwitch.bottom; left: parent.left; right: parent.right }
        height: 10

        Label { anchors.left: parent.left; anchors.leftMargin: 20; text: qsTr("CHOOSE DEVICE:") }
    }

    Item {
        id: hardwareSwitch
        anchors { top: hardwareHeader.bottom; left: parent.left; right: parent.right }
        width: default_width; height: default_height * 3/4

        CustomSwitch {
            anchors {top: parent.top; topMargin: 10; left: parent.left; leftMargin: 20 }
            property bool backend: false
            textLeft: 'Pi CAM'; textRight: 'USB CAM'
            enabled: videoStreamer.camEnabled ? false : true
            checked: backend

            onClicked: {
                backend = checked
                videoStreamer.toggleDevice(backend)
            }
        }
    }

    Item {
        id: cameraHeader
        anchors { top: hardwareSwitch.bottom; left: parent.left; right: parent.right }
        height: 10

        Label { anchors.left: parent.left; anchors.leftMargin: 20; text: qsTr("CONNECT CAM:") }
    }

    Item {
        id: cameraSwitch
        anchors { top: cameraHeader.bottom; left: parent.left; right: parent.right }
        width: default_width; height: default_height * 3/4

        CustomSwitch {
            id: camOnline
            anchors {top: parent.top; topMargin: 10; left: parent.left; leftMargin: 20 }
            property bool backend: false
            textLeft: 'OFF'; textRight: 'ON'
            checked: backend

            onClicked: {
                backend = checked
                videoStreamer.toggleConnection(backend)
            }
        }
    }

    Button {
        id: screenshotButton
        anchors { top: cameraSwitch.bottom ; left: parent.left; right: parent.right }
        width: default_width; height: default_height
        text: qsTr("TAKE SCREENSHOT")

        onClicked: {
            videoStreamer.takeScreenshot()
        }
    }

    Button {
        id: clearButton
        anchors { top: screenshotButton.bottom; left: parent.left; right: parent.right }
        width: default_width; height: default_height
        text: qsTr("DELETE SCREENSHOTS")

        onClicked: {
            videoStreamer.clearScreenshotFolder()
        }
    }
}
