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

    QTreeView *m_tree_view;
    SQLEdit * m_text_edit;
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
