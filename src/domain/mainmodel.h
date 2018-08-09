#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QFutureWatcher>

#include "maininteractor.h"
#include "mainstate.h"
#include "mainsource.h"

class MainModel : public QObject, public MainInteractor
{
    Q_OBJECT

public:
    using MainModelObservable = Interactor<MainState>::SharedObservable;

    explicit MainModel(QObject *parent, QSharedPointer<MainSource> source);

    virtual MainModelObservable observeState() override;

    virtual void update() override;

private slots:
    void handleFinished();

    void handleCanceled();

private:
    MainModelObservable _observableState;
    QSharedPointer<MainSource> _source;
    QFutureWatcher<QString> _watcher;
    QFuture<QString> _future;
};

#endif // MAINMODEL_H
