#include "maindatasource.h"

MainDataSource::MainDataSource()
{

}

QFuture<QString> MainDataSource::getData()
{
    return QtConcurrent::run(QThreadPool::globalInstance(), this, &MainDataSource::loadData);
}

QString MainDataSource::loadData()
{
    QThread::msleep(3000);
    return "Loaded string";
}
