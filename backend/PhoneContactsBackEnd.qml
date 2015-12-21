import QtQuick 2.0
import ContactsHelper 1.0

Item {
    id: backEnd
    property alias localContactModel: localContactModelInternal
    property alias contactNumbersModel: contactNumbersModelInternal
    property alias nullModel: nullModelInternal
    property int index: 0;
    property int count: 0;

    signal modelsPopulated;


    ContactsHelper {
        id: contactsHelper;
        onContactFound: {
            console.log ("QML: onContactFound signal received for: " + index + " of " + count + ", displayLabel: " + contact.displayLabel);
            backEnd.index = index;
            backEnd.count = count;
            localContactModelInternal.appendContact(contact);
//TODO, send signal to GUI, so loading indicator can show progress....
        }

        onAllContactsSent: {         
            console.log ("QML: onAllContactsSent signal received, sending signal backEnd.modelsPopulated()");
            backEnd.modelsPopulated();
        }
    }

    //This is called when the owner Tab becomes active.
//TODO: check if the model is already populated, if so, no need to do again?
    function populateModels() {
        localContactModelInternal.populate();
        //On Android the call to  contactsHelper.getContacts() is asynchronous
        //therefore we wait for the signal "onAllContacts" sent from java
        //before signalling modelsPopuated to the GUI
    }

    //This model is exposed to the GUI via the alias localContactModel
    ListModel {
        id: localContactModelInternal

        property string role2FilterOn: "displayLabel";
        function populate() {
            clear();
            contactsHelper.getContacts();
        }

        function appendContact(contact) {
            console.log("appending: " + contact.displayLabel.label);
            localContactModel.append({"contactId": contact.contactId,
                                  "displayLabel": contact.displayLabel.label,
                                  "firstName": contact.name.firstName,
                                  "lastName": contact.name.lastName,
                                  "phoneNumber": contact.phoneNumber,
                                  "phoneNumbers": contact.phoneNumbers,
                                  "phoneNumbersCount": contact.phoneNumbers.length});

//TODO: phoneNumber.length is available here, but later when our localContactModel is used, it is no longer available
//How does this get lost?
            //console.log("appending: " + contact.displayLabel.label + ", numbers: " + contact.phoneNumbers.length)
            //phoneNumbers is a dynamic property of ContactModel, and is only partially documented
            //harmattan uses contact.displayLabel, sailfish contact.displayLabel.label
        }
    }

    //Stores the phone numbers and types of one contact
    ListModel {
        id: contactNumbersModelInternal

        function loadNumbers(contact) {
            console.log("loadNumbers: name to load: " + contact.displayLabel)
            console.log("loadNumbers: numbers to load: " + contact.phoneNumbersCount);
            console.log("loadNumbers: numbers to load2: " + contact.phoneNumbers.length);
            contactNumbersModelInternal.clear();
            for(var i = 0; i < contact.phoneNumbersCount; i++) {
                //console.log("appending number" + contact.phoneNumbers[i] + ", " + contact.phoneNumbers[i].number + ", " + contact.phoneNumbers[i].subTypes[0] + ", " + contact.displayLabel )
                //var subType = (contact.phoneNumbers[i].subTypes[0] === undefined) ? "" : contact.phoneNumbers[i].subTypes[0]
                //contactNumbersModelInternal.append({num: contact.phoneNumbers[i].number, type: subType, name: contact.displayLabel});
//TODO: Decide do we want to keep numbers as
//a) a "simple" QStringList, or
//b) an object structure, inc subtype?

                console.log("appending number: " + contact.phoneNumbers[i]);

            }
        }

        function flushNumbers() {
            contactNumbersModelInternal.clear();
        }

    }
    ListModel {
        id: nullModelInternal
    }
}




/*
TODO:
1) PhoneContactsBackEnd expects a "phoneContactBackEnd.localContactModel" to use
as the model for the InitialCharacterPicker model.
See QML ListModel

*/
