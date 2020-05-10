#pragma once
#include <QList>
#include <QString>

class QSqlDatabase;

class DbContext final
{
public:

    void load(QSqlDatabase & db);

    //�û����б�
    QList<QString> user_tables;

    //�û����д洢����
    QList<QString> user_procs;

    //����
    QList<QString> user_funcs;

    //��ͼ
    QList<QString> user_views;
};

