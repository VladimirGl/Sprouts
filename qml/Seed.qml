import QtQuick 2.0

Rectangle {
    id : point
    z : 2

    width: 10
    height: width
    color: colors[lives]
    border.color: "black"
    border.width: 0.5
    radius: width * 0.5

    property int pointNumber: 0
    property int lives: 3
    property variant colors: ["#000000", "#f7070b", "#1ee422", "#1ee422"]

    function isAlive() {
        return (lives > 0)
    }

    function decrLives() {
        if (lives > 0) {
            lives--
        }
    }

    function select() {
        border.width = 2
    }

    function unselect() {
        border.width = 0.5
    }

    function incrLives() {
        if (lives < 3) {
            lives++
        }
    }
}
