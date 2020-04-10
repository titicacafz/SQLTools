#include "DatabaseView.h"
#include <QToolBar>
#include <QTableView>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlError>

#include "highlighter.h"
#include "GlobalContext.h"
#include "CustomSqlModel.h"
#include "SQLEdit.h"
#include "ErrorEdit.h"


DatabaseView::DatabaseView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    initView();
    initEvent();
}

DatabaseView::~DatabaseView()
{
}

void DatabaseView::initView()
{
    QToolBar * toolbar = new QToolBar(this);
    toolbar->addAction(ui.actionConnectDb);
    toolbar->addAction(ui.actionRunSQL);

    textEdit = new SQLEdit(this);
    Highlighter *highlighter = new Highlighter(textEdit->document());
    tableView = new QTableView(this);
    tableView->setVisible(false);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式
    tableView->setAlternatingRowColors(true);
    errorEdit = new ErrorEdit(this);    
    errorEdit->setVisible(false);
    QVBoxLayout *vboxLayout = new QVBoxLayout();
    vboxLayout->addWidget(toolbar);
    vboxLayout->addWidget(textEdit);
    vboxLayout->addWidget(tableView);
    vboxLayout->addWidget(errorEdit);
    setLayout(vboxLayout);    
}

void DatabaseView::initEvent()
{
    connect(ui.actionConnectDb, &QAction::triggered, this, &DatabaseView::onConnectDb);
    connect(ui.actionRunSQL, &QAction::triggered, this, &DatabaseView::onRunSql);    
}

void DatabaseView::onConnectDb()
{
    Config & config = CONTEXT.config;    

    db = QSqlDatabase::addDatabase(config.get("db_driver"));//QOCI
    db.setPort(config.get("db_port").toInt());
    db.setHostName(config.get("db_host"));
    db.setDatabaseName(config.get("db_database"));
    db.setUserName(config.get("db_user"));
    db.setPassword(config.get("db_pass"));


    if (db.open()) {        
        errorEdit->setPlainText(tr("Connect to databse successed!"));
        errorEdit->setVisible(true);
        tableView->setVisible(false);
    }
    else {
        errorEdit->setPlainText(tr("Connect to databse failed!"));
        errorEdit->setVisible(true);
        tableView->setVisible(false);
    }
}

void DatabaseView::onRunSql()
{
    QString sql_text = textEdit->textCursor().selectedText().trimmed().toUpper();
    if (sql_text.length() <= 0)
    {
        sql_text = textEdit->toPlainText();
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
    if (!db.isOpen())
    {
        onConnectDb();
    }

    if (!db.isOpen())
    {
        return;
    }

    //
    tableView->setUpdatesEnabled(false);
    CustomSqlModel *model = new CustomSqlModel(this);
    model->setQuery(sql_text, db);   
    QSqlError error = model->lastError();
    if (error.type() != QSqlError::NoError)
    {
        //QMessageBox::information(this, tr("Error Message"), error.text());  
        errorEdit->setPlainText(error.text());
        errorEdit->setVisible(true);
        tableView->setVisible(false);
    }
    else {
        errorEdit->setVisible(false);
        tableView->setModel(model);
        //ui.tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(255,228,225);color: black;}");
        tableView->setStyleSheet("QTableView{background-color: rgb(250, 250, 250);"
            "alternate-background-color: rgb(234, 234, 234);}");//设置表格颜色
        tableView->show();
        tableView->setUpdatesEnabled(true);
    }
    
}
