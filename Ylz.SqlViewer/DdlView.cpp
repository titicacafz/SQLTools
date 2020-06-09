#include "DDLView.h"
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QTreeView>
#include <QHeaderView>
#include <QSqlError>
#include <QSqlQuery>

#include "DbConnection.h"
#include "GlobalContext.h"
#include "SQLEdit.h"
#include "CopyableTableView.h"
#include "Highlighter.h"
#include "CustomSqlModel.h"
#include "SearchEdit.h"

DdlView::DdlView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    init_view();
}

DdlView::~DdlView()
{
}

//初始化界面
void DdlView::init_view()
{
    m_search_edit = new SearchEdit(this);
    m_tree_view = new QTreeView(this);

    m_model = new QStandardItemModel(m_tree_view);

    QStandardItem* tables = new QStandardItem(QString(tr("Tables")));
    QStandardItem* views = new QStandardItem(QString(tr("Views")));
    QStandardItem* procedures = new QStandardItem(QString(tr("Procedures")));
    QStandardItem* functions = new QStandardItem(QString(tr("Functions")));
    //加载表，函数，过程，视图
    QSqlDatabase db = DbConnection::database();
    if (db.isOpen())
    {
        DbContext & dbContext = CONTEXT.db_context();
        dbContext.load(db);

        for (QList<QString>::iterator iter = dbContext.user_tables.begin(); iter != dbContext.user_tables.end(); iter++)
        {
            QStandardItem* itemChild = new QStandardItem(*iter);
            tables->appendRow(itemChild);
        }

        for (QList<QString>::iterator iter = dbContext.user_views.begin(); iter != dbContext.user_views.end(); iter++)
        {
            QStandardItem* itemChild = new QStandardItem(*iter);
            views->appendRow(itemChild);
        }

        for (QList<QString>::iterator iter = dbContext.user_procs.begin(); iter != dbContext.user_procs.end(); iter++)
        {
            QStandardItem* itemChild = new QStandardItem(*iter);
            procedures->appendRow(itemChild);
        }

        for (QList<QString>::iterator iter = dbContext.user_funcs.begin(); iter != dbContext.user_funcs.end(); iter++)
        {
            QStandardItem* itemChild = new QStandardItem(*iter);
            functions->appendRow(itemChild);
        }
    }
    m_model->appendRow(tables);
    m_model->appendRow(views);
    m_model->appendRow(procedures);
    m_model->appendRow(functions);

    m_tree_view->setModel(m_model);
    m_tree_view->header()->hide();
    m_tree_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_text_edit = new SqlEdit(this);
    Highlighter *highlighter = new Highlighter(m_text_edit->document());
    m_table_view = new CopyableTableView(this);
    m_table_view->setVisible(false);
    m_table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式
    m_table_view->setAlternatingRowColors(true);
    m_table_view->setVisible(false);

    //总体水平布局管理器
    QHBoxLayout *hboxLayout = new QHBoxLayout(this);

    //左侧垂直布局管理器
    QVBoxLayout *vboxLayout = new QVBoxLayout();
    vboxLayout->addWidget(m_search_edit);
    vboxLayout->addWidget(m_tree_view);

    hboxLayout->addLayout(vboxLayout);
    hboxLayout->addWidget(m_text_edit);
    hboxLayout->addWidget(m_table_view);
    hboxLayout->setStretchFactor(vboxLayout, 1);
    hboxLayout->setStretchFactor(m_text_edit, 2);
    hboxLayout->setStretchFactor(m_table_view, 2);
    setLayout(hboxLayout);

    connect(m_tree_view->selectionModel(), &QItemSelectionModel::currentChanged, this, &DdlView::on_current_changed);
    connect(m_search_edit, &QLineEdit::returnPressed, this, &DdlView::on_return_pressed);
}

void DdlView::on_current_changed(const QModelIndex &current, const QModelIndex &previous)
{
    QStandardItem* item = m_model->itemFromIndex(current);
    if (item == nullptr)
        return;

    QStandardItem* parent = item->parent();
    if (parent == nullptr)
        return;

    if (parent->text() == tr("Tables"))
    {
        show_table(item->text());
    }
    else if (parent->text() == tr("Views"))
    {
        show_view(item->text());
    }
    else if (parent->text() == tr("Procedures"))
    {
        show_procedure(item->text());
    }
    else if (parent->text() == tr("Functions"))
    {
        show_function(item->text());
    }
    else {
        //查DDL
        m_table_view->setVisible(false);
        m_text_edit->setVisible(true);
    }
}

void DdlView::show_table(const QString & name)
{
    //查表列等数据
    QString sql_text = "select "
        " a.column_name as \"Column\","
        " a.data_type as \"Type\","
        " a.data_length as \"Length\","
        " a.nullable  as \"Null able\","
        " a.data_default as \"Default\","
        " b.comments  as \"Comment\""
        " from all_tab_columns a, all_col_comments  b"
        " where"
        " a.table_name = '" + name + "'"
        " and b.table_name = '" + name + "'"
        "and a.column_name = b.column_name";
    m_table_view->setUpdatesEnabled(false);
    CustomSqlModel *model = new CustomSqlModel(this);
    model->setQuery(sql_text, DbConnection::database());
    QSqlError error = model->lastError();
    if (error.type() != QSqlError::NoError) {
        ;
    }
    else {
        m_table_view->setModel(model);
        m_table_view->setStyleSheet("QTableView{background-color: rgb(250, 250, 250);"
            "alternate-background-color: rgb(234, 234, 234);}");//设置表格颜色
        m_table_view->show();
        m_table_view->setUpdatesEnabled(true);
    }
    m_table_view->setVisible(true);
    m_text_edit->setVisible(false);
}

void DdlView::show_procedure(const QString & name)
{
    m_text_edit->clear();
    m_text_edit->appendPlainText("create or replace ");
    QString sql_text = "select text from all_source where name = '" + name + "' and type = 'PROCEDURE'";
    QSqlQuery query(DbConnection::database());
    query.exec(sql_text);
    while (query.next())
    {
        m_text_edit->appendPlainText(query.value(0).toString());
    }
    m_text_edit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    m_table_view->setVisible(false);
    m_text_edit->setVisible(true);
}

void DdlView::show_function(const QString & name)
{
    m_text_edit->clear();
    m_text_edit->appendPlainText("create or replace ");
    QString sql_text = "select text from all_source where name = '" + name + "' and type = 'FUNCTION'";
    QSqlQuery query(DbConnection::database());
    query.exec(sql_text);
    while (query.next())
    {
        m_text_edit->appendPlainText(query.value(0).toString());
    }
    m_text_edit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    m_table_view->setVisible(false);
    m_text_edit->setVisible(true);
}

void DdlView::show_view(const QString & name)
{
    m_text_edit->clear();
    m_text_edit->appendPlainText("create or replace view " + name + " as ");
    QString sql_text = "select text from all_views where view_name='" + name + "'";
    QSqlQuery query(DbConnection::database());
    query.exec(sql_text);
    while (query.next())
    {
        m_text_edit->appendPlainText(query.value(0).toString());
    }
    m_text_edit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
    m_table_view->setVisible(false);
    m_text_edit->setVisible(true);
}

void DdlView::on_return_pressed()
{
    //统一转大写
    QString toSearch = m_search_edit->text().trimmed().toUpper();
    //
    if (toSearch.isEmpty())
        return;

    m_tree_view->collapseAll();
    //夫节点
    for (int i = 0; i < m_model->rowCount(); i++)
    {
        QStandardItem *item = m_model->item(i);
        //子节点
        for (int j = 0; j < item->rowCount(); j++)
        {
            QStandardItem * childitem = item->child(j);
            if (childitem->text() == toSearch)
            {
                m_tree_view->expand(item->index());
                QItemSelectionModel * selectModel = m_tree_view->selectionModel();
                selectModel->select(childitem->index(), QItemSelectionModel::Select);
                emit selectModel->currentChanged(childitem->index(), childitem->index());
                return;
            }
        }
    }
}