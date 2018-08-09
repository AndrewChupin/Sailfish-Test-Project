import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    property var model

    Component.onCompleted: {
        model.onCreated()
    }

    onStatusChanged: {
        if (status === PageStatus.Deactivating) {
            model.onDeactivating()
        } else if (status === PageStatus.Activating) {
            model.onActivating()
        }
    }

    Connections {
        target: Qt.application
        onActiveChanged: {
            if (!Qt.application.active) {
                model.onDeactivating()
            } else {
                model.onActivating()
            }
        }
    }
}
