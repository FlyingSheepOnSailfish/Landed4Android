import QtQuick 2.0

//gives access to the contacts from the phone (as opposed to contacts stored by Landed / LandedSettings)

//The content of this page is lazy-loaded when the page becomes visible (as oppossed to when the app starts).
//http://harmattan-dev.nokia.com/docs/library/html/qt-components/qt-components-meego-pagestack.html#advanced-usage
//dynamic loading of page content as loading contacts takes time
//and sometimes stalls during load with error "The task queue's background thread stalled"

//TODO: on Android, tabs lazy load in anycase, so we could simplify this greatly
//i.e. merge PhoneContactsTab and PhoneContactsTabContent, scrapping the custom loading behaviour
//Maybe for Sailfish it could be moved to the AUITab object, and would thus count for all tabs, not just this one?


Item {
    id: contactsTab

    anchors.fill: parent

    signal contactSelected(string phoneNumber, string name)

    property Item containerObject;

    QtObject {
        id: privateVars
        property bool created: false
    }

    //On Sailfish, we used onVisibleChanged:, but on Android that property is already set to visible
    //when the tab is first displayed, so content was never created!
    Component.onCompleted: {
        console.log("PhoneContactsTab: onCompleted: visible: " + visible);
        //console.log("PhoneContactsTab: onVisibleChanged: " + visible + ", privateVars.created: " + privateVars.created);
        if (visible && !privateVars.created) {
            // create component
            console.log("PhoneContactsTab: Page content created.");
            var object = componentDynamic.createObject(contactsTab);
            privateVars.created = true;
            containerObject = object;
            console.log("contactsTab.height: " + contactsTab.height)
        } else {
            //why destroy: if we have gone to the bother of loading this, then we should keep this stuff
            //we don't need to take the loss of time to load this more than once.
            // destroy component
            //console.log("Page content destroyed.");
            //containerObject.destroy();
        }
    }

    // Page content inside Component, this is created dynamically when page is visible
    Component {
        id: componentDynamic
        PhoneContactsTabContent {
            anchors.fill: contactsTab
            id: content
            onContactSelected: contactsTab.contactSelected(number, name);
        }
    }

}


