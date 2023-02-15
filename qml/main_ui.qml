import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    id: main
    visible: true
    title: qsTr("CameraLiveView")

    property int defaultButtonWidth: 160
    property int defaultButtonHeight: 80

    Button
    {
        id: startButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: closeButton.left
        width: defaultButtonWidth
        height: defaultButtonHeight
        text: "Open"

        onClicked: {
            VideoStreamer.openVideoCamera(videoPath.text)
            opencvImage.visible = true
        }
    }

    Button
    {
        id: closeButton
        anchors.top: parent.top
        anchors.left: startButton.right
        anchors.right: imageRect.left
        width: defaultButtonWidth
        height: defaultButtonHeight
        text: "Close"

        onClicked: {
            VideoStreamer.closeVideoCamera()
            opencvImage.visible = false
        }
    }

    Button
    {
        id: screenshotButton
        anchors.top: videoPath.bottom
        anchors.left: parent.left
        anchors.right: clearButton.left
        width: defaultButtonWidth
        height: defaultButtonHeight
        text: "Screenshot"

        onClicked: {
            VideoStreamer.takeScreenshot(screenshotPath.text)
        }
    }

    Button
    {
        id: clearButton
        anchors.top: videoPath.bottom
        anchors.left: screenshotButton.right
        anchors.right: imageRect.left
        width: defaultButtonWidth
        height: defaultButtonHeight
        text: "Clear"

        onClicked: {
            VideoStreamer.clearScreenshotFolder()
        }
    }

    TextField
    {
        id:videoPath
        anchors.top: startButton.bottom
        anchors.left: parent.left
        anchors.right: imageRect.left
        text: "/dev/v4l"
        width: defaultButtonWidth * 2
        height: defaultButtonHeight / 2
        cursorVisible: true
    }

    TextField
    {
        id:screenshotPath
        anchors.top: screenshotButton.bottom
        anchors.left: parent.left
        anchors.right: imageRect.left
        text: "./screenshots"
        width: defaultButtonWidth * 2
        height: defaultButtonHeight / 2
        cursorVisible: true
        enabled: false
    }

    Rectangle
    {
        id: imageRect
        anchors.top: parent.top
        anchors.right: parent.right
        width: 1280
        height: 720
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

    Rectangle
    {
        id: detectRect
        anchors.top: imageRect.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: VideoStreamer.m_RecognizedMotion ? "green" : "red"
        border.color: "black"
        border.width: 3
    }

    Connections
    {
        target: liveImageProvider

        function onImageChanged()
        {
            opencvImage.reload()
        }

    }

    Component.onCompleted: {
        main.showFullScreen();
    }
}
