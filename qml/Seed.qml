import QtQuick 2.0

Rectangle {
    id : point
    z : 1

    width: 20
    height: width
    color: colors[lives]
    border.color: "black"
    border.width: 1
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
}
