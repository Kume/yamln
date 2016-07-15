import QtQuick 2.0
import yamln 0.1

Rectangle {
    property UIViewModel viewModel

    border.color: 'lightgray'
    border.width: 0.5
    radius: 4

    TextEdit {
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        font.pointSize: basicStyle.fontSize
        horizontalAlignment: TextEdit.AlignLeft
        verticalAlignment: TextEdit.AlignVCenter
        selectByMouse: true
    }
}
