#include "YlzSqlViewer.h"
#include <QAction>
#include <QNetworkAccessManager>
#include <QString>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QMessageBox>
#include <QTextCodec>
#include <QDockWidget>

#include "GlobalContext.h"
#include "highlighter.h"
#include "SettingsView.h"
#include "DatabaseView.h"


YlzSqlViewer::YlzSqlViewer(QWidget *parent)
    : QMainWindow(parent), position(0)
{
    QIcon icon(":/YlzSqlViewer/Resources/app.ico");
    this->setWindowIcon(icon);
    ui.setupUi(this);   
    setWindowState(Qt::WindowMaximized);

    connect(ui.actionStart, &QAction::triggered, this, &YlzSqlViewer::onStart);
    connect(ui.actionStop, &QAction::triggered, this, &YlzSqlViewer::onStop);
    connect(ui.actionClear, &QAction::triggered, this, &YlzSqlViewer::onClear);
    connect(ui.actionSettings, &QAction::triggered, this, &YlzSqlViewer::onSettings);
    connect(ui.actionSave, &QAction::triggered, this, &YlzSqlViewer::onSave);
    connect(ui.actionLogDownload, &QAction::triggered, this, &YlzSqlViewer::onLogDownload);
    connect(ui.actionDatabase, &QAction::triggered, this, &YlzSqlViewer::onDatabase);

    ui.actionStart->setEnabled(true);
    ui.actionStop->setEnabled(false);    
    
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &YlzSqlViewer::onUpdate);;   //GET结束读取信息

    timer = new QTimer(this);    
    connect(timer, &QTimer::timeout, this, &YlzSqlViewer::onTimer);     

    Highlighter *highlighter = new Highlighter(ui.textEdit->document());
    ui.textEdit->setReadOnly(true);   


    status_bar = this->statusBar();
    status_bar->setGeometry(this->x(), this->height() - 30, this->width(), 30);    
}

void YlzSqlViewer::onStart()
{    
    Config & config = CONTEXT.config;
    QString server = config.get("server");
    if (server.isEmpty())
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Setting Server First!"));
        return;
    }
    ui.actionStart->setEnabled(false);
    ui.actionStop->setEnabled(true);
    status_bar->showMessage(tr("start monitor..."));
    timer->start(500);
}

void YlzSqlViewer::onStop()
{
    status_bar->showMessage(tr("stop monitor"), 5000);
    ui.actionStart->setEnabled(true);
    ui.actionStop->setEnabled(false);
    position = 0;
    timer->stop();
}

void YlzSqlViewer::onUpdate(QNetworkReply *reply)
{
    try
    {
        if (this == nullptr)
        {
            return;
        }

        if (!reply->error() == QNetworkReply::NoError)
        {
            return;
        }

        long long new_position = 0;
        new_position = QString(reply->rawHeader("x-last-position")).toInt();

        QString charset = reply->header(QNetworkRequest::ContentTypeHeader).toString();

        if (position < new_position)
        {
            position = new_position;

            QByteArray logs = reply->readAll();            

            if (logs.size() > 0)
            {
                //界面更新
                if (charset.toLower().indexOf("utf-8") > 0)
                {
                    ui.textEdit->appendPlainText(QString::fromUtf8(logs));
                }
                else
                {
                    ui.textEdit->appendPlainText(QString::fromLocal8Bit(logs));
                }
                
                QTextCursor cursor = ui.textEdit->textCursor();
                //将光标移动到文本结尾，便于删除字符测试，实际上并不需要该步骤            
                cursor.movePosition(QTextCursor::End);
                ui.textEdit->setTextCursor(cursor);
                status_bar->showMessage(tr("log update"));
            }
        }
    }    
    catch(std::exception& e)
    {
        qDebug(e.what());
    }
    reply->deleteLater();
    timer->start(500);
    
}

void YlzSqlViewer::onTimer()
{    

    timer->stop();
    Config & config = CONTEXT.config;
    QString server = config.get("server");
    if (server.isEmpty())
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Setting Server First!"));
        return;
    }
    QUrl url(server); //读取url

    QUrlQuery postData;
    if (position > 0)
    {
        postData.addQueryItem("position", QString::number(position, 10));
    }
    QString remoteIp = config.get("remoteIp");
    if (!remoteIp.isEmpty())
    {
        postData.addQueryItem("remoteAddress", remoteIp);
    }
    url.setQuery(postData);
    QNetworkRequest request(url);
    manager->get(request);
    //timer->start();
}

void YlzSqlViewer::onClear()
{
    ui.textEdit->clear();
    ui.textEdit->setPlainText("");
}

void YlzSqlViewer::onSettings()
{   
    //打开配置文件  
    
    SettingsView * settingView = new SettingsView(this);
    settingView->setFeatures(QDockWidget::AllDockWidgetFeatures);    
    addDockWidget(Qt::RightDockWidgetArea, settingView);
    
}

void YlzSqlViewer::onSave()
{
    if (ui.textEdit->toPlainText().size() <= 0)
    {
        return;
    }
    QString tmp = QCoreApplication::applicationDirPath() + "/tmp.txt";
    QFile file(tmp);//文件命名
    if (!file.open(QFile::WriteOnly | QFile::Text))     //检测文件是否打开
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Select a Text File!"));
        return;
    }
    QTextStream out(&file);                 //分行写入文件
    out << ui.textEdit->toPlainText();  

    //提示保存成功
    QDesktopServices::openUrl(QUrl::fromLocalFile(tmp));
}

//日志下载
void YlzSqlViewer::onLogDownload()
{
    Config & config = CONTEXT.config;
    QString fullLogUrl = config.get("fullLogUrl");
    QDesktopServices::openUrl(fullLogUrl);
}

//数据库查看界面
void YlzSqlViewer::onDatabase()
{
    DatabaseView * databaseView = new DatabaseView(this);
    databaseView->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, databaseView);
}
