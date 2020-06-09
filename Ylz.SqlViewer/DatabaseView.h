#pragma once

#include <QWidget>
#include <QSqlDatabase>
#include "ui_DatabaseView.h"

class SqlEdit;
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

    SqlEdit * m_text_edit;
    ErrorEdit * m_error_edit;
    CopyableTableView* m_table_view;

    //初始化界面
    void init_view();

    //事件挂接
    void init_event();

    //连接数据库
    void on_connect_db();

    //运行SQL
    void on_run_sql();
};
