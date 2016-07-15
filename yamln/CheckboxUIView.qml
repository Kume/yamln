import QtQuick 2.7
import QtQuick.Controls 2.0
import yamln 0.1

Item {
    id: viewRoot
    property UIViewModel viewModel

    CheckBox {
        id: checkbox
        anchors.fill: parent
        text: "Yes"

        indicator: Rectangle {
            implicitWidth: viewRoot.height - 4
            implicitHeight: viewRoot.height - 4
            x: control.leftPadding
            y: parent.height / 2 - height / 2
            radius: 3
            border.color: checkbox.down ? "#17a81a" : "#21be2b"

            Rectangle {
                width: 14
                height: 14
                x: 6
                y: 6
                radius: 2
                color: checkbox.down ? "#17a81a" : "#21be2b"
                visible: checkbox.checked
            }
        }
    }

    Component.onCompleted: {
        console.log('test')
    }
}
