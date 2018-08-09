#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>

#include <stdexcept>
#include "../di/provider.h"
#include "../domain/interactor.h"

template<class Model, class State>
class ViewModel : public QObject
{
public:
    using InteractorPtr = QSharedPointer<Model>;
    using ObservableState = QSharedPointer<Observable<State>>;
    using Subscription = QSharedPointer<int>;

    explicit ViewModel(QObject *parent)
        : QObject(parent)
    {

    }

    virtual ~ViewModel() = default;

    virtual void onCreated() {
        inject();
        if (_interactor.isNull()) {
            throw std::runtime_error("Illegal state: _interactor is not injected");
        }
        _state = _interactor->observeState();
    }

    virtual void onActivating() {
        using namespace std::placeholders;

        if (_subscription.isNull()) {
            _subscription = _state->subscribe(std::bind(&ViewModel<Model, State>::updateState, this, _1));
        }
    }

    virtual void onDeactivating() {
        _state->unsubscribe(_subscription);
        _subscription.clear();
    }

protected:
    virtual void inject() = 0;

    void setInteractor(InteractorPtr interactor) {
        _interactor = interactor;
    }

    InteractorPtr getInteractor() {
        return _interactor;
    }

    virtual void updateState(const State &state) = 0;

private:
    InteractorPtr _interactor;
    ObservableState _state;
    Subscription _subscription;
};

#endif // PRESENTER_H
