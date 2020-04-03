#pragma once

#include <QWidget>
#include <QSqlDatabase>
#include "ui_DatabaseView.h"

class QPlainTextEdit;
class QTableView;
class QSqlDatabase;

class DatabaseView : public QWidget
{
    Q_OBJECT

public:
    DatabaseView(QWidget *parent = Q_NULLPTR);
    ~DatabaseView();

private:
    Ui::DatabaseView ui;

    QPlainTextEdit * textEdit;
    QTableView     * tableView;

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
};
