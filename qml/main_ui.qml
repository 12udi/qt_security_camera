import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    id: mainWindow
    width: 1024
    height: 600
    visible: true
    title: qsTr("CameraLiveView")

    property int defaultButtonWidth: 200
    property int defaultButtonHeight: 100

    Column {

        anchors.left: parent.left
        anchors.right: imageRect.left

        Switch {
            id: connectCamera
            text: "Camera Status"

            width: defaultButtonWidth
            height: defaultButtonHeight

            onClicked: {
                if (position == 1.0) {
                    opencvImage.visible = true
                    VideoStreamer.openVideoCamera(videoPath.text)
                } else {
                    opencvImage.visible = false
                    VideoStreamer.closeVideoCamera()
                }
            }
        }

        TextField
        {
            id:videoPath
            text: "/dev/video0"

            width: defaultButtonWidth
            height: defaultButtonHeight

            cursorVisible: true
        }

        Switch {
            id: enableMotionDetect
            text: "Motion Detection"

            width: defaultButtonWidth
            height: defaultButtonHeight

            onClicked: {
                if (position == 1.0) {
                    //enable motion detect
                } else {
                    //disable motion detect
                }
            }
        }

        TextField
        {
            id:screenshotPath
            text: "./screenshots"
            width: defaultButtonWidth * 2
            height: defaultButtonHeight / 2
            cursorVisible: true
            enabled: false
        }
    }

    //    Button
    //    {
    //        id: screenshotButton
    //        anchors.top: videoPath.bottom
    //        anchors.left: parent.left
    //        anchors.right: clearButton.left
    //        width: defaultButtonWidth
    //        height: defaultButtonHeight
    //        text: "Screenshot"

    //        onClicked: {
    //            VideoStreamer.takeScreenshot(screenshotPath.text)
    //        }
    //    }

    //    Button
    //    {
    //        id: clearButton
    //        anchors.top: videoPath.bottom
    //        anchors.left: screenshotButton.right
    //        anchors.right: imageRect.left
    //        width: defaultButtonWidth
    //        height: defaultButtonHeight
    //        text: "Clear"

    //        onClicked: {
    //            VideoStreamer.clearScreenshotFolder()
    //        }
    //    }

    //    Button
    //    {
    //        id: clearButton
    //        anchors.top: videoPath.bottom
    //        anchors.left: screenshotButton.right
    //        anchors.right: imageRect.left
    //        width: defaultButtonWidth
    //        height: defaultButtonHeight
    //        text: "Close App"

    //        onClicked: {
    //            VideoStreamer.clearScreenshotFolder()
    //        }
    //    }

    Rectangle
    {
        id: imageRect
        anchors.top: parent.top
        anchors.right: parent.right
        width: 640
        height: 480
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

        //    }

        //    Rectangle
        //    {
        //        id: detectRect
        //        anchors.top: imageRect.bottom
        //        anchors.left: parent.left
        //        anchors.right: parent.right
        //        anchors.bottom: parent.bottom
        //        color: VideoStreamer.recognizedMotion ? "green" : "red"
        //        border.color: "black"
        //        border.width: 3
        //    }

        //    Connections
        //    {
        //        target: liveImageProvider

        //        function onImageChanged()
        //        {
        //            opencvImage.reload()
        //        }

        //    }

        Component.onCompleted: {
            mainWindow.showFullScreen();
        }
    }
}
