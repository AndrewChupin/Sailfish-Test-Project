#ifndef DIPRODUCT_H
#define DIPRODUCT_H

#include "di.h"
#include "../data/maindatasource.h"
#include "../data/listdatasource.h"
#include "../domain/mainmodel.h"
#include "../domain/listmodel.h"

class MainDataModule : public MainDataComponent
{
public:
    MainDataModule()
        : _mainSource(new MainDataSource())
    {
    }
    virtual ~MainDataModule() = default;

    virtual QSharedPointer<MainSource> provide() override {
        return _mainSource;
    }

private:
    QSharedPointer<MainSource> _mainSource;
};

class ListDataModule : public ListDataComponent
{
public:
    ListDataModule()
        : _listSource(new ListDataSource())
    {
    }
    virtual ~ListDataModule() = default;

    virtual QSharedPointer<ListSource> provide() override {
        return _listSource;
    }

private:
    QSharedPointer<ListSource> _listSource;
};

class DataModule : public DataComponent {
public:
    DataModule()
        : _mainComponent(new MainDataModule()),
          _listComponent(new ListDataModule())
    {
    }

    virtual QSharedPointer<MainDataComponent> provideMainDataComponent() override {
        return _mainComponent;
    }

    virtual QSharedPointer<ListDataComponent> provideListDataComponent() override {
        return _listComponent;
    }

private:
    QSharedPointer<MainDataComponent> _mainComponent;
    QSharedPointer<ListDataComponent> _listComponent;
};

class MainModelModule : public MainModelComponent {
public:
    MainModelModule(DomainComponent *domainComponent)
        : MainModelComponent(domainComponent),
          _mainModel(new MainModel(getDomainComponent()
                                    ->getApplicationComponent()
                                    ->provideApplication(),
                                   getDomainComponent()
                                    ->getApplicationComponent()
                                    ->provideDataComponent()
                                    ->provideMainDataComponent()
                                    ->provide()))
    {
    }

    virtual QSharedPointer<MainInteractor> provide() override {
        return _mainModel;
    }

private:
    QSharedPointer<MainInteractor> _mainModel;
};

class DomainModule : public DomainComponent {
public:
    DomainModule(ApplicationComponent *appComponent)
        : DomainComponent(appComponent),
          _mainComponent(new MainModelModule(this))
    {
    }

    virtual QSharedPointer<MainModelComponent> provideMainModelComponent() override {
        return _mainComponent;
    }

private:
    QSharedPointer<MainModelComponent> _mainComponent;
};

class ApplicationModule : public ApplicationComponent {
public:
    ApplicationModule(QGuiApplication *app)
        : ApplicationComponent(app),
          _mainComponent(new DataModule()),
          _domainComponent(new DomainModule(this))
    {
    }

    virtual QSharedPointer<DataComponent> provideDataComponent() override {
        return _mainComponent;
    }

    virtual QSharedPointer<DomainComponent> provideDomainComponent() override {
        return _domainComponent;
    }

private:
    QSharedPointer<DataComponent> _mainComponent;
    QSharedPointer<DomainComponent> _domainComponent;
};

class MainViewModelModule : public MainViewModelComponent {
public:
    MainViewModelModule(ApplicationComponent *appComponent, ViewModel<MainInteractor, MainState> *viewModel)
        : MainViewModelComponent(appComponent, viewModel),
          _mainModel(appComponent->provideDomainComponent()->provideMainModelComponent()->provide())
    {
    }

    virtual QSharedPointer<MainInteractor> provide() override {
        return _mainModel;
    }

private:
    QSharedPointer<MainInteractor> _mainModel;
};

class SecondViewModelModule : public SecondViewModelComponent {
public:
    SecondViewModelModule(ApplicationComponent *appComponent, ViewModel<ListInteractor, ListState> *viewModel)
        : SecondViewModelComponent(appComponent, viewModel),
          _secondModel(new ListModel(viewModel, appComponent->provideDataComponent()->provideListDataComponent()->provide()))
    {
    }

    virtual QSharedPointer<ListInteractor> provide() override {
        return _secondModel;
    }

private:
    QSharedPointer<ListInteractor> _secondModel;
};

#endif // DIPRODUCT_H
