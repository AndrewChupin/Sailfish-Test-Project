#include "liststate.h"

ListState ListState::ERROR_STATE = ListState(QVector<QString>(), 0, "Somthing gone wrong", false, false);

ListState::ListState()
{

}

ListState::ListState(const QVector<QString> &items,
                     int page,
                     const QString &error,
                     bool isLoading,
                     bool isLastPage)
    : _items(items),
      _page(page),
      _error(error),
      _loading(isLoading),
      _lastPage(isLastPage)
{

}

ListState::ListState(const ListState &state)
{
    _items = state._items;
    _page = state._page;
    _error = state._error;
    _loading = state._loading;
    _lastPage = state._lastPage;
}

ListState &ListState::operator =(const ListState &state)
{
    _items = state._items;
    _page = state._page;
    _error = state._error;
    _loading = state._loading;
    _lastPage = state._lastPage;
    return *this;
}

const QVector<QString> &ListState::items() const
{
    return _items;
}

int ListState::page() const
{
    return _page;
}

const QString ListState::error() const
{
    return _error;
}

bool ListState::isLoading() const
{
    return _loading;
}

bool ListState::isLastPage() const
{
    return _lastPage;
}
