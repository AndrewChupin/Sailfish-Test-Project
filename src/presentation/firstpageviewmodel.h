#ifndef FIRSTPAGEPRESENTER_H
#define FIRSTPAGEPRESENTER_H

#include <QObject>
#include <QString>

#include "viewmodel.h"
#include "../di/di.h"

class FirstPageViewModel : public ViewModel<MainInteractor, MainState>
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message NOTIFY stateChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY stateChanged)

public:
    explicit FirstPageViewModel(QObject *parent = nullptr);

    QString message();

    bool isLoading();

    Q_INVOKABLE void update();

    Q_INVOKABLE virtual void onCreated() override;

    Q_INVOKABLE virtual void onActivating() override;

    Q_INVOKABLE virtual void onDeactivating() override;

signals:
    void stateChanged();

protected:
    virtual void inject() override;

    virtual void updateState(const MainState &state) override;

private:
    QString _message;
    bool _loading;
};

#endif // FIRSTPAGEPRESENTER_H
