#include "DbConnection.h"
#include "GlobalContext.h"

QSqlDatabase DbConnection::database()
{
    Config& config = CONTEXT.config();
    if (!QSqlDatabase::contains("hisdb")) {
        QSqlDatabase db = QSqlDatabase::addDatabase(config.get("db_driver"), "hisdb");//QOCI
        db.setPort(config.get("db_port").toInt());
        db.setHostName(config.get("db_host"));
        db.setDatabaseName(config.get("db_database"));
        db.setUserName(config.get("db_user"));
        db.setPassword(config.get("db_pass"));
    }

    return QSqlDatabase::database("hisdb");
}