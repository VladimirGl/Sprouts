import QtQuick 2.0

Rectangle {
    id : point

     width: 20
     height: width
     color: "#1ee422"
     border.color: "black"
     border.width: 1
     radius: width * 0.5

     property int pointNumber

//     MouseArea {
//         id: area
//         anchors.fill: parent
//         onPressed: {
//             canvas.lastX = parent.width / 2
//             canvas.lastY = parent.height / 2
//         }
//         onReleased: {
//             if (contains(Qt.point(mouseX, mouseY))) {
//                game.drawEnds(10, 10) }
//         }

//         onPositionChanged: {
//             canvas.requestPaint()
//         }
//     }
}
