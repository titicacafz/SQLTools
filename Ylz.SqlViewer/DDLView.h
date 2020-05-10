#pragma once

#include <QWidget>
#include "ui_DdlView.h"

class QTreeView;
class SqlEdit;
class CopyableTableView;
class QStandardItemModel;
class SearchEdit;

class DdlView : public QWidget
{
    Q_OBJECT

public:
    DdlView(QWidget *parent = Q_NULLPTR);
    ~DdlView();

private:
    Ui::DDLView ui;

    QTreeView *m_tree_view;
    SqlEdit * m_text_edit;
    CopyableTableView * m_table_view;
    QStandardItemModel* m_model;
    SearchEdit * m_search_edit;

    //初始化界面
    void init_view();

    //QTreeView选择节点变化事件
    void on_current_changed(const QModelIndex &current, const QModelIndex &previous);

    //显示表结构
    void show_table(const QString & name);

    //显示脚本源码
    void show_procedure(const QString & name);

    //显示脚本源码
    void show_function(const QString & name);

    //显示视图
    void show_view(const QString & name);

    //搜索框输入回车
    void on_return_pressed();

};
