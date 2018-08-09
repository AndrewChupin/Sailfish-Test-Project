#ifndef LISTSOURCE_H
#define LISTSOURCE_H

#include <QString>
#include <QFuture>
#include <QVector>

class ListSource
{
public:
    ListSource() = default;
    virtual ~ListSource() = default;

    virtual int pageCount() = 0;

    virtual QFuture<QVector<QString>> loadPage(int page) = 0;
};

#endif // LISTSOURCE_H
