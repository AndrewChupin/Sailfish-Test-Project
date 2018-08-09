#ifndef SECONDPAGEPRESENTER_H
#define SECONDPAGEPRESENTER_H

#include "viewmodel.h"
#include "../di/di.h"

class StringListViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit StringListViewModel(QObject *parent = nullptr);

    enum ListRoles {
            NameRole = Qt::UserRole + 1
        };

    virtual QHash<int, QByteArray> roleNames() const override;

    virtual int rowCount(const QModelIndex&) const override;

    virtual QVariant data(const QModelIndex &index, int role) const override;

    void setItems(const QVector<QString> &items);

private:
    QVector<QString> _items;
};

class SecondPageViewModel : public ViewModel<ListInteractor, ListState>
{
    Q_OBJECT
    Q_PROPERTY(StringListViewModel* listModel READ listModel NOTIFY stateChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY stateChanged)
    Q_PROPERTY(bool isLastPage READ isLastPage NOTIFY stateChanged)

public:
    explicit SecondPageViewModel(QObject *parent = nullptr);

    Q_INVOKABLE virtual void onCreated() override;

    Q_INVOKABLE virtual void onActivating() override;

    Q_INVOKABLE virtual void onDeactivating() override;

    Q_INVOKABLE void loadMore();

    StringListViewModel *listModel();
    bool isLoading();
    bool isLastPage();

signals:
    void stateChanged();

protected:
    virtual void inject() override;

    virtual void updateState(const ListState &state) override;

private:
    QScopedPointer<StringListViewModel> _listModel;
    bool _loading;
    bool _lastPage;
};

#endif // SECONDPAGEPRESENTER_H
