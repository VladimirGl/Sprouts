// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    visible: true
    width: 360
    height: 360

    property int numberOfPoints : 0

    Loader { id: pageLoader }

    Rectangle {
        id: rectaa

        color: "black"

        width: parent.width
        height: 40

        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }


    Canvas {
        z : -1

        id: canvas
        anchors {
            left: parent.left
            right: parent.right
            top: rectaa.bottom
            bottom: parent.bottom
            margins: 8
        }
        property int lastX
        property int lastY
        property color color : "#33B5E5"



        onPaint: {
            var ctx = getContext('2d')
            ctx.lineWidth = 1.5
            ctx.strokeStyle = canvas.color
            ctx.beginPath()
            ctx.moveTo(lastX, lastY)
            lastX = area.mouseX
            lastY = area.mouseY

            game.addPoint(lastX, lastY)
            ctx.lineTo(lastX, lastY)
            ctx.stroke()
        }

        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: {
                if (numberOfPoints == 3) {

                    if (parent.childAt(mouseX, mouseY).z == 1) {
                        game.drawStarts(2, parent.childAt(mouseX, mouseY).pointNumber)
                    }

                canvas.lastX = mouseX
                canvas.lastY = mouseY



                } else {

                var component = Qt.createComponent("qrc:///qml/Seed.qml")
                var button = component.createObject(parent)

                button.x = mouseX - button.width / 2
                button.y = mouseY - button.height / 2
                button.pointNumber = numberOfPoints

                }

            }
            onReleased: {
                if (numberOfPoints == 3) {

                    if (parent.childAt(mouseX, mouseY).z == 1) {
                        game.drawEnds(2, parent.childAt(mouseX, mouseY).pointNumber)
                    }
                } else {
                    numberOfPoints++
                }
            }

            onPositionChanged: {
                if (numberOfPoints == 3) {
                canvas.requestPaint()
                }
            }
        }
    }
}
