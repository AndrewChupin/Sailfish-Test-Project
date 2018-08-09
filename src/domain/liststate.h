#ifndef LISTSTATE_H
#define LISTSTATE_H

#include <QString>
#include <QVector>

class ListState
{
public:
    static ListState newState(const QVector<QString> &items, int page) {
        return ListState(items, page);
    }

    static ListState newMoreLoadingState(const QVector<QString> &items, int page) {
        return ListState(items, page, "", true, false);
    }

    static ListState newFinishedState(const QVector<QString> &items,  int page) {
        return ListState(items, page, "", false, true);
    }

    static const ListState &errorState() {
        return ERROR_STATE;
    }

    ListState();
    ListState(const QVector<QString> &items,
              int page = 0,
              const QString &error = "",
              bool isLoading = false,
              bool isLastPage = false);
    ListState(const ListState &state);

    ListState &operator =(const ListState &state);

    const QVector<QString> &items() const;

    int page() const;

    const QString error() const;

    bool isLoading() const;

    bool isLastPage() const;

private:
    static ListState ERROR_STATE;

private:
    QVector<QString> _items;
    int _page;
    QString _error;
    bool _loading;
    bool _lastPage;
};

#endif // LISTSTATE_H
