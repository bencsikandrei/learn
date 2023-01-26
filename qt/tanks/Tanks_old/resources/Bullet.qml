import QtQuick 2.0
import boardItems 1.0

Rectangle {
    id: bullet

    width: 10
    height: width
    color: "grey"

    x: bulletController.posX
    y: bulletController.posY

    property int tankX: 0
    property int tankY: 0
    property int heading: 0

    BulletController {
        id: bulletController
        heading: bullet.heading
        posX: tankX
        posY: tankY

        onObjectHit:
        {
            console.log("Destroying bullet...");
            bullet.destroy();
        }
    }
}
