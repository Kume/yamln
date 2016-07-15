import QtQuick 2.0
import QtQuick.Controls 2.0
import yamln 0.1

Column {
    property UIViewModel viewModel

    height: header.height + rows.height + commands.height

    Row {
        id: header
        height: basicStyle.rowHeight

        Label {
            width: basicStyle.labelWidth
        }

        Row {
            Repeater {
                model: viewModel.headers
                delegate: TableHeaderUIView {
                    viewModel: model.display
                }
            }
        }
    }

    ListView {
        id: rows
        height: basicStyle.rowHeight * 5
        width: parent.width

        model: viewModel.rows
        delegate: TableRowUIView {
            viewModel: model.display
        }
    }

    Row {
        id: commands
        height: basicStyle.rowHeight
        Button {
            height: basicStyle.rowHeight

            text: 'Add'
            onClicked: {
                viewModel.createNewRowAtLast("")
            }
        }
    }
}
