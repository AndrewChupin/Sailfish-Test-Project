#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <functional>
#include <QVector>
#include <QSharedPointer>

/**
 * Класс не потоко-безопасный. Предполагается, что вся работа
 * с классом происходит в контексте одного потока.
 */
template<class State>
class Observable {
public:
    using Subscriber = std::function<void(const State &)>;
    using Subscription = QSharedPointer<int>;

    void next(const State &state) {
        _state = state;
        sendState();
    }

    Subscription subscribe(Subscriber subscriber) {
        _subscribers.push_back(subscriber);
        subscriber(_state);
        auto subscribtion = Subscription(new int(_subscribers.length() - 1));
        _subscribtions.push_back(subscribtion);
        return subscribtion;
    }

    void unsubscribe(Subscription subscribtion) {
        if (_subscribers.isEmpty() || subscribtion.isNull()) {
            return;
        }

        _subscribers.remove(*subscribtion);
        decrementSubscribtions(subscribtion);
        removeSubscribtion(subscribtion);
    }

    const State &state() {
        return _state;
    }

private:
    void sendState() {
        for (auto subscriber: _subscribers) {
            subscriber(_state);
        }
    }

    void decrementSubscribtions(Subscription after) {
        for (auto subscribtion: _subscribtions) {
            if (*subscribtion > *after) {
                (*subscribtion)--;
            }
        }
    }

    void removeSubscribtion(Subscription subscribtion) {
        _subscribtions.remove(_subscribtions.indexOf(subscribtion));
        subscribtion.clear();
    }

private:
    State _state;
    QVector<Subscriber> _subscribers;
    QVector<Subscription> _subscribtions;
};

#endif // OBSERVABLE_H
