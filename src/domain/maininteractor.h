#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include "interactor.h"
#include "mainstate.h"

class MainInteractor : public Interactor<MainState> {
public:
    MainInteractor() = default;

    virtual ~MainInteractor() = default;

    virtual void update() = 0;
};

#endif // MAININTERACTOR_H
