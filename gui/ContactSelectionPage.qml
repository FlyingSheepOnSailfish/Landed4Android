//Sailfish Imports
//import QtQuick 2.0
//user interface abstraction layer so both harmattan and sailfish can be supported with the same code base
//import org.flyingsheep.abstractui 1.0

//Android Imports
import QtQuick 2.5
import AUI 1.0
import "../aui"

import QtQuick.Controls 1.4


//gives access to contacts (landed favourites, dialer, phone contacts)

AUIPage {id: pageContactSelection

    property string area_id
    property string template_id

    //width: 480
    //height: 828
    //height: 740
    orientationLock: AUIPageOrientation.LockPortrait
    //don't show / enable the pagestack indicator on the contactsTab.
    backNavigation: tabGroup.currentTab == contactsTab ? false : true
    showNavigationIndicator: backNavigation

    property int toolbarHeight: 0
    //property int toolbarHeight: 110
    backgroundColor: "lightgrey"
    property int itemHeight: 100;
    property int headerHeight: itemHeight;
    property int fontPixelSize: 30
    property color labelColorActive

    signal backPageWithInfo(string contactName, string contactPhone)
    signal cancelled()

    Component.onCompleted: {
        console.log("pageContactSelection.onCompleted")
        //set the initial tab and button selected
        tabGroup.currentTab = favouriteTab;
        tabButtonRow.checkedButton = button1;
    }

    onStatusChanged: {
        console.log ("ContactSelectionPage.status: " + status);
        if (status == AUIPageStatus.Active)  {
            console.log ("Contact Selection Page now active with area_id: " + area_id + ", template_id: " + template_id);
            tabView.visible = true;
            tabView.enabled = true;
            //Sailfish / AUI call to method of tab content
            //favouriteTab.populate(area_id, template_id);
            //Qt Components way to call a method of a tab content
            //Tab is based on Loader, not Item, hence content cannot be called directly!
            tabView.favouriteTabItem.populate(area_id, template_id);
        }
        else {
            console.log ("Contact Selection Page NOT active");
        }
    }

//A standard QtQuick Components TabView is immediately visible "on top of the app", even if the owner page is hidden!
//
    TabView {
        id: tabView;
        enabled: false;
        visible: false;
        anchors.fill: parent;
        property alias favouriteTabItem: favouriteTab.item
        Tab {
            id: favouriteTab
            title: "Fav"
            FavouriteContactsPage {
                //anchors //have no effect on Sailfish, as this is a page, and the parent will not be tabgroup
                //anchors.fill: parent;
                //area_id: pageContactSelection.area_id
                //template_id: pageContactSelection.template_id
                fontPixelSize: pageContactSelection.fontPixelSize
                itemHeight: pageContactSelection.itemHeight
                headerHeight: pageContactSelection.headerHeight
                backgroundColor: pageContactSelection.backgroundColor
                labelColorActive: pageContactSelection.labelColorActive

                onContactSelected: {
                    pageContactSelection.backPageWithInfo(name, phoneNumber)
                }
                onCancelled: {
                    pageContactSelection.cancelled();
                }
            }
        }
        Tab {
            id: keyPadTab
            title: "Dial"
            PhoneDialer {   
                //anchors //have no effect on Sailfish, as this is a page, and the parent will not be tabgroup
                width: keyPadTab.width
                //width: pageContactSelection.width
                onNumberEntered: {
                    pageContactSelection.backPageWithInfo("Custom number", phoneNumber)
                }
                onCancelled: {
                    pageContactSelection.cancelled();
                }
            }
        }
        Tab {
            id: contactsTab
            title: "Contacts"
//            onActiveChanged: {
//                contactsTab.item.populateModels();
//            }
            PhoneContactsTab {
                anchors.topMargin: 0
                onContactSelected: {
                    console.log ("phone contact selected: " + name + ", ") + phoneNumber
                    pageContactSelection.backPageWithInfo(name, phoneNumber)
                }
            }
        }
    }

//    //container for the 3 tab-pages
//    AUITabGroup {id: tabGroup
//        anchors.top: parent.top
//        anchors.bottom: tabBar.top
//        width: parent.width

//        FavouriteContactsPage { id: favouriteTab
//            //anchors //have no effect on Sailfish, as this is a page, and the parent will not be tabgroup
//            fontPixelSize: pageContactSelection.fontPixelSize
//            itemHeight: pageContactSelection.itemHeight
//            headerHeight: pageContactSelection.headerHeight
//            backgroundColor: pageContactSelection.backgroundColor
//            labelColorActive: pageContactSelection.labelColorActive

//            onContactSelected: {
//                pageContactSelection.backPageWithInfo(name, phoneNumber)
//            }
//            onCancelled: {
//                pageContactSelection.cancelled();
//            }
//        }

//        PhoneDialer {id: keyPadTab
//            //anchors //have no effect on Sailfish, as this is a page, and the parent will not be tabgroup
//            width: tabGroup.width
//            //width: pageContactSelection.width
//            onNumberEntered: {
//                pageContactSelection.backPageWithInfo("Custom number", phoneNumber)
//            }
//            onCancelled: {
//                pageContactSelection.cancelled();
//            }
//        }

//        PhoneContactsTab {id: contactsTab
//            anchors.topMargin: 0
//            onContactSelected: {
//                console.log ("phone contact selected: " + name + ", ") + phoneNumber
//                pageContactSelection.backPageWithInfo(name, phoneNumber)
//            }
//        }
//    }
//    Rectangle {
//        id: tabBar
//        //color: "grey"
//        color: "black"
//        visible: true
//        //height: 109;
//        height: 74;
//        width: parent.width
//        anchors.bottom: parent.bottom;

//        AUIButtonRow {id: tabButtonRow
//            visible: true;
//            enabled: true;
//            anchors.bottom: parent.bottom;
//            height: parent.height;
//            width: parent.width;

//            AUITabButton { id: button1;
//                visible: true;
//                enabled: true;
//                tab: favouriteTab;
//                iconSource: "icons/icon-m-toolbar-favorite-mark-white.png";
//                onClicked: {console.log("button1.onClicked");
//                }
//            }
//            AUITabButton { id: button2;
//                visible: true;
//                enabled: true;
//                tab: keyPadTab;
//                iconSource: "icons/icon-m-toolbar-dialer-white.png";
//                onClicked: {
//                    console.log("button2.onClicked");
//                }
//            }
//            AUITabButton { id: button3
//                visible: true;
//                enabled: true;
//                tab: contactsTab;
//                iconSource: "icons/icon-m-toolbar-contact-white.png";
//                onClicked: console.log("button3.onClicked");
//            }
//        }
//    }
}
