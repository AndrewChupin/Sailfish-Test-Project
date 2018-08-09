#ifndef MAINSOURCE_H
#define MAINSOURCE_H

#include <QFuture>

class MainSource
{
public:
    MainSource() = default;

    virtual ~MainSource() = default;

    virtual QFuture<QString> getData() = 0;
};

#endif // MAINSOURCE_H
