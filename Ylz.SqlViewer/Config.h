#pragma once

class QSettings;
class QString;

class Config final
{
public:
    Config();
    ~Config();

    //��ȡ
    QString get(const QString & name);

    //���������ļ�����
    void load();

private:
    QSettings *ini;
};
