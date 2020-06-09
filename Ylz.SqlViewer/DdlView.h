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

    //��ʼ������
    void init_view();

    //QTreeViewѡ��ڵ�仯�¼�
    void on_current_changed(const QModelIndex &current, const QModelIndex &previous);

    //��ʾ��ṹ
    void show_table(const QString & name);

    //��ʾ�ű�Դ��
    void show_procedure(const QString & name);

    //��ʾ�ű�Դ��
    void show_function(const QString & name);

    //��ʾ��ͼ
    void show_view(const QString & name);

    //����������س�
    void on_return_pressed();
};
