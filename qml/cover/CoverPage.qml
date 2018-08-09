import QtQuick 2.0
import Sailfish.Silica 1.0
import com.a65apps.test 1.0

CoverBackground {

    FirstPageViewModel {
        id: viewModel
    }

    Component.onCompleted: {
        viewModel.onCreated()
    }

    onStatusChanged: {
        if (status === Cover.Deactivating) {
            viewModel.onDeactivating()
        } else if (status === Cover.Activating) {
            viewModel.onActivating()
        }
    }

    Label {
        id: label
        anchors.centerIn: parent
        text: viewModel.message
    }

    CoverActionList {
        id: coverAction

        CoverAction {
            iconSource: "image://theme/icon-cover-next"
            onTriggered: {
                viewModel.update()
            }
        }
    }
}
