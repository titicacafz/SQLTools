#include "TraceView.h"
#include <QIcon>
#include <QToolBar>
#include <QVBoxLayout>
#include <QAction>
#include <QPlainTextEdit>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QTimer>
#include <QMessageBox>
#include <QDesktopServices>

#include "highlighter.h"
#include "GlobalContext.h"

TraceView::TraceView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    initView();
    initEvent();
}

TraceView::~TraceView()
{
}

void TraceView::initView()
{

    position = 0;
    //
    manager = new QNetworkAccessManager(this);

    timer = new QTimer(this);

    QToolBar * toolbar = new QToolBar(this);
    toolbar->setMaximumHeight(40);
    toolbar->addAction(ui.actionStart);
    toolbar->addAction(ui.actionStop);
    toolbar->addAction(ui.actionClear);
    toolbar->addAction(ui.actionSave);

    textEdit = new QPlainTextEdit(this);
    Highlighter *highlighter = new Highlighter(textEdit->document());
    textEdit->setReadOnly(true);

    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addWidget(toolbar);
    vboxLayout->addWidget(textEdit);
    setLayout(vboxLayout);
}

void TraceView::initEvent()
{
    //��������عҽ�
    connect(ui.actionStart, &QAction::triggered, this, &TraceView::onStart);
    connect(ui.actionStop, &QAction::triggered, this, &TraceView::onStop);
    connect(ui.actionClear, &QAction::triggered, this, &TraceView::onClear);
    connect(ui.actionSave, &QAction::triggered, this, &TraceView::onSave);

    //������عҽ�
    connect(manager, &QNetworkAccessManager::finished, this, &TraceView::onUpdate);;   //GET������ȡ��Ϣ

    //��ʱ��
    connect(timer, &QTimer::timeout, this, &TraceView::onTimer);
}

//��ʼ���
void TraceView::onStart()
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
    timer->start(500);
}

//ֹͣ���
void TraceView::onStop()
{    
    ui.actionStart->setEnabled(true);
    ui.actionStop->setEnabled(false);
    position = 0;
    timer->stop();
}

//�����ʾ��־
void TraceView::onClear()
{
    textEdit->clear();
    textEdit->setPlainText("");
}

//����
void TraceView::onSave()
{
    if (textEdit->toPlainText().size() <= 0)
    {
        return;
    }
    QString tmp = QCoreApplication::applicationDirPath() + "/tmp.txt";
    QFile file(tmp);//�ļ�����
    if (!file.open(QFile::WriteOnly | QFile::Text))     //����ļ��Ƿ��
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Select a Text File!"));
        return;
    }
    QTextStream out(&file);                 //����д���ļ�
    out << textEdit->toPlainText();

    //��ʾ����ɹ�
    QDesktopServices::openUrl(QUrl::fromLocalFile(tmp));
}

//http�ӿڽ������
void TraceView::onUpdate(QNetworkReply *reply)
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
                //�������
                if (charset.toLower().indexOf("utf-8") > 0)
                {
                    textEdit->appendPlainText(QString::fromUtf8(logs));
                }
                else
                {
                    textEdit->appendPlainText(QString::fromLocal8Bit(logs));
                }

                QTextCursor cursor = textEdit->textCursor();
                //������ƶ����ı���β������ɾ���ַ����ԣ�ʵ���ϲ�����Ҫ�ò���            
                cursor.movePosition(QTextCursor::End);
                textEdit->setTextCursor(cursor);                
            }
        }
    }
    catch (std::exception& e)
    {
        qDebug(e.what());
    }
    reply->deleteLater();
    timer->start(500);
}

//��ʱ��������ô��
void TraceView::onTimer()
{
    timer->stop();
    Config & config = CONTEXT.config;
    QString server = config.get("server");
    if (server.isEmpty())
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Setting Server First!"));
        return;
    }
    QUrl url(server); //��ȡurl

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
}
