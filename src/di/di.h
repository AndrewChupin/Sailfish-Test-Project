#ifndef DI_H
#define DI_H

#include <sailfishapp.h>
#include <QSharedPointer>

#include "provider.h"
#include "../domain/mainsource.h"
#include "../domain/listsource.h"
#include "../domain/maininteractor.h"
#include "../domain/listinteractor.h"
#include "../presentation/viewmodel.h"

class MainDataComponent {
public:
    MainDataComponent() = default;
    virtual ~MainDataComponent() = default;

    virtual QSharedPointer<MainSource> provide() = 0;
};

class ListDataComponent {
public:
    ListDataComponent() = default;
    virtual ~ListDataComponent() = default;

    virtual QSharedPointer<ListSource> provide() = 0;
};

class DataComponent {
public:
    DataComponent() = default;
    virtual ~DataComponent() = default;

    virtual QSharedPointer<MainDataComponent> provideMainDataComponent() = 0;

    virtual QSharedPointer<ListDataComponent> provideListDataComponent() = 0;
};

class MainModelComponent {
public:
    MainModelComponent(class DomainComponent *domainComponent)
        : _domainComponent(domainComponent)
    {
    }
    virtual ~MainModelComponent() = default;

    virtual QSharedPointer<MainInteractor> provide() = 0;

    class DomainComponent *getDomainComponent() {
        return _domainComponent;
    }

private:
    class DomainComponent *_domainComponent;
};

class DomainComponent {
public:
    DomainComponent(class ApplicationComponent *appComponent)
        : _appComponent(appComponent)
    {
    }
    virtual ~DomainComponent() = default;

    class ApplicationComponent *getApplicationComponent() {
        return _appComponent;
    }

    virtual QSharedPointer<MainModelComponent> provideMainModelComponent() = 0;

private:
    class ApplicationComponent *_appComponent;
};

class ApplicationComponent {
public:

    static ApplicationComponent *getInstance() {
        return instance;
    }

    ApplicationComponent(QGuiApplication *app) : _app(app)
    {
        if (instance != nullptr) {
            qWarning("ApplicationComponent::ApplicationComponent() called multiple times!");
        } else {
            instance = this;
        }
    }

    virtual ~ApplicationComponent() = default;

    QGuiApplication *provideApplication() {
        return _app;
    }

    virtual QSharedPointer<DataComponent> provideDataComponent() = 0;

    virtual QSharedPointer<DomainComponent> provideDomainComponent() = 0;

private:
    static ApplicationComponent *instance;

private:
    QGuiApplication *_app;
};

class MainViewModelComponent : public Provider<MainInteractor> {
public:
    MainViewModelComponent(ApplicationComponent *appComponent, ViewModel<MainInteractor, MainState> *viewModel)
        : _appComponent(appComponent),
          _viewModel(viewModel)
    {
    }

    virtual ~MainViewModelComponent() = default;

    ApplicationComponent *provideApplicationComponent() {
        return _appComponent;
    }

    ViewModel<MainInteractor, MainState> *provideViewModel() {
        return _viewModel;
    }

private:
    ApplicationComponent *_appComponent;
    ViewModel<MainInteractor, MainState> *_viewModel;
};

class SecondViewModelComponent : public Provider<ListInteractor> {
public:
    SecondViewModelComponent(ApplicationComponent *appComponent, ViewModel<ListInteractor, ListState> *viewModel)
        : _appComponent(appComponent),
          _viewModel(viewModel)
    {
    }

    virtual ~SecondViewModelComponent() = default;

    ApplicationComponent *provideApplicationComponent() {
        return _appComponent;
    }

    ViewModel<ListInteractor, ListState> *provideViewModel() {
        return _viewModel;
    }

private:
    ApplicationComponent *_appComponent;
    ViewModel<ListInteractor, ListState> *_viewModel;
};

#endif // DI_H
