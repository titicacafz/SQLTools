#pragma once
/***
数据库连接管理类
*/
#include <QSqlDatabase>

class DbConnection final
{
public:
    static QSqlDatabase database();
};

