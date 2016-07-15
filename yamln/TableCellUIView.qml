import QtQuick 2.0
import QtQuick.Controls 2.0
import yamln 0.1

Item {
    property UIViewModel viewModel

    width: basicStyle.labelWidth

    Loader {
        id: contentLoader
        anchors.fill: parent
        anchors.margins: 2
        source: typeQmlPathMap[viewModel.content.type]
    }

    Binding {
        target: contentLoader.item
        property: "viewModel"
        value: viewModel.content
    }
}
