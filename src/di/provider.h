#ifndef PROVIDER_H
#define PROVIDER_H

#include <QSharedPointer>

template<class T>
class Provider {
public:
    Provider() = default;

    virtual ~Provider() = default;

    virtual QSharedPointer<T> provide() = 0;
};

#endif // PROVIDER_H
