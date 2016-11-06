import QtQuick 2.0
import yamln 0.1

Item {
    property UIViewModel viewModel: null
    height: column.height

    onViewModelChanged: {
        console.log('onViewModelChanged')
        console.log(viewModel.elements)
    }

    Column {
        id: column

        Repeater {
            model: viewModel.elements
            delegate: FormElement {
                viewModel: model.display
            }
        }
    }
}
