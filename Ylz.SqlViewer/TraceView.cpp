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

    m_text_edit = new QPlainTextEdit(this);
    Highlighter *highlighter = new Highlighter(m_text_edit->document());
    m_text_edit->setReadOnly(true);

    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addWidget(toolbar);
    vboxLayout->addWidget(m_text_edit);
    setLayout(vboxLayout);
}

void TraceView::init_event()
{
    //工具栏相关挂接
    connect(ui.actionStart, &QAction::triggered, this, &TraceView::on_start);
    connect(ui.actionStop, &QAction::triggered, this, &TraceView::on_stop);
    connect(ui.actionClear, &QAction::triggered, this, &TraceView::on_clear);
    connect(ui.actionSave, &QAction::triggered, this, &TraceView::on_save);

    //网络相关挂接
    connect(m_manager, &QNetworkAccessManager::finished, this, &TraceView::on_update);;   //GET结束读取信息

    //定时器
    connect(m_timer, &QTimer::timeout, this, &TraceView::on_timer);
}

//开始监控
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

//停止监控
void TraceView::on_stop()
{    
    ui.actionStart->setEnabled(true);
    ui.actionStop->setEnabled(false);
    m_position = 0;
    m_timer->stop();
}

//清空显示日志
void TraceView::on_clear()
{
    m_text_edit->clear();
    m_text_edit->setPlainText("");
}

//保存
void TraceView::on_save()
{
    if (m_text_edit->toPlainText().size() <= 0)
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
    out << m_text_edit->toPlainText();

    //提示保存成功
    QDesktopServices::openUrl(QUrl::fromLocalFile(tmp));
}

//http接口交互完成
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
                //界面更新
                if (charset.toLower().indexOf("utf-8") > 0)
                {
                    m_text_edit->appendPlainText(QString::fromUtf8(logs));
                }
                else
                {
                    m_text_edit->appendPlainText(QString::fromLocal8Bit(logs));
                }

                QTextCursor cursor = m_text_edit->textCursor();
                //将光标移动到文本结尾，便于删除字符测试，实际上并不需要该步骤            
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

//定时器，先这么用
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
    QUrl url(server); //读取url

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
