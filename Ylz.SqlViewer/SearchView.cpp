#include "SearchView.h"
#include <QPlainTextEdit>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QPushButton>
#include <QHostInfo>
#include "Config.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QFile>
#include "GlobalContext.h"
#include "HighLighter.h"

LogSearchView::LogSearchView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    Highlighter *highlighter = new Highlighter(ui.log_edit->document());
    ui.log_edit->setReadOnly(true);

    QTime endTime = QTime::currentTime();
    QTime beginTime = endTime.addSecs(-10*60);

    ui.end_time->setTime(endTime);
    ui.begin_time->setTime(beginTime);

    //本机ip
    QString host = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(host);

    foreach(QHostAddress address, info.addresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            ui.ip->setText(address.toString());
    }

    m_manager = new QNetworkAccessManager(this);

    connect(ui.btn_log_get, &QPushButton::clicked, this, &LogSearchView::on_log_search);
    connect(m_manager, &QNetworkAccessManager::finished, this, &LogSearchView::on_update);
    connect(ui.begin_time, &QTimeEdit::timeChanged, this, &LogSearchView::on_end_time_changed);
    m_find_dialog = new FindDialog(this, ui.log_edit);
    connect(ui.btn_log_find, &QPushButton::clicked, this, &LogSearchView::on_find);
    connect(ui.btn_saveto, &QPushButton::clicked, this, &LogSearchView::on_save);
}

LogSearchView::~LogSearchView()
{
}

void LogSearchView::on_log_search()
{
    ui.btn_log_get->setEnabled(false);
    Config & config = CONTEXT.config();
    QString server = config.get("logSearchUrl");
    if (server.isEmpty())
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Setting Log Search Url First!"));
        return;
    }
    QUrl url(server); //读取url

    QUrlQuery postData;
    
    QString ip = ui.ip->text();
    QString begin_time = ui.begin_time->text();
    QString end_time = ui.end_time->text();

    
    if (ip.isEmpty() || begin_time.isEmpty() || end_time.isEmpty())
    {
        return;
    }
    postData.addQueryItem("remoteAddress", ip);
    postData.addQueryItem("beginTime", begin_time);
    postData.addQueryItem("endTime", end_time);
    
    url.setQuery(postData);
    QNetworkRequest request(url);
    m_manager->get(request);
}

void LogSearchView::on_update(QNetworkReply *reply)
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

        ui.log_edit->setPlainText("");
        

        QString charset = reply->header(QNetworkRequest::ContentTypeHeader).toString();

        QByteArray logs = reply->readAll();

        if (logs.size() > 0)
        {
            //界面更新
            if (charset.toLower().indexOf("utf-8") > 0)
            {
                ui.log_edit->appendPlainText(QString::fromUtf8(logs));
            }
            else
            {
                ui.log_edit->appendPlainText(QString::fromLocal8Bit(logs));
            }

            QTextCursor cursor = ui.log_edit->textCursor();
            //将光标移动到文本结尾，便于删除字符测试，实际上并不需要该步骤
            cursor.movePosition(QTextCursor::End);
            ui.log_edit->setTextCursor(cursor);
        }
    }
    catch (std::exception& e)
    {
        qDebug(e.what());
    }
    reply->deleteLater();
    ui.btn_log_get->setEnabled(true);
}

void LogSearchView::on_end_time_changed(const QTime &time)
{
    //
    QTime endTime = time.addSecs(5*60);
    ui.end_time->setTime(endTime);
}

void LogSearchView::on_find()
{
    m_find_dialog->onShow();
}

void LogSearchView::on_save()
{
    if (ui.log_edit->toPlainText().size() <= 0)
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
    out << ui.log_edit->toPlainText();

    //提示保存成功
    QDesktopServices::openUrl(QUrl::fromLocalFile(tmp));
}
