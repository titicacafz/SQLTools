#pragma once
/***
���ݿ����ӹ�����
*/
#include <QSqlDatabase>

class DbConnection final
{
public:
    static QSqlDatabase database();
};

