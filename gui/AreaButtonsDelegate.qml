//Sailfish Imports
//import QtQuick 2.0
//user interface abstraction layer so both harmattan and sailfish can be supported with the same code base
//import org.flyingsheep.abstractui 1.0

//Android Imports
import QtQuick 2.5
import "../aui"

Rectangle {

    signal clicked();
    property string text
    property bool checked
    property alias pressed: thisButton.pressed
    property color backgroundColor
    color: backgroundColor

    AUIRadioButton {
        id: thisButton
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        //AUIRadoButton is based on TextSwitch widget
        //While TextSwitch offers text property, it does not seem to offer any way of changing the size of the text!!!
        //fontPixelSize: LandedTheme.FontSizeLarge
        text: parent.text
        checked: parent.checked
        platformStyle: greenCheck;
        onClicked: {
            console.log ("text is: " + text)
            console.log("Checked: " + checked)
            parent.clicked();
        }

        GreenCheckButtonStyle { id: greenCheck
        }
    }
}



