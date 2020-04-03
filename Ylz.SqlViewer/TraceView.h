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
    QPlainTextEdit * textEdit;

    QTimer * timer;

    long long position;

    QNetworkAccessManager *manager;
    

    //初始化界面
    void initView();

    //事件挂接
    void initEvent();


    //开始监控
    void onStart();

    //停止监控
    void onStop();

    //清空显示日志
    void onClear();

    //保存
    void onSave();

    //http接口交互完成
    void onUpdate(QNetworkReply *reply);

    //定时器，先这么用
    void onTimer();
};
