import QtQuick 2.5
import QtQuick.Controls 1.4
import AUI 1.0

Item {
    property Item tools: null;
    property int orientationLock: AUIPageOrientation.Automatic;
    property color backgroundColor;
    property bool showNavigationIndicator;
    property bool backNavigation
    property int status: AUIPageStatus.Inactive;
}
