#include "DatabaseView.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

#include "highlighter.h"
#include "GlobalContext.h"
#include "CustomSqlModel.h"
#include "SQLEdit.h"
#include "ErrorEdit.h"
#include "CopyableTableView.h"
#include "DbConnection.h"

DatabaseView::DatabaseView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    init_view();
    init_event();
}

DatabaseView::~DatabaseView()
{
}

void DatabaseView::init_view()
{
    QToolBar * toolbar = new QToolBar(this);
    toolbar->addAction(ui.actionConnectDb);
    toolbar->addAction(ui.actionRunSQL);

    m_text_edit = new SqlEdit(this);
    Highlighter *highlighter = new Highlighter(m_text_edit->document());
    m_table_view = new CopyableTableView(this);
    m_table_view->setVisible(false);
    m_table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式
    m_table_view->setAlternatingRowColors(true);
    m_error_edit = new ErrorEdit(this);
    m_error_edit->setVisible(false);
    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addWidget(toolbar);
    vboxLayout->addWidget(m_text_edit);
    vboxLayout->addWidget(m_table_view);
    vboxLayout->addWidget(m_error_edit);
    setLayout(vboxLayout);
}

void DatabaseView::init_event()
{
    connect(ui.actionConnectDb, &QAction::triggered, this, &DatabaseView::on_connect_db);
    connect(ui.actionRunSQL, &QAction::triggered, this, &DatabaseView::on_run_sql);
}

void DatabaseView::on_connect_db()
{
    if (DbConnection::database().isOpen()) {
        m_error_edit->setPlainText(tr("Connect to databse successed!"));
        m_error_edit->setVisible(true);
        m_table_view->setVisible(false);
        //CONTEXT.dbContext.load(db);
    }
    else {
        m_error_edit->setPlainText(tr("Connect to databse failed!"));
        m_error_edit->setVisible(true);
        m_table_view->setVisible(false);
    }
}

void DatabaseView::on_run_sql()
{
    QString sql_text = m_text_edit->textCursor().selectedText().trimmed().toUpper();
    if (sql_text.length() <= 0)
    {
        sql_text = m_text_edit->toPlainText();
    }
    if (sql_text.length() <= 0)
    {
        QMessageBox::information(this, tr("Error Message"), tr("No SQL stament!"));
        return;
    }

    if (sql_text.indexOf("CREATE ") > 0 ||
        sql_text.indexOf("INSERT INTO ") > 0)
    {
        QMessageBox::information(this, tr("Error Message"), tr("Only run select stament!"));
        return;
    }

    //执行sql
    if (!DbConnection::database().isOpen())
    {
        on_connect_db();
    }

    if (!DbConnection::database().isOpen())
    {
        return;
    }

    //
    m_table_view->setUpdatesEnabled(false);
    CustomSqlModel *model = new CustomSqlModel(this);
    model->setQuery(sql_text, DbConnection::database());
    QSqlError error = model->lastError();
    if (error.type() != QSqlError::NoError)
    {
        m_error_edit->setPlainText(error.text());
        m_error_edit->setVisible(true);
        m_table_view->setVisible(false);
    }
    else {
        m_error_edit->setVisible(false);
        m_table_view->setModel(model);
        //ui.tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(255,228,225);color: black;}");
        m_table_view->setStyleSheet("QTableView{background-color: rgb(250, 250, 250);"
            "alternate-background-color: rgb(234, 234, 234);}");//设置表格颜色
        m_table_view->show();
        m_table_view->setUpdatesEnabled(true);
    }
}