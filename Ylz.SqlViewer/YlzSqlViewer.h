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

    //��ʼ���
    void onStart();

    //ֹͣ���
    void onStop();  

    //�����ʾ��־
    void onClear();

    //�������ļ�
    void onSettings();

    //����
    void onSave();

    //http�ӿڽ������
    void onUpdate(QNetworkReply *reply);

    //��־����
    void onLogDownload();

    //���ݿ�鿴����
    void onDatabase();

    //��ʱ��������ô��
    void onTimer();
    
};
