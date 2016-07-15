import QtQuick 2.0
import yamln 0.1

Rectangle {
    property UIViewModel viewModel

    height: basicStyle.rowHeight

    border.width: 0.5
    border.color: "#DDDDDD"

    Row {
        id: row
        height: parent.height

        Item {
            height: parent.height
            width: basicStyle.labelWidth
        }

        Row {
            id: cells
            height: parent.height
            Repeater {
                model: viewModel.cells
                delegate: TableCellUIView {
                    height: cells.height
                    viewModel: model.display
                }
            }
        }
    }
}
