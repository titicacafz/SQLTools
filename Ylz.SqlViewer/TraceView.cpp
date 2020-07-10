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
    init_view();
    init_event();
}

TraceView::~TraceView()
{
}

void TraceView::init_view()
{
    m_position = 0;
    //
    m_manager = new QNetworkAccessManager(this);

    m_timer = new QTimer(this);
    

    QToolBar * toolbar = new QToolBar(this);
    toolbar->setMaximumHeight(40);
    toolbar->addAction(ui.actionStart);
    toolbar->addAction(ui.actionStop);
    toolbar->addAction(ui.actionClear);
    toolbar->addAction(ui.actionSave);
    toolbar->addAction(ui.actionFind);

    m_text_edit = new QPlainTextEdit(this);
    Highlighter *highlighter = new Highlighter(m_text_edit->document());
    m_text_edit->setReadOnly(true);

   

    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addWidget(toolbar);
    vboxLayout->addWidget(m_text_edit);
    setLayout(vboxLayout);

    m_find_dialog = new FindDialog(this, m_text_edit);
}

void TraceView::init_event()
{
    //��������عҽ�
    connect(ui.actionStart, &QAction::triggered, this, &TraceView::on_start);
    connect(ui.actionStop, &QAction::triggered, this, &TraceView::on_stop);
    connect(ui.actionClear, &QAction::triggered, this, &TraceView::on_clear);
    connect(ui.actionSave, &QAction::triggered, this, &TraceView::on_save);
    connect(ui.actionFind, &QAction::triggered, this, &TraceView::on_find);

    //������عҽ�
    connect(m_manager, &QNetworkAccessManager::finished, this, &TraceView::on_update);;   //GET������ȡ��Ϣ

    //��ʱ��
    connect(m_timer, &QTimer::timeout, this, &TraceView::on_timer);
}

//��ʼ���
void TraceView::on_start()
{
    Config & config = CONTEXT.config();
    QString server = config.get("server");
    if (server.isEmpty())
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Setting Server First!"));
        return;
    }
    ui.actionStart->setEnabled(false);
    ui.actionStop->setEnabled(true);
    m_timer->start(500);
}

//ֹͣ���
void TraceView::on_stop()
{
    ui.actionStart->setEnabled(true);
    ui.actionStop->setEnabled(false);
    m_position = 0;
    m_timer->stop();
}

//�����ʾ��־
void TraceView::on_clear()
{
    m_text_edit->clear();
    m_text_edit->setPlainText("");
}

//����
void TraceView::on_save()
{
    if (m_text_edit->toPlainText().size() <= 0)
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
    out << m_text_edit->toPlainText();

    //��ʾ����ɹ�
    QDesktopServices::openUrl(QUrl::fromLocalFile(tmp));
}

//http�ӿڽ������
void TraceView::on_update(QNetworkReply *reply)
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

        if (m_position < new_position)
        {
            m_position = new_position;

            QByteArray logs = reply->readAll();

            if (logs.size() > 0)
            {
                //�������
                if (charset.toLower().indexOf("utf-8") > 0)
                {
                    m_text_edit->appendPlainText(QString::fromUtf8(logs));
                }
                else
                {
                    m_text_edit->appendPlainText(QString::fromLocal8Bit(logs));
                }

                QTextCursor cursor = m_text_edit->textCursor();
                //������ƶ����ı���β������ɾ���ַ����ԣ�ʵ���ϲ�����Ҫ�ò���
                cursor.movePosition(QTextCursor::End);
                m_text_edit->setTextCursor(cursor);
            }
        }
    }
    catch (std::exception& e)
    {
        qDebug(e.what());
    }
    reply->deleteLater();
    m_timer->start(500);
}

//��ʱ��������ô��
void TraceView::on_timer()
{
    m_timer->stop();
    Config & config = CONTEXT.config();
    QString server = config.get("server");
    if (server.isEmpty())
    {
        QMessageBox::information(this, tr("Error Message"), tr("Please Setting Server First!"));
        return;
    }
    QUrl url(server); //��ȡurl

    QUrlQuery postData;
    if (m_position > 0)
    {
        postData.addQueryItem("position", QString::number(m_position, 10));
    }

    QString remoteIp = config.get("remoteIp");
    if (!remoteIp.isEmpty())
    {
        postData.addQueryItem("remoteAddress", remoteIp);
    }
    url.setQuery(postData);
    QNetworkRequest request(url);
    m_manager->get(request);
}

void TraceView::on_find()
{
    m_find_dialog->onShow();
}
