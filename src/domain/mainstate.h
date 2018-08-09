#ifndef MAINSTATE_H
#define MAINSTATE_H

#include <QString>

class MainState
{
public:
    static MainState newState(const QString &message) {
        return MainState(message);
    }

    static const MainState &errorState() {
        return ERROR_STATE;
    }

    static const MainState &loadingState() {
        return LOADING_STATE;
    }

    MainState();

    MainState(const MainState &state);

    MainState(const QString &message,
              const QString &error = "",
              bool isLoading = false);

    MainState &operator =(const MainState &state);

    const QString &message() const;

    const QString &error() const;

    bool isLoading() const;

private:
    static MainState ERROR_STATE;
    static MainState LOADING_STATE;

private:
    QString _message;
    QString _error;
    bool _loading;
};

#endif // MAINSTATE_H
