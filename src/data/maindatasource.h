#ifndef MAINDATASOURCE_H
#define MAINDATASOURCE_H

#include <QtConcurrent/QtConcurrent>

#include "../domain/mainsource.h"

class MainDataSource : public MainSource
{
public:
    MainDataSource();

    virtual QFuture<QString> getData() override;

private:
    QString loadData();
};

#endif // MAINDATASOURCE_H
