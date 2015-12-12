import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import LandedTheme 1.0
import JSONStorage 1.0
import "javascript/settings.js" as SETTINGS
import "aui"
import "gui"

AUIPageStackWindow {
    id: appWindow
    visible: true

    property int fontPixelSize: LandedTheme.FontSizeSmall;
//TODO: the properties largeFonts and smallFonts are still accessed from MainPage.qml. Why?
    property int largeFonts: LandedTheme.FontSizeSmall;
    property color backgroundColor: LandedTheme.BackgroundColorA
    property color textColorActive: LandedTheme.TextColorActive
    property color textColorInactive: LandedTheme.TextColorInactive
    property color labelColorActive: LandedTheme.LabelColorActive
    property color labelColorInactive: LandedTheme.LabelColorInactive

    initialPage: mainPage
    //cover is a sailfish only property
    //cover: Qt.resolvedUrl("cover/CoverPage.qml")

    Component.onCompleted: {
        console.log("main.qml: retrieving settings from Settings DB")
        var db = new SETTINGS.Settings();
        var rs = db.getDBLevel();
        var dbLevel = rs.rows.item(0)
        console.log ("main.qml: and the current dblevel is: " + dbLevel)
        if (dbLevel == "prod") {
            JSONStorage.setDbLevel(JSONStorage.Prod);
        }
        else if (dbLevel == "test") {
            JSONStorage.setDbLevel(JSONStorage.Test);
        }
    }

    MainPage {
        id: mainPage
        fontPixelSize: appWindow.fontPixelSize
        backgroundColor: appWindow.backgroundColor
        textColorActive: appWindow.textColorActive
        textColorInactive: appWindow.textColorInactive
        labelColorActive: appWindow.labelColorActive
        labelColorInactive: appWindow.labelColorInactive

        //On Qt5.5/Android it is necessary to explicitly bind Page status to Stack.status. This was not required on SailfishOS
        status: Stack.status;
        onNextPage: {
            if (pageType =="SMS") {
                console.log("smsType is: " + smsType)
                if (smsType =="Default") pageStack.push(smsPage, {lati: mainPage.getLatiDMS(), latiDec: mainPage.getLatiDec(), longi: mainPage.getLongiDMS(), longiDec: mainPage.getLongiDec(), alti: mainPage.getAlti(), area_id: area_id, template_id: template_id, msg_status: msg_status, lastPage: "mainPage"})
            }
            else {
                pageStack.push(areaSelectionPage)
            }
        }
    }

    AreaSelectionPage {
        id: areaSelectionPage
        fontPixelSize: appWindow.fontPixelSize
        backgroundColor: appWindow.backgroundColor
        labelColorActive: appWindow.labelColorActive
        //On Qt5.5/Android it is necessary to explicitly bind Page status to Stack.status. This was not required on SailfishOS
        status: Stack.status;
        onBackPageWithInfo: {
            mainPage.areaSet = true;
            mainPage.area_id = area_id;
            pageStack.pop(mainPage);
        }
        onCancelled: pageStack.pop(mainPage);
    }

    SMSPage {
        id: smsPage
        fontPixelSize: appWindow.fontPixelSize
        onCancelled: pageStack.pop(mainPage);
        status: Stack.status;
        onNextPage: {
            pageStack.push(contactSelectionPage, {area_id: area_id, template_id: template_id})
        }
    }

    ContactSelectionPage {
        id: contactSelectionPage
        fontPixelSize: appWindow.fontPixelSize
        backgroundColor: appWindow.backgroundColor
        labelColorActive: appWindow.labelColorActive
        status: Stack.status;
        onBackPageWithInfo: {
            console.log("About to pop smsPage; contactName: " + contactName + ", contactPhone: " + contactPhone);
            smsPage.contactName = contactName;
            smsPage.contactPhone = contactPhone;
            smsPage.lastPage = "contactSelectionPage";
            pageStack.pop(smsPage);
        }
        onCancelled: pageStack.pop(smsPage);
    }
    menuBar: MenuBar {
        Menu {
            title: "Database"
            MenuItem {
                text: "Set Prod Database";
                onTriggered: JSONStorage.setDbLevel(JSONStorage.Prod);
            }
            MenuItem {
                text: "Set Test Database";
                onTriggered: JSONStorage.setDbLevel(JSONStorage.Test);
            }
        }
        Menu {
            title: "Test Functions"
            MenuItem {
                text: "Fake GPS Aquired";
                onTriggered: mainPage.fakeGPSAcquired();
            }
        }
    }
}

