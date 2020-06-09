#pragma once
#include <QSqlQueryModel>

class CustomSqlModel :
    public QSqlQueryModel
{
    Q_OBJECT

public:
    CustomSqlModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;
};
