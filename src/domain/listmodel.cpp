#include "listmodel.h"

ListModel::ListModel(QObject *parent, QSharedPointer<ListSource> source)
    : QObject(parent),
      _observableState(ListModelObservable(new Observable<ListState>())),
      _source(source)
{
    connect(&_watcher, SIGNAL(finished()), this, SLOT(handleFinished()));
    connect(&_watcher, SIGNAL(canceled()), this, SLOT(handleCanceled()));

    loadMore();
}

ListModel::ListModelObservable ListModel::observeState()
{
    return _observableState;
}

void ListModel::loadMore()
{
    auto state = _observableState->state();
    auto page = state.page() + 1;
    if (page <= _source->pageCount()) {
        _observableState->next(ListState::newMoreLoadingState(state.items(), page));
        _future = _source->loadPage(page);
        _watcher.setFuture(_future);
    } else {
        _observableState->next(ListState::newFinishedState(state.items(), state.page()));
    }
}

void ListModel::handleFinished()
{
    auto result = _future.result();
    auto state = _observableState->state();
    QVector<QString> vec(state.items());
    vec.append(result);
    if (state.page() < _source->pageCount()) {
        _observableState->next(ListState::newState(vec, state.page()));
    } else {
        _observableState->next(ListState::newFinishedState(vec, state.page()));
    }
}

void ListModel::handleCanceled()
{
    _observableState->next(ListState::errorState());
}

