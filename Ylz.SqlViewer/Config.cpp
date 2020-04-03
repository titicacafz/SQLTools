#include "Config.h"
#include <QSettings>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

Config::Config()
{
    //配置文件
    load();
}

Config::~Config()
{
    delete ini;
}

//获取
QString Config::get(const QString & name)
{   
    return QString(ini->value(name).toString());
}

//加载配置文件内容
void Config::load()
{
    //配置文件
    QString path = QCoreApplication::applicationDirPath();
    ini = new QSettings(path + "/setting.txt", QSettings::IniFormat);
    //监控相关设置
    QString server(ini->value("server").toString());    
    QString remoteIp(ini->value("remoteIp").toString());    
    QString fullLogUrl(ini->value("fullLogUrl").toString());

    //数据库相关设置
    QString db_driver(ini->value("db_driver").toString());
    QString db_host(ini->value("db_host").toString());    
    QString db_port(ini->value("db_port").toString());    
    QString db_database(ini->value("db_database").toString());    
    QString db_user(ini->value("db_user").toString());    
    QString db_pass(ini->value("db_pass").toString());   

    QFile file(path);
    //文件存在就不保存了
    if (file.exists())
    {
        return;
    }
    ini->setValue("server", server);
    ini->setValue("remoteIp", remoteIp);
    ini->setValue("fullLogUrl", fullLogUrl);
    ini->setValue("db_driver", db_driver);
    ini->setValue("db_host", db_host);
    ini->setValue("db_port", db_port);
    ini->setValue("db_database", db_database);
    ini->setValue("db_user", db_user);
    ini->setValue("db_pass", db_pass);
}
