//Sailfish Imports
//import QtQuick 2.0
//user interface abstraction layer so both harmattan and sailfish can be supported with the same code base
//import org.flyingsheep.abstractui 1.0

//Android Imports
import QtQuick 2.5
import "../aui"

//should be factored out, as Sailfish does not have styles

AUICheckBoxStyle {id: greenCheckButton
    backgroundPressed: "image://theme/color2-meegotouch-button-checkbox-inverted-background-pressed";
    backgroundSelected: "image://theme/color2-meegotouch-button-checkbox-inverted-background-selected";
    backgroundDisabled: "image://theme/color2-meegotouch-button-checkbox-inverted-background-disabled";
}
