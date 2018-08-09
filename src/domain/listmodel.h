#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QFutureWatcher>

#include "listsource.h"
#include "listinteractor.h"

class ListModel : public QObject, public ListInteractor
{
    Q_OBJECT

public:
    using ListModelObservable = Interactor<ListState>::SharedObservable;

    ListModel(QObject *parent, QSharedPointer<ListSource> source);

    virtual ListModelObservable observeState() override;

    virtual void loadMore() override;

private slots:
    void handleFinished();

    void handleCanceled();

private:
    ListModelObservable _observableState;
    QSharedPointer<ListSource> _source;
    QFutureWatcher<QVector<QString>> _watcher;
    QFuture<QVector<QString>> _future;
};

#endif // LISTMODEL_H
