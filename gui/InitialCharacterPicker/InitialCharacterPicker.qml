// Copyright (C) 2014 Chris Lamb
// This sofware is released under the MIT License --> http://en.wikipedia.org/wiki/MIT_license

//Sailfish Imports
//import QtQuick 2.0
//import Sailfish.Silica 1.0

//Android Imports
import QtQuick 2.5

//Shared Imports
import "../../javascript/initialCharacterPicker.js" as IPCJS

//How does the IntialCharcterPicker work?
// It's a list view, with clever header and footer components.
// The rows of character buttons are hosted by the listView's header and footers (both the header and footer host the full alphabet)
// Each row decides for itself if it should be visible on the header or footer.
// The model displayed is a copy of that provided by parameter to InitialPicker.qml, filtered as necessary.
// A javascript array count the number of hits per character. This is used to provide visual indication if a button is worth pressing.
// Both rows and the buttons they host are dynmically created QML elements. which is a neat trick cutting down repetative code.

//The header and footer automagically decide which (if any) rows of buttons should be visible based on the selected initial
//Each initial should only be displayed once, either in the header, or in the footer, never in both.
//Initial is in the selected row      --> visible in Header, Not visible in Footer
//Initial is above the selected row   --> visible in Header, Not visible in Footer
//Initial is below the selected row   --> visible in Footer, Not visible in Header

Item {
    id: picker

    Component.onCompleted: {
        console.log("InitialCharacterPicker: onCompleted " + picker.count);
        if ((picker.count) && (picker.count > 0)) {
            PrivateObject.populateModels();
        }
    }

    signal clicked (string character, string rowName)
    onClicked: {
        console.log("InitialPicker onClicked:" + character + ", row is: " + rowName);
        if (selectedCharacter == character) {
            console.log("the same character has been clicked again, close up")
            selectedCharacter = "";
        }
        else {
            selectedCharacter = character;
        }
        selectedRow = rowName;
    }

    property alias delegate: listView.delegate
    property alias currentIndex: listView.currentIndex
    property QtObject model

    anchors.fill: parent

    property variant characters
    property int charactersPerRow
    property string initialCharacter: ""
    property string selectedCharacter
    property string selectedRow: "none"
    property string role2Filter
    property bool caseSensitive: false
    property alias count: listView.count

    onSelectedCharacterChanged: {
        console.log("picker: onSelectedCharacterChanged: " + selectedCharacter + " filtering model")
        filteredModel.populate(picker.model, selectedCharacter);
    }

    function populate(){
        privateObject.populateModels();
    }

    QtObject {
        id: privateObject
        property variant charactersModel

        function getChar(character) {
            for (var i=0; i < privateObject.charactersModel.length; i++) {
                if (privateObject.charactersModel[i].character == character) {
                    console.log("privateObject.getChar: character: " + character + " found");
                    return privateObject.charactersModel[i];
                }
            }
        }

        function filterMatch(field2Filter, filterCharacter) {
            //console.log("filterCharacter: " + filterCharacter)
            var left = field2Filter.trim()
            var right = filterCharacter.trim()
            if (picker.caseSensitive) {
                return (left.charAt(0) == right);
            }
            else {
                return (left.charAt(0).toUpperCase() == right.toUpperCase());
            }
        }

        function countHits4Character (charHits) {
            //console.log("starting countHits4Character for character: " + charHits.character + ", model members: " + model.count)
            charHits.hits = 0;
            charHits.startIndex = charHits.endIndex; //start where we last ended
            for (var j = charHits.startIndex; j < model.count; j++) {
                //Using ["displayLabel"] we can access fields dynamically by name (not hard coded by dot notation)
                //This means we can have a property role2Filter as a hint which role we use
                //but would be free to use another if we so chose.
                var value2FilterOn = model.get(j)[model.role2FilterOn];
                //console.log("countHits4Character: displayLabel: " + value2FilterOn);

                if (privateObject.filterMatch(value2FilterOn, charHits.character)) {
                    charHits.hits++;
                } else {
                    if (charHits.hits > 0) {
                        //console.log("we have encountered a new character!");
                    } else {
//TODO add special handling here for character type
//If the passed filter char is A-Z, and value2FilterOn is numeric, skip to next item
//Or better said if chars are same type --> problem
//if different type /number vs char, skip to next char.

                        //console.log("there are no hits for this char: " + charHits.character);
                    }
                    //In either case:
                    // a) abort this loop, and
                    // b) start the loop for the next character at this point
                    charHits.endIndex = j;
                    break;
                }

                /*
                The original CountHits4Character function looped through the entire Contact model multiple times, once per char.
                This version tries to loop through the model and char in parallel, making the assumption that bot models are sorted
                alphabetically.

                Note that the number of hits per char is sent down to CharacterButton level,
                but the only important factor is: 0 or > 0.  i.e. no hits vs. hits. The true number of hits is NOT used.
                */
            }
            //console.log("ending countHits4Character for character: " + charHits.character + ", hits: " + charHits.hits + ", start: " + charHits.startIndex + ", end: " + charHits.endIndex);
            return charHits;
        }

//THINK! as currently sorted, contacts with numeric display labels
// are the start of the contact model, but we have the number button at the end of the character model!
        function populateModels() {
            console.log("IPC.privateObject populateModels called. characters: "  + characters.length);
            var charsModel = []
            var charHits = new IPCJS.CharHits("", 0, 0, 0);
            for (var i=0; i < characters.length; i++) {
                charHits.character = characters[i];
                var hits = 0;
                if (characters[i] == "%") {
                    //Wildcard for all leading characters
                    charHits.hits = picker.model.count;
                }
                else if (characters[i] == "#") {
                    //Wildcard for leading numerals
                    var numeralHits = 0;
                    var startIndex = 0;
                    for (var j = 0; j <= 9; j++) {
                        charHits.character = j.toString();
                        charHits = countHits4Character(charHits);
                        numeralHits = numeralHits + charHits.hits;
                        if ((numeralHits > 0) && (startIndex == 0)) {
                             //startIndex has to be set to the lowest value where numeralHits is positive
                            startIndex = (charHits.endIndex - charHits.hits);
                        }
                    }
                    charHits.character = "#";
                    charHits.startIndex = startIndex;
                    charHits.endIndex = startIndex + numeralHits;
                    charHits.hits = numeralHits;
                }
                else {
                    //normal character
                    charHits = countHits4Character(charHits);
                }
                //console.log("populateModels: pushing: " + charHits.character + ", startIndex: " + charHits.startIndex + ", endIndex: " + charHits.endIndex);
                //clone the object before pushing ... to prevent subsequent changes affecting the pushed copies ...
                var pushCharHits = charHits.clone();
                charsModel.push({"character": pushCharHits.character, charHits: pushCharHits});
            }
            //console.log("populateModels: length: " + charsModel.length)

            //when charactersModel changes, the header and footer dynamically create their rows
            //any previously created rows are destroyed (see CharacterGrid.qml)
            privateObject.charactersModel = charsModel;

            //Now populate the filter model
            filteredModel.clear();
            filteredModel.populate(picker.model, picker.initialCharacter);
        }
    }

    ListModel {
        id: filteredModel
        objectName: "filteredModel"
        function populate(model, filter) {
            //console.log("populating filteredModel for character: " + filter)
            filteredModel.clear();
            if (filter =="") {
                //leave the model empty
            }
            else if (filter =="%") {
                //Wildcard for all entries
                console.log("don't filter, copy the model lock stock and barrel " + model.count);
                for (var i = 0; i < model.count; i ++) {
                    var rec = model.get(i);
                    filteredModel.append(rec);
                }
            }
            else if (filter =="#") {
                //Wildcard for all numeric entries
                //filter on the chosen character
                bulkAppend(model, filter);
//                for (var j = 0; j <= 9; j++) {
//                    bulkAppend(model, j.toString());
//                }
            }
            else {
                //filter on the chosen character
                bulkAppend(model, filter);
            }
            //console.log("populated filteredModel with entries: " + filteredModel.count);
        }
        function bulkAppend(model, filter) {
            var character = privateObject.getChar(filter);
            var startIndex = character.charHits.startIndex;
            var endIndex = character.charHits.endIndex;
            console.log("Bulk appending entries for character: " + filter + ", " + character.charHits.character +", startIndex: " + startIndex + ", endIndex: " + endIndex);
            for (var i = startIndex; i < endIndex; i ++) {
                var rec = model.get(i);
                filteredModel.append(rec);
            }
        }
    }

    //SilicaListView {
    ListView {
        id: listView
        anchors.fill: parent
        //height: childrenRect.height // don't this, it stops the listview flicking!!!!!
        model: filteredModel
        header: characterHeader
        footer: characterFooter
        clip: true
//        VerticalScrollDecorator { flickable: listView }
    }

    Component{
        id: characterHeader
        CharacterGrid {
            charactersPerRow: picker.charactersPerRow
//this property binding communicates the "change" from the privateObject to the buttons
            charactersModel: privateObject.charactersModel
            //these 3 properties used to determine which character rows should be open on header or footer
            selectedCharacter: picker.selectedCharacter
            selectedRow: picker.selectedRow
            isHeader: true
            onClicked: picker.clicked(character, rowName);
        }
    }

    Component{
        id: characterFooter
        CharacterGrid {
            charactersPerRow: picker.charactersPerRow
            charactersModel: privateObject.charactersModel
            //these 3 properties used to determine which character rows should be open on header or footer
            selectedCharacter: picker.selectedCharacter
            selectedRow: picker.selectedRow
            isHeader: false //we are a footer!
            onClicked: picker.clicked(character, rowName);
        }
    }
}
