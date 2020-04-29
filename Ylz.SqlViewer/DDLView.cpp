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

DDLView::DDLView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    initView();
}

DDLView::~DDLView()
{
}

//初始化界面
void DDLView::initView()
{
    searchEdit = new SearchEdit(this);    
    treeView = new QTreeView(this);
    
    model = new QStandardItemModel(treeView);      

    QStandardItem* tables = new QStandardItem(QString(tr("Tables")));
    QStandardItem* views = new QStandardItem(QString(tr("Views")));
    QStandardItem* procedures = new QStandardItem(QString(tr("Procedures")));
    QStandardItem* functions = new QStandardItem(QString(tr("Functions")));
    //加载表，函数，过程，视图
    QSqlDatabase db = DbConnection::database();
    if (db.isOpen())
    {
        DbContext & dbContext = CONTEXT.dbContext;
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
    model->appendRow(tables);
    model->appendRow(views);
    model->appendRow(procedures);
    model->appendRow(functions);
    
    treeView->setModel(model);    
    treeView->header()->hide();
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    textEdit = new SQLEdit(this);
    Highlighter *highlighter = new Highlighter(textEdit->document());
    tableView = new CopyableTableView(this);
    tableView->setVisible(false);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式
    tableView->setAlternatingRowColors(true);
    tableView->setVisible(false);
    
    
    //总体水平布局管理器
    QHBoxLayout *hboxLayout = new QHBoxLayout(this);

    //左侧垂直布局管理器
    QVBoxLayout *vboxLayout = new QVBoxLayout();
    vboxLayout->addWidget(searchEdit);
    vboxLayout->addWidget(treeView);

    hboxLayout->addLayout(vboxLayout);
    hboxLayout->addWidget(textEdit);
    hboxLayout->addWidget(tableView);
    hboxLayout->setStretchFactor(vboxLayout, 1);
    hboxLayout->setStretchFactor(textEdit, 2);
    hboxLayout->setStretchFactor(tableView, 2);
    setLayout(hboxLayout);

    connect(treeView->selectionModel(), &QItemSelectionModel::currentChanged, this, &DDLView::onCurrentChanged);
    connect(searchEdit, &QLineEdit::returnPressed, this, &DDLView::onReturnPressed);
}

void DDLView::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QStandardItem* item = model->itemFromIndex(current);
    if (item == nullptr)
        return;
    
    QStandardItem* parent = item->parent();
    if (parent == nullptr)
        return;

    if (parent->text() == tr("Tables"))
    {
        showTable(item->text());
    }
    else if (parent->text() == tr("Views"))
    {
        showView(item->text());
    }
    else if (parent->text() == tr("Procedures"))
    {
        showProcedure(item->text());
    }
    else if (parent->text() == tr("Functions"))
    {
        showFunction(item->text());
    }
    else {
        //查DDL
        tableView->setVisible(false);
        textEdit->setVisible(true);
    }
    
}

void DDLView::showTable(const QString & name)
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
    tableView->setUpdatesEnabled(false);
    CustomSqlModel *model = new CustomSqlModel(this);
    model->setQuery(sql_text, DbConnection::database());
    QSqlError error = model->lastError();
    if (error.type() != QSqlError::NoError) {
        ;
    }
    else {
        tableView->setModel(model);
        tableView->setStyleSheet("QTableView{background-color: rgb(250, 250, 250);"
            "alternate-background-color: rgb(234, 234, 234);}");//设置表格颜色
        tableView->show();
        tableView->setUpdatesEnabled(true);
    }
    tableView->setVisible(true);
    textEdit->setVisible(false);
}

void DDLView::showProcedure(const QString & name)
{
    textEdit->clear();
    textEdit->appendPlainText("create or replace ");
    QString sql_text = "select text from all_source where name = '"+name+"' and type = 'PROCEDURE'";
    QSqlQuery query(DbConnection::database());
    query.exec(sql_text);
    while (query.next())
    {
        textEdit->appendPlainText(query.value(0).toString());
    }
    textEdit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    tableView->setVisible(false);
    textEdit->setVisible(true);
}

void DDLView::showFunction(const QString & name)
{
    textEdit->clear();
    textEdit->appendPlainText("create or replace ");
    QString sql_text = "select text from all_source where name = '" + name + "' and type = 'FUNCTION'";
    QSqlQuery query(DbConnection::database());
    query.exec(sql_text);
    while (query.next())
    {
        textEdit->appendPlainText(query.value(0).toString());
    }
    textEdit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    tableView->setVisible(false);
    textEdit->setVisible(true);
}

void DDLView::showView(const QString & name)
{
    textEdit->clear();
    textEdit->appendPlainText("create or replace view "+name+" as ");
    QString sql_text = "select text from all_views where view_name='"+name+"'";
    QSqlQuery query(DbConnection::database());
    query.exec(sql_text);
    while (query.next())
    {
        textEdit->appendPlainText(query.value(0).toString());
    }
    textEdit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
    tableView->setVisible(false);
    textEdit->setVisible(true);
}

void DDLView::onReturnPressed()
{
    //统一转大写
    QString toSearch = searchEdit->text().trimmed().toUpper();
    //
    if (toSearch.isEmpty())
        return;

    treeView->collapseAll(); 
    //夫节点
    for (int i = 0; i < model->rowCount(); i++)
    {
        QStandardItem *item = model->item(i);          
        //子节点
        for (int j = 0; j < item->rowCount(); j++)
        {
            QStandardItem * childitem = item->child(j);            
            if (childitem->text() == toSearch)
            {
                treeView->expand(item->index());
                QItemSelectionModel * selectModel= treeView->selectionModel();
                selectModel->select(childitem->index(), QItemSelectionModel::Select);
                emit selectModel->currentChanged(childitem->index(), childitem->index());
                return;
            }
        }
    }
}
