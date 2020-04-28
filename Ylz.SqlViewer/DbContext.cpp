#include "DbContext.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

void DbContext::load(QSqlDatabase & db)
{
    if (!db.isOpen())
    {
        return;
    }
    //
    {    
        user_tables.clear();
        QSqlQuery query(db); //
        query.exec("select table_name from all_tables order by table_name");
        while (query.next())
        {
            user_tables << query.value(0).toString();
        }
    }

    {        
        user_procs.clear();
        QSqlQuery query(db); //存储过程      
        query.exec("select object_name from all_procedures where object_type='PROCEDURE' order by object_name");
        while (query.next())
        {
            user_procs << query.value(0).toString();
        }
    }

    {
        user_funcs.clear();
        QSqlQuery query(db); //函数      
        query.exec("select object_name from all_procedures where object_type='FUNCTION' order by object_name");
        while (query.next())
        {
            user_funcs << query.value(0).toString();
        }
    }

    {
        user_views.clear();
        QSqlQuery query(db); //视图
        query.exec("select view_name from all_views order by view_name");
        while (query.next())
        {
            user_views << query.value(0).toString();
        }
    }
}
