#include "mainstate.h"

MainState MainState::ERROR_STATE = MainState("", "Somthing gone wrong", false);
MainState MainState::LOADING_STATE = MainState("Loading...", "", true);

MainState::MainState()
    : _message(""),
      _error(""),
      _loading(false)
{

}

MainState::MainState(const MainState &state)
{
    _message = state._message;
    _error = state._error;
    _loading = state._loading;
}

MainState::MainState(const QString &message,
                     const QString &error,
                     bool isLoading)
    : _message(message),
      _error(error),
      _loading(isLoading)
{

}

MainState &MainState::operator =(const MainState &state)
{
    _message = state._message;
    _error = state._error;
    _loading = state._loading;
    return *this;
}

const QString &MainState::message() const
{
    return _message;
}

const QString &MainState::error() const
{
    return _error;
}

bool MainState::isLoading() const
{
    return _loading;
}
