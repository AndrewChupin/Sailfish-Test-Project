#include "mainmodel.h"

MainModel::MainModel(QObject *parent, QSharedPointer<MainSource> source) :
    QObject(parent),
    _observableState(MainModelObservable(new Observable<MainState>())),
    _source(source)
{
    connect(&_watcher, SIGNAL(finished()), this, SLOT(handleFinished()));
    connect(&_watcher, SIGNAL(canceled()), this, SLOT(handleCanceled()));

    update();
}

MainModel::MainModelObservable MainModel::observeState()
{
    return _observableState;
}

void MainModel::update()
{
    _observableState->next(MainState::loadingState());

    _future = _source->getData();
    _watcher.setFuture(_future);
}

void MainModel::handleFinished()
{
    _observableState->next(MainState::newState(_future.result()));
}

void MainModel::handleCanceled()
{
    _observableState->next(MainState::errorState());
}
