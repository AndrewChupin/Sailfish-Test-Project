import QtQuick 2.0
import Sailfish.Silica 1.0
import com.a65apps.test 1.0

BasePage {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    model: FirstPageViewModel {
        id: viewModel
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Show Page 2")
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
                visible: !viewModel.isLoading
            }
            MenuItem {
                text: qsTr("Update State")
                onClicked: viewModel.update()
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("UI Template")
            }

            Label {
                x: Theme.horizontalPageMargin
                text: viewModel.message
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }

            BusyIndicator {
                running: viewModel.isLoading
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
