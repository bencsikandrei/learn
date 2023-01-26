import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    width: 800
    height: 640

    Scene {
        id: scene
        anchors.fill: parent

        Tank {
            id: tankPlayer
        }
    }
}
