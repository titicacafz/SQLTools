#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainViewer.h"


class DatabaseView;
class TraceView;
class DDLView;
class QMdiSubWindow;


class MainViewer : public QMainWindow
{
    Q_OBJECT

public:
    MainViewer(QWidget *parent = Q_NULLPTR);

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
};
