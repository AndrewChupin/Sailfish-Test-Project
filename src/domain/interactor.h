#ifndef INTERACTOR_H
#define INTERACTOR_H

#include <QSharedPointer>

#include "observable.h"

template<class State>
class Interactor {
public:
    using SharedObservable = QSharedPointer<Observable<State>>;

    Interactor() = default;

    virtual ~Interactor() = default;

    virtual SharedObservable observeState() = 0;
};

#endif // INTERACTOR_H
