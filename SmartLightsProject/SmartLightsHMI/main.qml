import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.0
import QtGraphicalEffects 1.0



ApplicationWindow 
{
    id: mainWindow
    visible: true
    width: 1024
    height: 600
    
    signal turnOnSignal()
    signal turnOffSignal()
    signal setColSignal(int colour)
    signal setBrigSignal(int bright)
    signal setWhiteSignal()
    signal setAutoDimming(int enabled)
    signal setMinimumLuxVal(int val)

    SystemPalette { id: activePalette }
    
    Rectangle
    {
        id: mainWindowRectangle
        anchors.fill: parent
        Item
        {
            anchors.fill: parent
            Image
            {
                id: background
                x: 0
                y: 0
                fillMode: Image.Tile
                anchors.fill: mainWindow
                anchors.centerIn: mainWindow
                smooth: true
                source: "img/Img2.jpg"
                
                visible: true

                Button
                {
                    id: button1
                    x: 113
                    y: 516
                    width: 313
                    height: 67
                    text: qsTr("")
                    checkable: false
                    activeFocusOnPress: true

                    onClicked:
                    {
                        setAutoDimming(1)
                    }

                    Text {
                        id: turnReset1
                        width: 203
                        height: 31
                        color: "#008df9"
                        text: qsTr("Auto dimming")
                        horizontalAlignment: Text.AlignHCenter
                        anchors.verticalCenterOffset: 0
                        anchors.horizontalCenterOffset: -50
                        elide: Text.ElideMiddle
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                        font.pointSize: 16
                        font.family: "MV Boli"
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: turnReset2
                        x: 8
                        y: 0
                        width: 91
                        height: 45
                        color: "#215600"
                        text: qsTr("ON")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideMiddle
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                        font.pointSize: 20
                        font.family: "MV Boli"
                        anchors.horizontalCenterOffset: 103
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 0
                    }
                }

                Button {
                    id: button2
                    x: 432
                    y: 516
                    width: 306
                    height: 67
                    text: qsTr("")
                    activeFocusOnPress: true

                    onClicked:
                    {
                        setAutoDimming(0)
                    }

                    Text {
                        id: turnReset3
                        width: 191
                        height: 31
                        color: "#008df9"
                        text: qsTr("Auto dimming")
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideMiddle
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                        font.pointSize: 16
                        font.family: "MV Boli"
                        anchors.horizontalCenterOffset: -52
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 2
                    }

                    Text {
                        id: turnReset4
                        x: 8
                        y: 0
                        width: 91
                        height: 45
                        color: "#c20101"
                        text: qsTr("OFF")
                        elide: Text.ElideMiddle
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                        font.pointSize: 20
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "MV Boli"
                        anchors.horizontalCenterOffset: 94
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 0
                    }
                    checkable: false
                }

                Slider {
                    id: sliderHorizontal1
                    x: 744
                    y: 516
                    width: 180
                    height: 67
                    minimumValue: 10
                    value: 10
                    maximumValue: 300
                    activeFocusOnPress: false
                    tickmarksEnabled: false

                    onValueChanged:
                    {
                        label1.text = parseInt(sliderHorizontal1.value, 10)
                        setMinimumLuxVal(parseInt(sliderHorizontal1.value, 10))
                    }
                }

                Label {
                    id: label1
                    x: 938
                    y: 521
                    width: 81
                    height: 57
                    color: "#100101"
                    text: qsTr("10")
                    styleColor: "#000000"
                    style: Text.Normal
                    font.pointSize: 27
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        ColorDialog
        {
            id: colorDialog
            title: "Please choose a color"

            onAccepted:
            {
                console.log("You chose: " + colorDialog.color)
                setColSignal(colorDialog.color)
            }
            onRejected:
            {
                console.log("Canceled")
            }
        }
        
        Rectangle 
        {
            id: toolBar
            width: parent.width; height: 50
            color: "#96e5ec"
            anchors.bottom: mainWindow.bottom
            visible: true
            radius: 10
            opacity: .5
            gradient: Gradient {
                GradientStop {
                    position: 0.14;
                    color: "#000000";
                }
                GradientStop {
                    position: 1.00;
                    color: "#ffffff";
                }
            }
            
            Rectangle
            {
                id: buttonArea
                width: parent.width / 5
                height: parent.height
                radius: 20
                anchors 
                { 
                    left: parent.left + 5; 
                    verticalCenter: parent.verticalCenter                
                }
                
                Button  
                {
                    anchors.fill: parent
                    visible: true
                    Text 
                    {
                        id: name
                        anchors
                        {
                            verticalCenter: parent.verticalCenter 
                            horizontalCenter : parent.horizontalCenter
                        }
                        text: qsTr("Set colour")
                        font.family: "MV Boli"
                        font.bold: true
                        color: "#008df9"
                        font.pointSize: 20
                        elide: Text.ElideMiddle
                    }
                    onClicked:
                    {
                        colorDialog.open()
                    }
                }
            }
        
            Rectangle
            {
                id: buttonXArea
                width: parent.width / 5
                height: parent.height
                radius: 20
                anchors 
                { 
                    right: parent.right + 5; 
                    verticalCenter: parent.verticalCenter                
                }
                x: parent.width - width
                
                Button  
                {
                    anchors.fill: parent
                    visible: true
                    Text 
                    {
                        id: exit
                        anchors
                        {
                            verticalCenter: parent.verticalCenter 
                            horizontalCenter : parent.horizontalCenter
                        }
                        text: qsTr("X")
                        font.family: "MV Boli"
                        font.bold: true
                        color: "#008df9"
                        font.pointSize: 30
                        elide: Text.ElideMiddle
                }
                    onClicked: Qt.quit()
                }
            }            
            
            Rectangle
            {
                id: toolBarBottom
                anchors.top: parent.bottom
                width: parent.width
                height: 10
                radius: 10
                
                BorderImage 
                {
                    id: imgBottom
                    source: "img/bottomBar.jpg"
                    border.left: 2; border.top: 2
                    anchors.fill: parent
                }
            }            
        }
        
        Rectangle
        {
            id: buttonsArea
            width: 800
            height: 173
            y: 68
            anchors
            {
                horizontalCenter: parent.horizontalCenter
            }
            opacity: 0.7
            radius: 30
            anchors.horizontalCenterOffset: 0

            gradient: Gradient {
                GradientStop {
                    position: 0.00;
                    color: "#cae8f1";
                }
                GradientStop {
                    position: 1.00;
                    color: "#1519e6";
                }
            }

            Row
            {
                width: 3* turnOnButton.width + 2*30
                height: parent.height -30
                anchors
                {
                    horizontalCenter : parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                spacing: 30

                Button
                {
                    id: turnOnButton
                    width: 200
                    height: 150
                    visible: true
                    anchors.verticalCenter: parent.verticalCenter

                    Text
                    {
                        id: turnOn
                        anchors
                        {
                            verticalCenter: parent.verticalCenter
                            horizontalCenter : parent.horizontalCenter
                        }
                        text: qsTr("Turn On")
                        font.family: "MV Boli"
                        font.bold: true
                        color: "#008df9"
                        font.pointSize: 20
                        elide: Text.ElideMiddle
                    }
                    onClicked: turnOnSignal()
                }

                Button
                {
                    id: turnOffButton
                    width: 200
                    height: 150
                    visible: true
                    anchors.verticalCenter: parent.verticalCenter

                    Text
                    {
                        id: turnOff
                        anchors
                        {
                            verticalCenter: parent.verticalCenter
                            horizontalCenter : parent.horizontalCenter
                        }
                        text: qsTr("Turn Off")
                        font.family: "MV Boli"
                        font.bold: true
                        color: "#008df9"
                        font.pointSize: 20
                        elide: Text.ElideMiddle
                    }
                    onClicked: turnOffSignal()
                }

                Button
                {
                    id: turnResetButton
                    width: 200
                    height: 150
                    visible: true
                    anchors.verticalCenter: parent.verticalCenter

                    Text
                    {
                        id: turnReset
                        anchors
                        {
                            verticalCenter: parent.verticalCenter
                            horizontalCenter : parent.horizontalCenter
                        }
                        text: qsTr("Reset colour")
                        font.family: "MV Boli"
                        font.bold: true
                        color: "#008df9"
                        font.pointSize: 20
                        elide: Text.ElideMiddle
                    }
                    onClicked: setWhiteSignal()
                }
            }
        }

        Rectangle
        {
            id: colorsArea
            width: 800
            height: 140
            y: 247
            anchors
            {
                horizontalCenter: parent.horizontalCenter
            }
            opacity: 0.7
            radius: 30
            anchors.horizontalCenterOffset: 0
            border.color: "#b7c4d3"
            gradient: Gradient {
                GradientStop {
                    position: 0.00;
                    color: "#cae8f1";
                }
                GradientStop {
                    position: 1.00;
                    color: "#1519e6";
                }
            }

            Row
            {
                spacing: 10
                anchors
                {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                PropertyAnimation
                {
                    id: animateSize;
                    //targets: [rViolet, rBlue, rAqua, rGreen, rOrange, rPink, rRed, rYellow]
                    properties: "scale";
                    from: 2
                    to: 1;
                    duration: 500
                    easing.type: Easing.InBack
                }

                Rectangle
                {
                    id: rViolet
                    width: 80; height: 80; color: "violet"; radius: 10; opacity: 1
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(0); animateSize.target = rViolet; animateSize.start() }
                    }
                }
                Rectangle
                {
                    id: rBlue
                    width: 80; height: 80; color: "blue"; radius: 10; opacity: 1
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(0); animateSize.target = rBlue; animateSize.start() }
                    }
                }
                Rectangle
                {
                    id: rAqua
                    width: 80; height: 80; color: "Aqua"; radius: 10; opacity: 1
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(48); animateSize.target = rAqua; animateSize.start() }
                    }
                }
                Rectangle
                {
                    id: rGreen
                    width: 80; height: 80; color: "Green"; radius: 10; opacity: 1
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(96); animateSize.target = rGreen; animateSize.start()}
                    }
                }
                Rectangle
                {
                    id: rYellow
                    width: 80; height: 80; color: "Yellow"; radius: 10; opacity: 1
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(128); animateSize.target = rYellow; animateSize.start() }
                    }
                }
                Rectangle
                {
                    id: rOrange
                    width: 80; height: 80; color: "Orange"; radius: 10; opacity: 1
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(160); animateSize.target = rOrange; animateSize.start() }
                    }
                }
                Rectangle
                {
                    id: rRed
                    width: 80; height: 80; color: "Red"; radius: 10; opacity: 1; visible: true
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(176); animateSize.target = rRed; animateSize.start() }
                    }
                }
                Rectangle
                {
                    id: rPink
                    width: 80; height: 80; color: "Pink"; radius: 10; opacity: 1
                    MouseArea
                    {
                            anchors.fill: parent
                            onClicked: { setColSignal(192); animateSize.target = rPink; animateSize.start() }
                    }
                }
            }
        }

        Rectangle
        {
            id: sliderArea
            y: 405
            width: 822
            height: 100
            anchors 
            {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin:95
            }
            opacity: 0.7
            radius: 30
            anchors.horizontalCenterOffset: 11

            gradient: Gradient {
                GradientStop {
                    position: 0.00;
                    color: "#ffffff"
                }
                GradientStop {
                    position: 1.00;
                    color: "#1519e6";
                }
            }
            
            Text 
            {
                id: sliderText
                text: qsTr("Brightness")
                font.family: "MV Boli"
                font.bold: true
                color: "#008df9"
                font.pointSize: 20
                elide: Text.ElideMiddle
                anchors 
                {
                    horizontalCenter: parent.horizontalCenter
                }
            }
            
            Slider
            {
                id: slider
                width: 600
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.fill: parent
                value: 100
                onValueChanged: 
                {
                    setBrigSignal(value * 100)
                }
            }
        }        
    }
}
