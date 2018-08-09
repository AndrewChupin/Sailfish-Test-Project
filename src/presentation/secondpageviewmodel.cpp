#include "secondpageviewmodel.h"
#include "../di/diproduct.h"

SecondPageViewModel::SecondPageViewModel(QObject *parent)
    : ViewModel<ListInteractor, ListState>(parent),
      _listModel(new StringListViewModel(this))
{

}

void SecondPageViewModel::onCreated()
{
    ViewModel<ListInteractor, ListState>::onCreated();
}

void SecondPageViewModel::onActivating()
{
    ViewModel<ListInteractor, ListState>::onActivating();
}

void SecondPageViewModel::onDeactivating()
{
    ViewModel<ListInteractor, ListState>::onDeactivating();
}

void SecondPageViewModel::loadMore()
{
    getInteractor()->loadMore();
}

StringListViewModel *SecondPageViewModel::listModel()
{
    return _listModel.data();
}

bool SecondPageViewModel::isLoading()
{
    return _loading;
}

bool SecondPageViewModel::isLastPage()
{
    return _lastPage;
}

void SecondPageViewModel::inject()
{
    QSharedPointer<SecondViewModelModule> module(new SecondViewModelModule(ApplicationComponent::getInstance(), this));
    setInteractor(module->provide());
}

void SecondPageViewModel::updateState(const ListState &state)
{
    _loading = state.isLoading();
    _lastPage = state.isLastPage();
    _listModel->setItems(state.items());
    emit stateChanged();
}

StringListViewModel::StringListViewModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

QHash<int, QByteArray> StringListViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

int StringListViewModel::rowCount(const QModelIndex &) const
{
    return _items.size();
}

QVariant StringListViewModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    if(role == NameRole) {
        return QVariant(_items[index.row()]);
    }
    return QVariant();
}

void StringListViewModel::setItems(const QVector<QString> &items)
{
    int size = _items.length();
    int newSize = items.length();
    if (size == 0 && newSize > 0) {
        beginResetModel();
        _items = items;
        endResetModel();
    } else {
        if (newSize > size) {
            for (int i = size; i < newSize; ++i) {
                beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
                _items.append(items[i]);
                endInsertRows();
            }
        }
    }
}
