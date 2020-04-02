#include "Config.h"
#include <QSettings>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

Config::Config()
{
    //�����ļ�
    load();
}

Config::~Config()
{
    delete ini;
}

//��ȡ
QString Config::get(const QString & name)
{   
    return QString(ini->value(name).toString());
}

//���������ļ�����
void Config::load()
{
    //�����ļ�
    QString path = QCoreApplication::applicationDirPath();
    ini = new QSettings(path + "/setting.txt", QSettings::IniFormat);
    QString server(ini->value("server").toString());    
    QString remoteIp(ini->value("remoteIp").toString());    
    QString fullLogUrl(ini->value("fullLogUrl").toString());

    QFile file(path);
    //�ļ����ھͲ�������
    if (file.exists())
    {
        return;
    }
    ini->setValue("server", server);
    ini->setValue("remoteIp", remoteIp);
    ini->setValue("fullLogUrl", fullLogUrl);
}
