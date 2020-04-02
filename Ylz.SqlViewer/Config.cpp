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
    QString server(ini->value("server").toString());    
    QString remoteIp(ini->value("remoteIp").toString());    
    QString fullLogUrl(ini->value("fullLogUrl").toString());

    QFile file(path);
    //文件存在就不保存了
    if (file.exists())
    {
        return;
    }
    ini->setValue("server", server);
    ini->setValue("remoteIp", remoteIp);
    ini->setValue("fullLogUrl", fullLogUrl);
}
