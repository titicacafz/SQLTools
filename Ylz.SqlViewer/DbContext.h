#pragma once
#include <QList>
#include <QString>

class QSqlDatabase;

class DbContext final
{
public:

    void load(QSqlDatabase & db);

    //用户所有表
    QList<QString> user_tables;

    //用户所有存储过程
    QList<QString> user_procs;

    //函数
    QList<QString> user_funcs;

    //视图
    QList<QString> user_views;
};

