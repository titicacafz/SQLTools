#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_YlzSqlViewer.h"



class YlzSqlViewer : public QMainWindow
{
    Q_OBJECT

public:
    YlzSqlViewer(QWidget *parent = Q_NULLPTR);

private:
    Ui::YlzSqlViewerClass ui;

 
    QStatusBar * status_bar;
    

    //�򿪼��
    void onMonitor();

    //�������ļ�
    void onSettings();

    //��־����
    void onLogDownload();

    //���ݿ�鿴����
    void onDatabase();

};
