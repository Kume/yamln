import QtQuick 2.0
import QtQuick.Controls 1.4
import yamln 0.1

Rectangle {
    property UIViewModel viewModel: null
    readonly property UIViewModel contentViewModel: viewModel.content

    height: basicStyle.rowHeight

    Item {
        id: labelItem
        width: basicStyle.labelWidth
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 2
        Label {
            anchors.fill: parent
            text: viewModel.content.label
            verticalAlignment: "AlignVCenter"
            font.pointSize: basicStyle.fontSize
        }
    }

    Loader {
        id: contentLoader
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: labelItem.right
        anchors.right: parent.right
        anchors.margins: 2
        source: typeQmlPathMap[contentViewModel.type]
    }

    Binding {
        target: contentLoader.item
        property: "viewModel"
        value: viewModel.content
    }
}
