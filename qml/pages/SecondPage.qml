import QtQuick 2.0
import Sailfish.Silica 1.0
import com.a65apps.test 1.0

BasePage {
    id: page

    model: SecondPageViewModel {
        id: viewModel
    }

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView

        PushUpMenu {
            busy: viewModel.isLoading

            quickSelect: true

            MenuItem {
                text: qsTr("Load more")
                onClicked: viewModel.loadMore()
                enabled: !viewModel.isLoading && !viewModel.isLastPage
            }
        }

        model: viewModel.listModel
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Nested Page")
        }
        delegate: BackgroundItem {
            id: delegate

            Label {
                x: Theme.horizontalPageMargin
                text: name
                anchors.verticalCenter: parent.verticalCenter
                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
            }
            onClicked: console.log("Clicked " + index)
        }
        VerticalScrollDecorator {}
    }
}
