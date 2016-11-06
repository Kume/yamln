import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtWebEngine 1.0

Window {
    visible: true
    property BasicUIStyle basicStyle: BasicUIStyle{
    }

    Menu {
    }

    width: 600
    height: 400


    SplitView {
        anchors.fill: parent
        ScrollView {
            height: parent.height

            Form {
                height: parent.height
                viewModel: test.content
            }
        }


        WebEngineView {

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
