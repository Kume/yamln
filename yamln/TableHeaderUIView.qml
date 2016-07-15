import QtQuick 2.0
import QtQuick.Controls 2.0
import yamln 0.1

Item {
    property UIViewModel viewModel

    height: basicStyle.rowHeight
    width: basicStyle.labelWidth

    Rectangle {
        anchors.fill: parent
        anchors.margins: 2
        color: "#DDDDDD"
    }

    Label {
        anchors.fill: parent
        anchors.margins: 2

        verticalAlignment: "AlignVCenter"
        text: viewModel.label
    }
}
