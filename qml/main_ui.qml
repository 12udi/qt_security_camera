import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("CameraLiveView")

    Rectangle
    {
        id: imageRect
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 320
        height: 240

        color: "transparent"
        border.color: "black"
        border.width: 3

        Image
        {
            id: opencvImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            property bool counter: false
            visible: false
            source: "image://live/image"
            asynchronous: false
            cache: false

            function reload()
            {
                counter = !counter
                source = "image://live/image?id=" + counter
            }
        }
    }

    Button
    {
        id: startButton
        x: imageRect.x/2 - startButton.width/2
        y: imageRect.height/6 + imageRect.y
        text: "Open"

        onClicked: {
            VideoStreamer.openVideoCamera(videoPath.text)
            opencvImage.visible = true
        }
    }

    Button
    {
        id: closeButton
        anchors.top: startButton.top
        anchors.left: startButton.right
        width: startButton.width
        text: "Close"

        onClicked: {
            VideoStreamer.closeVideoCamera()
            opencvImage.visible = false
        }
    }

    Button
    {
        id: screenshotButton
        anchors.top: startButton.bottom
        anchors.left: startButton.left
        anchors.right: startButton.right

        text: "Screenshot"

        onClicked: {
            VideoStreamer.takeScreenshot()
        }
    }

    TextField
    {
        id:videoPath
        text: "/dev/video0"
        x: startButton.x - startButton.width
        y: startButton.y + startButton.height * 2
        placeholderText: "Video Path or Video Index"
        cursorVisible: true

        width: startButton.width * 3
    }

    Connections
    {
        target: liveImageProvider

        function onImageChanged()
        {
            opencvImage.reload()
        }
    }
}
