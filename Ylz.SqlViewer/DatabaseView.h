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

    //��ʼ������
    void init_view();

    //�¼��ҽ�
    void init_event();

    //�������ݿ�
    void on_connect_db();

    //����SQL
    void on_run_sql();
};
