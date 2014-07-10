// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

import QtQuick 2.2
import QtQuick.Window 2.1

/*
  States:
    0 - init
    1 - start new game
    2 - set points
    3 - game starts
    4 - line draw starts
    5 - line draw ends
    6 - set new point
    7 - game ends
*/

Window {
    id: field

    visible: true
    width: 360
    height: 360

    property int numberOfPoints: 0

    property int state: 0

    function setState(newState) {
        state = newState
        mStateChanged()
    }

    function mStateChanged() {
        switch (state) {
        case 0:
            setState(1)
            break
        case 1:
            canvas.clear()
            canvas.init()
            setState(2)
            break
        case 2:
            break
        case 3:
            break
        case 4:
            break
        case 5:
            setState(6)
            break
        case 6:
            break
        case 7:
            break
        }
    }

    Rectangle {
        id: rect

        color: "black"

        width: parent.width
        height: 40

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (field.state != 2) {
                    field.setState(1)
                } else {
                    field.setState(3)
                }
            }
        }
    }

    Canvas {
        z : -1

        id: canvas
        anchors {
            left: parent.left
            right: parent.right
            top: rect.bottom
            bottom: parent.bottom
            margins: 8
        }


        property int lastX: 0
        property int lastY: 0

        property int newX: 0
        property int newY: 0

        property color backgroundColor: "#ffffff"

        property var lastVertex
        property var lastView
        property bool isImageDrawed: false

        function init() {
            var ctx = getContext('2d')

            ctx.fillStyle = backgroundColor

            ctx.fillRect(0, 0, width, height)

            lastView = canvas.toDataURL()
        }

        function clear() {
            var ctx = getContext('2d')
            ctx.clearRect(0, 0, width, height)

            for (var i = children.length; i > 1; i--) {
                children[i - 1].destroy()
            }

            state = 0
            numberOfPoints = 0
        }

        function undo() {
            lastVertex.incrLives()
            isImageDrawed = false
            console.log("pshh")
            loadImage(lastView)
            imageLoaded()
            game.clear()

            console.log("undoend")
        }

        function createPoint(x, y) {
            var component = Qt.createComponent("qrc:///qml/Seed.qml")
            var button = component.createObject(canvas)

            button.x = x - button.width / 2
            button.y = y - button.height / 2
            button.pointNumber = field.numberOfPoints

            return button
        }

        function addInitPoint(x, y) {
            console.log("add init point")

            createPoint(x, y)

            field.numberOfPoints++
        }

        function addPoint(x, y) {
            console.log("add new point")

            var button = createPoint(x, y)
            button.decrLives()
            button.decrLives()

            field.numberOfPoints++
        }

        function isBackground(r, g, b, a) {
            return (backgroundColor.toString() == Qt.rgba(r, g, b, a).toString())
        }

        function isIntersected(ctx, lastX, lastY, newX, newY) {

            var diff = 3

            var sx = lastX <= newX ? 2 : -diff - 2
            var sy = lastY <= newY ? 2 : -diff - 2

            var c = ctx.getImageData(lastX + sx,
                                     lastY + sy,
                                     diff,
                                     diff).data

            for (var i = 0; i < c.length; i += 4) {
                if (!isBackground(c[i + 0] / 255, c[i + 1] / 255,
                                  c[i + 2] / 255, c[i + 3] / 255)) {
                    return true
                }
            }

            return false
        }

        onPaint: {
            var ctx = getContext('2d')

            if (isImageLoaded(lastView) && !isImageDrawed) {
                ctx.drawImage(lastView, 0, 0)
                isImageDrawed = true
                return
            }

//            ctx.clearRect(0, 0, 300, 300)
            ctx.lineWidth = 2
            ctx.strokeStyle = "#33B5E5"
            ctx.beginPath()
            ctx.moveTo(lastX, lastY)

            if (isIntersected(ctx, lastX, lastY, newX, newY) && field.state != 5 && field.state != 6) {
                return
            }

            lastX = newX
            lastY = newY

            game.addPoint(lastX, lastY)
            ctx.lineTo(lastX, lastY)
            ctx.stroke()

            ctx.closePath()
        }

        onImageLoaded: {
//            console.log("imgg")

            requestPaint()

//            var ctx = getContext('2d')
//            ctx.beginPath()

//            ctx.clearRect(0, 0, width, height)
//            ctx.drawImage(lastView, 0, 0)

//            ctx.closePath()

//            console.log("imageloaded")
        }

        MouseArea {
            id: area
            anchors.fill: parent

            onPressed: {
                switch (field.state) {
                case 2:
                    console.log("state 2")
                    parent.addInitPoint(mouseX, mouseY)
                    break
                case 3:
                    var ch = parent.childAt(mouseX, mouseY)

                    if (ch.z != 1) {
                        break
                    }

                    if (!ch.isAlive()) {
                        break
                    }

                    console.log("line start")
                    canvas.lastView = canvas.toDataURL()

                    game.drawStarts(2, ch.pointNumber)
                    ch.decrLives()

                    canvas.lastX = ch.x + ch.width / 2
                    canvas.lastY = ch.y + ch.height / 2

                    canvas.lastVertex = ch

                    field.setState(4)
                    break
                case 6:
                    var point = game.nearestPoint(mouseX, mouseY)
                    parent.addPoint(point.x, point.y)

                    game.clear()
                    field.setState(3)
                }
            }

            onReleased: {
                console.log(field.state)

                if (field.state == 4) {
                    if (parent.childAt(mouseX, mouseY).z == 1) {
                        console.log("finish")

                        var ch = parent.childAt(mouseX, mouseY)

                        if (!ch.isAlive()) {
                            console.log("bad finish")
                            canvas.undo()
                            field.setState(3)
                            return
                        }

                        canvas.newX = ch.x + ch.width / 2
                        canvas.newY = ch.y + ch.height / 2

                        field.setState(5)
                        canvas.requestPaint()

                        game.drawEnds(2, ch.pointNumber)
                        ch.decrLives()
                    } else {
                        console.log("bad finish")
                        canvas.undo()
                        field.setState(3)
                    }
                }
            }

            onPositionChanged: {
                if (field.state == 4) {
                    var ch = parent.childAt(mouseX, mouseY)

                    if (ch.z == 1) {
                        return
                    }

                    canvas.requestPaint()

                    canvas.newX = mouseX
                    canvas.newY = mouseY
                }
            }
        }
    }
}
