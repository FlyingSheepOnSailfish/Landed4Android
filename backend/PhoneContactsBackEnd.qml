import QtQuick 2.0
import ContactsHelper 1.0

Item {
    id: backEnd
    property alias localContactModel: localContactModelInternal

    signal modelsPopulated;

    ContactsHelper {
        id: contactsHelper;
        onContactFound2: {
            console.log ("QML: onContactFound2 signal received for: " + index + " of " + count + ", displayLabel: " + contact.displayLabel);
            localContactModelInternal.appendContact(contact);
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

        function populate() {
            clear();
            contactsHelper.getContacts();
        }

        function appendContact(contact) {
            console.log("appending: " + contact.displayLabel);
            //Note the Sailfish version has displayLabel.label, for Android we have only implemented
            //displayLabel (w/o the .label child attribute).
            localContactModel.append({"contactId": contact.contactId,
                                  "displayLabel": contact.displayLabel,
                                  "firstName": contact.name.firstName,
                                  "lastName": contact.name.lastName,
                                  "phoneNumber": contact.phoneNumber,
                                  "phoneNumbers": contact.phoneNumbers,
                                  "phoneNumbersCount": contact.phoneNumbers.length});
//TODO: in the Qt Mobility version, we have a name object
            //with child attributes
//            "firstName": contact.name.firstName,
//            "lastName": contact.name.lastName,

//TODO: phoneNumber.length is available here, but later when our localContactModel is used, it is no longer available
//How does this get lost?
            //console.log("appending: " + contact.displayLabel.label + ", numbers: " + contact.phoneNumbers.length)
            //phoneNumbers is a dynamic property of ContactModel, and is only partially documented
            //harmattan uses contact.displayLabel, sailfish contact.displayLabel.label
        }
        //This function is required for InitialCharacterPicker, which is the consumer of this model
        function value2FilterOn(index){
            console.log("localContactModelInternal.value2FilterOn called: " + get(index).displayLabel)
//TODO: why does this give us undefined?
            return get(index).displayLabel;
        }
    }

}




/*
TODO:
1) PhoneContactsBackEnd expects a "phoneContactBackEnd.localContactModel" to use
as the model for the InitialCharacterPicker model.
See QML ListModel
2) Once all Contacts have been retreived from Java API,
we need to emit the modelsPopulated signal
3) We need to provide a model for the contact itself. See original Sailfish Code.

*/
