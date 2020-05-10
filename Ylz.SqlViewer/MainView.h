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

    //�򿪼��
    void onMonitor();

    //�������ļ�
    void onSettings();

    //��־����
    void onLogDownload();

    //���ݿ�鿴����
    void onDatabase();

    //DDL
    void onDDL();    
};
