import QtQuick 2.0
import boardItems 1.0

Item {
    id: tank

    width: 25
    height: 25
    x: tankController.posX
    y: tankController.posY
    focus: true
    transformOrigin: Item.Center

    // properties
    property int heading: 0

    Rectangle {
        id: tankTop
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: 10
        height: tank.height / 2
        color: "blue"
    }

    Rectangle {
        id: tankBottom
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height - tankTop.height
        color: "blue"
    }

    TankController {
        id: tankController
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Left) {
            event.accepted = true;
            tankController.moveLeft();
            heading = CommonDefs.V;
        }
        if (event.key === Qt.Key_Right) {
            event.accepted = true;
            tankController.moveRight();
            heading = CommonDefs.E;
        }
        if (event.key === Qt.Key_Up) {
            event.accepted = true;
            tankController.moveUp();
            heading = CommonDefs.N;
        }
        if (event.key === Qt.Key_Down) {
            event.accepted = true;
            tankController.moveDown();
            heading = CommonDefs.S;
        }
        if (event.key === Qt.Key_Space) {
            event.accepted = true;

            var component = Qt.createComponent('Bullet.qml');

            if (component.status === Component.Ready) {
                var bullet = component.createObject(scene,
                                                    {
                                                        "tankX": tank.x + tank.width / 4,
                                                        "tankY": tank.y,
                                                        "heading" : tank.heading
                                                    });
            }
        }
    }

    onHeadingChanged: {
        tank.rotation = tank.heading;
    }
}
