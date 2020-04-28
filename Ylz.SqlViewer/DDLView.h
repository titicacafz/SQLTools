#pragma once

#include <QWidget>
#include "ui_DDLView.h"

class QTreeView;
class SQLEdit;
class CopyableTableView;
class QStandardItemModel;
class SearchEdit;

class DDLView : public QWidget
{
    Q_OBJECT

public:
    DDLView(QWidget *parent = Q_NULLPTR);
    ~DDLView();

private:
    Ui::DDLView ui;

    QTreeView *treeView;
    SQLEdit * textEdit;
    CopyableTableView* tableView;
    QStandardItemModel* model;
    SearchEdit *searchEdit;

    //��ʼ������
    void initView();

    //QTreeViewѡ��ڵ�仯�¼�
    void onCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

    //��ʾ��ṹ
    void showTable(const QString & name);

    //��ʾ�ű�Դ��
    void showProcedure(const QString & name);

    //��ʾ�ű�Դ��
    void showFunction(const QString & name);

    //��ʾ��ͼ
    void showView(const QString & name);

    //����������س�
    void onReturnPressed();

};
