#pragma once

class QSettings;
class QString;

class Config final
{
public:
    Config();
    ~Config();

    //获取
    QString get(const QString & name);

    //加载配置文件内容
    void load();

private:
    QSettings *ini;
};
