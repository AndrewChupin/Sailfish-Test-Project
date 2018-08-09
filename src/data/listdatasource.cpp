#include "listdatasource.h"

ListDataSource::ListDataSource()
    : _pageCount(3)
{

}

int ListDataSource::pageCount()
{
    return _pageCount;
}

QFuture<QVector<QString> > ListDataSource::loadPage(int page)
{
    return QtConcurrent::run(QThreadPool::globalInstance(), this, &ListDataSource::loadData, page);
}

QVector<QString> ListDataSource::loadData(int page)
{
    QThread::msleep(1000);

    if (page == 1) {
        return {
            "Page 1",
            "Page 1",
            "Page 1",
            "Page 1",
            "Page 1",
            "Page 1",
            "Page 1",
            "Page 1",
            "Page 1",
            "Page 1"
        };
    } else if (page == 2) {
        return {
            "Page 2",
            "Page 2",
            "Page 2",
            "Page 2",
            "Page 2",
            "Page 2",
            "Page 2",
            "Page 2",
            "Page 2",
            "Page 2"
        };
    }

    return {
        "Page 3",
        "Page 3",
        "Page 3",
        "Page 3",
        "Page 3",
        "Page 3",
        "Page 3",
        "Page 3",
        "Page 3",
        "Page 3"
    };
}
