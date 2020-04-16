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
    CopyableTableView     * tableView;
    ErrorEdit * errorEdit;

    //���ݿ�
    QSqlDatabase db;

    //��ʼ������
    void initView();

    //�¼��ҽ�
    void initEvent();

    //�������ݿ�
    void onConnectDb();


    //����SQL
    void onRunSql();

    //copy
    void onCopy();
};
