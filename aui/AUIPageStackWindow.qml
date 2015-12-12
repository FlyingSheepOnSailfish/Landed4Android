import QtQuick 2.0
import QtQuick.Controls 1.4

ApplicationWindow {

    property alias initialPage: stackView.initialItem
    property alias pageStack: stackView

    StackView {
        id: stackView
        anchors.fill: parent

    }
}
