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

    //初始化界面
    void initView();

    //QTreeView选择节点变化事件
    void onCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

    //显示表结构
    void showTable(const QString & name);

    //显示脚本源码
    void showProcedure(const QString & name);

    //显示脚本源码
    void showFunction(const QString & name);

    //显示视图
    void showView(const QString & name);

    //搜索框输入回车
    void onReturnPressed();

};
