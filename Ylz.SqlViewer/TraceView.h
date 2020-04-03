#pragma once

#include <QWidget>
#include "ui_TraceView.h"

class QPlainTextEdit;
class QNetworkAccessManager;
class QNetworkReply;

class TraceView : public QWidget
{
    Q_OBJECT

public:
    TraceView(QWidget *parent = Q_NULLPTR);
    ~TraceView();

private:
    Ui::TraceView ui;

    //��ʾ����־�ı༭��
    QPlainTextEdit * textEdit;

    QTimer * timer;

    long long position;

    QNetworkAccessManager *manager;
    

    //��ʼ������
    void initView();

    //�¼��ҽ�
    void initEvent();


    //��ʼ���
    void onStart();

    //ֹͣ���
    void onStop();

    //�����ʾ��־
    void onClear();

    //����
    void onSave();

    //http�ӿڽ������
    void onUpdate(QNetworkReply *reply);

    //��ʱ��������ô��
    void onTimer();
};
