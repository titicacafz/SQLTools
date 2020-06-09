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
    ini->beginGroup(ini->value("env").toString());
    return QString(ini->value(name).toString());
}

//���������ļ�����
void Config::load()
{
    //�����ļ�
    QString path = QCoreApplication::applicationDirPath();
    ini = new QSettings(path + "/setting.txt", QSettings::IniFormat);
    QString env;
    ini->beginGroup("General");
    env = ini->value("env").toString();
    ini->endGroup();

    ini->beginGroup(env);
    //����������
    QString server(ini->value("server").toString());
    QString remoteIp(ini->value("remoteIp").toString());
    QString fullLogUrl(ini->value("fullLogUrl").toString());

    //���ݿ��������
    QString db_driver(ini->value("db_driver").toString());
    QString db_host(ini->value("db_host").toString());
    QString db_port(ini->value("db_port").toString());
    QString db_database(ini->value("db_database").toString());
    QString db_user(ini->value("db_user").toString());
    QString db_pass(ini->value("db_pass").toString());
    ini->endGroup();
}