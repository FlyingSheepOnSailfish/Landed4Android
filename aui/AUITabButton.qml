import QtQuick 2.5
import QtQuick.Controls 1.4
import LandedTheme 1.0

Item {
//BackgroundItem {
    id: tabIndicator

    signal clicked;

    property alias text: label.text
    property alias iconSource: image.source
    property bool __selected
    property Item tab

    width: parent.width / parent.children.length

    Connections {
        target: tab.parent
        onCurrentTabChanged: __selected = tab.parent.currentTab == tab;
    }

    Image {
        id: image
        visible: source != null
        opacity: __selected ? 1 : 0.5
        anchors.centerIn: parent
    }

    Label {
        visible: (image != visible) && (text.length > 0)
        id: label
        text: ""
        color: LandedTheme.secondaryHighlightColor
        font.pixelSize: LandedTheme.fontSizeExtraLarge
        font.bold: __selected
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent;
        onClicked: {tabIndicator.clicked}
    }

    onClicked: {
        tab.parent.currentTab = tab;
    }
}
