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

    //显示的日志的编辑框
    QPlainTextEdit * m_text_edit;

    QTimer * m_timer;

    long long m_position;

    QNetworkAccessManager * m_manager;

    //初始化界面
    void init_view();

    //事件挂接
    void init_event();

    //开始监控
    void on_start();

    //停止监控
    void on_stop();

    //清空显示日志
    void on_clear();

    //保存
    void on_save();

    //http接口交互完成
    void on_update(QNetworkReply *reply);

    //定时器，先这么用
    void on_timer();
};
