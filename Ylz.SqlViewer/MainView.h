#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainViewer.h"

class DatabaseView;
class TraceView;
class DdlView;
class QMdiSubWindow;

class MainViewer : public QMainWindow
{
    Q_OBJECT

public:
    MainViewer(QWidget *parent = Q_NULLPTR);

private:
    Ui::YlzSqlViewerClass ui;

    QStatusBar * m_status_bar;

    DatabaseView * m_database_view;
    TraceView *m_trace_view;
    DdlView * m_ddl_view;

    //打开监控
    void on_monitor();

    //打开配置文件
    void on_settings();

    //日志下载
    void on_log_download();

    //数据库查看工具
    void on_database();

    //DDL
    void on_ddl();
};
