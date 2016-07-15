import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    visible: true
    property BasicUIStyle basicStyle: BasicUIStyle{
    }

    Menu {
    }

    width: 600
    height: 400

    Form {
        anchors.fill: parent
        viewModel: test.content
        onViewModelChanged: {
            console.log(test)
            // mapToItem()
        }
    }

    readonly property var typeQmlPathMap: {
        "text": "TextUIView.qml",
        "form": "Form.qml",
        "table": "TableUIView.qml",
        "checkbox": "CheckboxUIView.qml",
        "checkboxes": "CheckboxesUIView.qml",
        "redio": "RedioUIView.qml"
    }
}
