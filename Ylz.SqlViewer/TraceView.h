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
    QPlainTextEdit * m_text_edit;

    QTimer * m_timer;

    long long m_position;

    QNetworkAccessManager * m_manager;

    //��ʼ������
    void init_view();

    //�¼��ҽ�
    void init_event();

    //��ʼ���
    void on_start();

    //ֹͣ���
    void on_stop();

    //�����ʾ��־
    void on_clear();

    //����
    void on_save();

    //http�ӿڽ������
    void on_update(QNetworkReply *reply);

    //��ʱ��������ô��
    void on_timer();
};
