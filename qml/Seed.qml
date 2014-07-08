import QtQuick 2.0

Rectangle {
    id : point

    z : 1

     width: 20
     height: width
     color: "#1ee422"
     border.color: "black"
     border.width: 1
     radius: width * 0.5

     property int pointNumber : 0

//     MouseArea {
//         id: area
//         anchors.fill: parent
//         onPressed: {
//            game.drawStarts(parent.parent.z, parent.parent.z)
//         }

//         onReleased: {
//             game.drawStarts(parent.y, parent.y)
//         }

//     }
}
