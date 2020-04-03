#include "CustomSqlModel.h"

CustomSqlModel::CustomSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}


QVariant CustomSqlModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);     
    return value.toString();
}
