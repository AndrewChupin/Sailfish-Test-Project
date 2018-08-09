#include "firstpageviewmodel.h"
#include "../di/diproduct.h"

FirstPageViewModel::FirstPageViewModel(QObject *parent)
    : ViewModel<MainInteractor, MainState>(parent),
      _message("Hello World"),
      _loading(false)
{
}

void FirstPageViewModel::inject()
{
    QSharedPointer<MainViewModelModule> module(new MainViewModelModule(ApplicationComponent::getInstance(), this));
    setInteractor(module->provide());
}

QString FirstPageViewModel::message()
{
    return _message;
}

bool FirstPageViewModel::isLoading()
{
    return _loading;
}

void FirstPageViewModel::update()
{
    getInteractor()->update();
}

void FirstPageViewModel::onCreated()
{
    ViewModel<MainInteractor, MainState>::onCreated();
}

void FirstPageViewModel::onActivating()
{
    ViewModel<MainInteractor, MainState>::onActivating();
}

void FirstPageViewModel::onDeactivating()
{
    ViewModel<MainInteractor, MainState>::onDeactivating();
}

void FirstPageViewModel::updateState(const MainState &state)
{
    _message = state.message();
    _loading = state.isLoading();
    emit stateChanged();
}
