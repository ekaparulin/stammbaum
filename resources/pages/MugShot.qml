import QtQuick 2.0

Rectangle {

    id: page
    color: "lightgray"

    property var fullName: ""
    property var isAlive: false
    property var liveSpan: ""
    property var sex: ""
    property var age: 25
    property var image: ""

    function setImage() {
        if(image =="") {
            if(sex == "") {
                return "/images/persons/unknown.png"
            }

            if(age > 65) {
                return "/images/persons/" + sex + "/mature_0.png"
            }

            if(age > 18) {
                return "/images/persons/" + sex + "/adult_" + Math.floor((Math.random() * 2)) + ".png"
            }

            return "/images/persons/" + sex + "/child_" + Math.floor((Math.random() * 2)) + ".png"
        }
        return image;
    }

/*
    MouseArea {
        anchors.fill: parent

        onPressAndHold: {
                parent.color = 'blue';
        }
        onExited: {
                parent.color = 'lightgray';
        }
    }
    /*onClicked: optionsMenu.open()

    Menu {
        id: optionsMenu
        x: parent.width - width
        transformOrigin: Menu.TopRight

        MenuItem {
            text: "Settings"
            onTriggered: settingsDialog.open()
        }
        MenuItem {
            text: "About"
            onTriggered: aboutDialog.open()
        }
    }
    */


    Image {
        width: parent.width
        height: parent.height
        source: setImage()
        anchors.horizontalCenter: page.horizontalCenter
        anchors.verticalCenter: page.verticalCenter
    }
    Canvas {
        id: sorrowBand
        width: parent.width
        height: parent.height
//        y: parent.top

        visible: !isAlive

        onPaint: {
            var ctx = getContext("2d");
            ctx.fillStyle = Qt.rgba(0, 0, 0, 1);
            ctx.strokeStyle = Qt.rgba(1, 1, 1, 1);
            ctx.beginPath();
            ctx.moveTo(width * 0.5, height);
            ctx.lineTo(width, height * 0.5);
            ctx.lineTo(width, height * 0.75);
            ctx.lineTo(width * 0.75, height);
            ctx.fill();
            ctx.stroke();
        }
    }

    Text {
        id: fullName
        text: parent.fullName

        font.bold : true


        anchors.horizontalCenter: page.horizontalCenter
        anchors.top: page.bottom
        anchors.margins: 10
        wrapMode: Text.WordWrap
    }
    Text {
        id: lifeSpan
        text: parent.liveSpan
        anchors.horizontalCenter: page.horizontalCenter
        anchors.top: fullName.bottom
        anchors.margins: 10
        wrapMode: Text.WordWrap
    }

}
