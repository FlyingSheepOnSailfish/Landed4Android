import QtQuick 2.5
import QtQuick.Controls 1.4
import AUI 1.0

Item {

    id: thisPage
    objectName: "thisPage"
    property Item tools: null;
    property int orientationLock: AUIPageOrientation.Automatic
    property alias menuitems: menuModel.children
    property color backgroundColor;
    property bool showNavigationIndicator;
    property bool backNavigation
    property int status: AUIPageStatus.Inactive;

    //not sure if we actually need these signals, it may be enough to pass on the menu.active property via alias
    //the stuff I am doing via the internal signal handlers could be done from onActiveChanged
    signal menuOpening()
    signal menuClosing()


    Item { id: menuModel; objectName: "menuModel"; }

    MenuBar {
        Menu {
            id: thisMenu
            objectName: "thisMenu"

            //Harmattan has MenuLayout here as child of Menu, parent of Repeater, Silica does not.
            Repeater {
                objectName: "repeater"
                model: menuModel.children
                MenuItem {
                    objectName: "menuItem"
                    text: modelData.text
                    onTriggered: {
                        console.log ("Menu active: " + thisMenu.active);
                        modelData.clicked();
                    }
                }
            }
            //Qt5.5 maybe aboutToShow / aboutToHide can be used here?
            //            onActiveChanged: {
            //                (thisMenu.active == true) ? thisPage.menuOpening() : thisPage.menuClosing();
            //            }
        }

    }

    //Indicate to the instance of the Page if a Menu is present, and the type of menu
    property int hasMenu: (menuitems.length > 0) ? 3 : 0
    //TODO Add a C++ enum for these values
    //0: no menu
    //1: Harmattan style toolbar pullup Menu
    //2: Sailfish PullDownMenu
    //3: Sailfish PushUpMenu

    NumberAnimation {
        id: fadeChilds
        properties: "opacity"
        to: 0.2
        duration: 500
    }

    NumberAnimation {
        id: unFadeChilds
        properties: "opacity"
        to: 1
        duration: 500
    }

    onMenuOpening: {
        console.log ("AUI Menu is opening: thisMenu height: " + thisMenu.height + " _activeHeight: " + thisMenu._activeHeight)
        //Ok at this point we are opening, but the height is still 0,
        //but the internal propery _activeHeight does give us a positive value
        //thisPage.children[i].opacity = thisPage.children[i].opacity / 10;
        fadeChilds.targets = setChildsToFade();
        fadeChilds.start();
    }
    onMenuClosing: {
        console.log ("AUI Menu is closing: thisMenu height: " + thisMenu.height);
        //thisPage.children[i].opacity = thisPage.children[i].opacity * 10;
        unFadeChilds.targets = setChildsToFade();
        unFadeChilds.start();
    }

    //in theory we could call this just on menuOpening:, store in a variable
    //and just reuse the varible on closing, thereby only unFading the same objects
    //and saving a loop around the ojbects
    function setChildsToFade() {
        var childsToFade = [];
        for(var i = 0; i < thisPage.children.length; i++) {
            if (thisPage.children[i].objectName != menuListView.objectName) {
                //thisPage.children[i].opacity = thisPage.children[i].opacity * 10;
                childsToFade.push(thisPage.children[i])
            }
        }
        return childsToFade;
    }

}

