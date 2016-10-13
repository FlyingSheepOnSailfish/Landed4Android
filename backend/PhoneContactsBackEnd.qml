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
            //console.log ("QML: onContactFound signal received for: " + index + " of " + count + ", displayLabel: " + contact.displayLabel);
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

        property string role2FilterOn: "filterLabel";
        function populate() {
            clear();
            contactsHelper.getContacts();
        }

        function appendContact(contact) {
            //console.log("appendContact: " + contact.displayLabel.label);
            //console.log("appendContact: phoneNumbers size : " + contact.phoneNumbers.length);
            var numbers = [];
            for(var i = 0; i < contact.phoneNumbers.length; i++) {
                //console.log("appendContact: number: " + contact.phoneNumbers[i].number);
                numbers.push( {"number": contact.phoneNumbers[i].number, "type": contact.phoneNumbers[i].type});
            }

            //Note we need to explicitly map all the properties of child objects
            //while we could just append "displayLabel": contact.displayLabel,
            //in the delegate displayLabel will be undefined, and thus not accessible.
            //Should the objects become complexer, than we could abandon the QML ListModel, and create a subclass of QAbstractItemModel
            //See http://stackoverflow.com/questions/34546485/accessing-properties-of-child-objects-stored-in-a-qml-listmodel
            localContactModel.append({"contactId": contact.contactId,
                                         "filterLabel": contact.displayLabel.label,
                                  "displayLabel": {"label": contact.displayLabel.label},
                                  "name": {"firstName": contact.name.firstName,
                                            "lastName": contact.name.lastName},
                                  "phoneNumber": contact.phoneNumber,
                                  "phoneNumbers": numbers,
                                  "phoneNumbersCount": contact.phoneNumbers.length});
            //Note the role "filterLabel" will be used by IPC via the property role2FilterOn to filter on!
            //the role must be at base level of the model.

        }
    }

    //Stores the phone numbers and types of one contact
    ListModel {
        id: contactNumbersModelInternal

        function loadNumbers(contact) {
            console.log("loadNumbers: name to load: " + contact.displayLabel.label)
            console.log("loadNumbers: numbers to load: " + contact.phoneNumbersCount);
            //console.log("loadNumbers: numbers to load2: " + contact.phoneNumbers.length); //gives undefined
            console.log("loadNumbers: numbers to load3: " + contact.phoneNumbers.count); //gives expected size
            contactNumbersModelInternal.clear();
            for(var i = 0; i < contact.phoneNumbersCount; i++) {
                console.log("1) appending number: " + contact.phoneNumbers.get(i).number);
                contactNumbersModelInternal.append({"num": contact.phoneNumbers.get(i).number,
                                                    "type": contact.phoneNumbers.get(i).type,
                                                    "name": contact.displayLabel.label});
                //contactNumbersModelInternal.append({num: contact.phoneNumbers[i].number, type: subType, name: contact.displayLabel});
            }
        //Curiously, javascript methods like contact.phoneNumbers.length and contact.phoneNumbers[i].number don't work!
        //This implies our container is not an a javascript array
        //The QT docu http://doc.qt.io/qt-5/qml-qtqml-models-listmodel.html#example-usage
        //ambiguously refers to roles containing [ ] as "list data"
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
