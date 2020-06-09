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

    //�򿪼��
    void on_monitor();

    //�������ļ�
    void on_settings();

    //��־����
    void on_log_download();

    //���ݿ�鿴����
    void on_database();

    //DDL
    void on_ddl();
};
