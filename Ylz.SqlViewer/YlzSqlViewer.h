#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_YlzSqlViewer.h"


class QTimer;
class QNetworkAccessManager;
class QNetworkReply;
class Config;

class YlzSqlViewer : public QMainWindow
{
    Q_OBJECT

public:
    YlzSqlViewer(QWidget *parent = Q_NULLPTR);

private:
    Ui::YlzSqlViewerClass ui;

    QNetworkAccessManager *manager;

    QStatusBar * status_bar;

    QTimer * timer;

    long long position;

    //开始监控
    void onStart();

    //停止监控
    void onStop();  

    //清空显示日志
    void onClear();

    //打开配置文件
    void onSettings();

    //保存
    void onSave();

    //http接口交互完成
    void onUpdate(QNetworkReply *reply);

    //日志下载
    void onLogDownload();

    //数据库查看工具
    void onDatabase();

    //定时器，先这么用
    void onTimer();
    
};
