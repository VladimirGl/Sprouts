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
    8 - waitTurn
*/

Window {
    width: 640
    height: 960

    id: field

    visible: true

    property int numberOfPoints: 0

    property int state: 0

    Connections {
        target: game
        onTurnEndss: {
            if (!game.turnResult()) {
                canvas.undo()
            }
            field.setState(3)
//            console.log(field.state)
            game.clear()
        }
    }


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
        case 8:
            break
        }
    }

    Rectangle {
        id: rect

        color: "black"

        width: parent.width
        height: 20

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (field.state != 2) {
                    field.setState(1)
                } else {
                    field.setState(3)
                    game.startGame(canvas.width, canvas.height)
                }
            }
        }
    }

    Canvas {
        z : -1

        width: parent.width
        height: parent.height - rect.height

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

        property var firstVertex
        property var secondVertex
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
            firstVertex.incrLives()
//            console.log(field.state)
            if (field.state == 8) {
                secondVertex.incrLives()
                children[children.length - 1].destroy()
            }

            isImageDrawed = false
            loadImage(lastView)
            imageLoaded()
            game.clear()
        }

        function createPoint(x, y) {
            var component = Qt.createComponent("qrc:///qml/Seed.qml")
            var seed = component.createObject(canvas)

            seed.width = Math.round(canvas.width / 20)

            seed.x = Math.round(x - seed.width / 2)
            seed.y = Math.round(y - seed.height / 2)
            seed.pointNumber = field.numberOfPoints

            return seed
        }

        function addInitPoint(x, y) {
            createPoint(x, y)
            game.addInitialPoint(x, y)

            field.numberOfPoints++
        }

        function addPoint(x, y) {
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
//            ctx.strokeStyle = "#33B5E5"
            ctx.strokeStyle = "black"
            ctx.beginPath()
            ctx.moveTo(lastX, lastY)

            if (isIntersected(ctx, lastX, lastY, newX, newY) && field.state != 5 && field.state != 6) {
                return
            }

            lastX = newX
            lastY = newY

            game.addPoint(Math.round(lastX), Math.round(lastY))
            ctx.lineTo(lastX, lastY)
            ctx.stroke()

            ctx.closePath()
        }

        onImageLoaded: {
            requestPaint()
        }

        MouseArea {
            id: area
            anchors.fill: parent

            property var visitedVertex
            property int visited: 0

            onPressed: {
//                console.log(field.state)

                switch (field.state) {
                case 2:
//                    console.log(mouseX, mouseY)
                    parent.addInitPoint(Math.round(mouseX), Math.round(mouseY))
                    break
                case 3:
                    var ch = parent.childAt(mouseX, mouseY)

                    if (ch.z != 2) {
                        break
                    }

                    if (!ch.isAlive()) {
                        break
                    }

                    canvas.lastView = canvas.toDataURL()

                    game.drawStarts(2, ch.pointNumber)
                    ch.decrLives()

                    canvas.lastX = Math.round(ch.x + ch.width / 2)
                    canvas.lastY = Math.round(ch.y + ch.height / 2)
//                    console.log(canvas.lastX, canvas.lastY)

                    game.addPoint(Math.round(canvas.lastX), Math.round(canvas.lastY))

                    visitedVertex = ch
                    canvas.firstVertex = ch

                    field.setState(4)
                    break
                case 6:
                    var point = game.nearestPoint(mouseX, mouseY)
                    field.setState(8)
                    parent.addPoint(point.x, point.y)

                    game.addVertex(point.x, point.y)
                }
            }

            onReleased: {

                if (field.state == 4) {
                    if (parent.childAt(mouseX, mouseY).z == 2) {

                        var ch = parent.childAt(mouseX, mouseY)

                        if (!ch.isAlive()) {
                            canvas.undo()
                            field.setState(3)
                            return
                        }

                        if ((visited != 1) && (ch != canvas.firstVertex && visited != 2)) {
                        }

                        visited = 0

                        canvas.newX = Math.round(ch.x + ch.width / 2)
                        canvas.newY = Math.round(ch.y + ch.height / 2)
//                        console.log(canvas.newX, canvas.newY)


                        game.addPoint(canvas.newX, canvas.newY)

                        field.setState(5)
                        canvas.requestPaint()
                        canvas.secondVertex = ch

                        game.drawEnds(ch.pointNumber, canvas.firstVertex.pointNumber)
                        ch.decrLives()
                        ch.unselect()
                    } else {
                        canvas.undo()
                        field.setState(3)
                    }
                }
            }

            onPositionChanged: {
                if (field.state == 4) {
                    var ch = parent.childAt(mouseX, mouseY)

                    if (ch.z == 2) {
                        if (ch != canvas.firstVertex && ch != visitedVertex) {
                            visitedVertex.unselect()
                            ch.select()
                            visited++
                            visitedVertex = ch
                        }

                        return
                    }

                    visitedVertex.unselect()

                    canvas.requestPaint()

                    canvas.newX = Math.round(mouseX)
                    canvas.newY = Math.round(mouseY)
                }
            }
        }
    }
}
