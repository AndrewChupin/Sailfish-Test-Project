#ifndef LISTINTERACTOR_H
#define LISTINTERACTOR_H

#include "interactor.h"
#include "liststate.h"

class ListInteractor : public Interactor<ListState> {
public:
    ListInteractor() = default;
    virtual ~ListInteractor() = default;

    virtual void loadMore() = 0;
};

#endif // LISTINTERACTOR_H
