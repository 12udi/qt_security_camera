import QtQuick 2.0

Item {
    id: imageRect
    anchors.fill: parent

    Image {
        id: opencvImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        property bool counter: false
        visible: false
        source: "image://live/image"
        asynchronous: false
        cache: false

        function reload() {
            counter = !counter
            source = "image://live/image?id=" + counter
        }
    }

    Connections {
        target: liveImageProvider

        function onImageChanged() {
            opencvImage.reload()
        }
    }
}
