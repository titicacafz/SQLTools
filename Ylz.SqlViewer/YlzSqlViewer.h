#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_YlzSqlViewer.h"


class DatabaseView;
class TraceView;
class DDLView;
class QWidget;


class YlzSqlViewer : public QMainWindow
{
    Q_OBJECT

public:
    YlzSqlViewer(QWidget *parent = Q_NULLPTR);

private:
    Ui::YlzSqlViewerClass ui;
 
    QStatusBar * status_bar; 

    DatabaseView * databaseView;
    TraceView *traceView;
    DDLView * ddlView;

    //打开监控
    void onMonitor();

    //打开配置文件
    void onSettings();

    //日志下载
    void onLogDownload();

    //数据库查看工具
    void onDatabase();

    //DDL
    void onDDL();

    //显示子窗体
    void onShowChild(QWidget *);
};
