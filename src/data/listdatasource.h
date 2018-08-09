#ifndef LISTDATASOURCE_H
#define LISTDATASOURCE_H

#include <QtConcurrent/QtConcurrent>

#include "../domain/listsource.h"

class ListDataSource : public ListSource
{
public:
    ListDataSource();

    virtual int pageCount() override;

    virtual QFuture<QVector<QString>> loadPage(int page) override;

private:
    QVector<QString> loadData(int page);

private:
    int _pageCount;
};

#endif // LISTDATASOURCE_H
