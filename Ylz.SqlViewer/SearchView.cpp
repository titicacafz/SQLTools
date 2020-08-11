#include "SearchView.h"
#include <QPlainTextEdit>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QPushButton>
#include "Config.h"
#include <QMessageBox>
#include "GlobalContext.h"
#include "HighLighter.h"

LogSearchView::LogSearchView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    Highlighter *highlighter = new Highlighter(ui.log_edit->document());
    ui.log_edit->setReadOnly(true);

    m_manager = new QNetworkAccessManager(this);

    connect(ui.btn_find, &QPushButton::clicked, this, &LogSearchView::on_log_search);
    connect(m_manager, &QNetworkAccessManager::finished, this, &LogSearchView::on_update);;
}

LogSearchView::~LogSearchView()
{
}

void LogSearchView::on_log_search()
{
    ui.btn_find->setEnabled(false);
    Config & config = CONTEXT.config();
    QString server = config.get("logSearchUrl");
    if (server.isEmpty())
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Setting Log Search Url First!"));
        return;
    }
    QUrl url(server); //��ȡurl

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
            //�������
            if (charset.toLower().indexOf("utf-8") > 0)
            {
                ui.log_edit->appendPlainText(QString::fromUtf8(logs));
            }
            else
            {
                ui.log_edit->appendPlainText(QString::fromLocal8Bit(logs));
            }

            QTextCursor cursor = ui.log_edit->textCursor();
            //������ƶ����ı���β������ɾ���ַ����ԣ�ʵ���ϲ�����Ҫ�ò���
            cursor.movePosition(QTextCursor::End);
            ui.log_edit->setTextCursor(cursor);
        }
    }
    catch (std::exception& e)
    {
        qDebug(e.what());
    }
    reply->deleteLater();
    ui.btn_find->setEnabled(true);
}
