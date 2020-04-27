#pragma once

#include <QWidget>
#include <QSqlDatabase>
#include "ui_DatabaseView.h"

class SQLEdit;
class ErrorEdit;
class CopyableTableView;
class QSqlDatabase;

class DatabaseView : public QWidget
{
    Q_OBJECT

public:
    DatabaseView(QWidget *parent = Q_NULLPTR);
    ~DatabaseView();

private:
    Ui::DatabaseView ui;

    SQLEdit * textEdit;
    ErrorEdit * errorEdit;
    CopyableTableView* tableView;

    //初始化界面
    void initView();

    //事件挂接
    void initEvent();

    //连接数据库
    void onConnectDb();


    //运行SQL
    void onRunSql();

};
