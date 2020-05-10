#include "MainView.h"
#include <QDesktopServices>
#include <QDockWidget>
#include <QMdiSubWindow>

#include "GlobalContext.h"
#include "SettingsView.h"
#include "DatabaseView.h"
#include "TraceView.h"
#include "DDLView.h"


MainViewer::MainViewer(QWidget *parent)
    : QMainWindow(parent),
    m_database_view(nullptr),
    m_trace_view(nullptr),
    m_ddl_view(nullptr)
{
    QIcon icon(":/YlzSqlViewer/Resources/app.ico");
    this->setWindowIcon(icon);
    ui.setupUi(this);   
    setWindowState(Qt::WindowMaximized);

    ui.mdiArea->setViewMode(QMdiArea::TabbedView);
    ui.mdiArea->setTabsClosable(true);  //ҳ����Թر�

    connect(ui.actionMonitor, &QAction::triggered, this, &MainViewer::on_monitor);
    connect(ui.actionSettings, &QAction::triggered, this, &MainViewer::on_settings);
    connect(ui.actionLogDownload, &QAction::triggered, this, &MainViewer::on_log_download);
    connect(ui.actionDatabase, &QAction::triggered, this, &MainViewer::on_database);  
    connect(ui.actionDDL, &QAction::triggered, this, &MainViewer::on_ddl);

    m_status_bar = this->statusBar();
    m_status_bar->setGeometry(this->x(), this->height() - 30, this->width(), 30);          

}

void MainViewer::on_settings()
{
    SettingsView * settingView = new SettingsView(this);
    settingView->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, settingView);
}

//��־����
void MainViewer::on_log_download()
{
    Config & config = CONTEXT.config();
    QString fullLogUrl = config.get("fullLogUrl");
    QDesktopServices::openUrl(fullLogUrl);
}

//���ݿ�鿴����
void MainViewer::on_database()
{    
    if (m_database_view == nullptr)
    {
        m_database_view = new DatabaseView(this);
        QMdiSubWindow *subWin = ui.mdiArea->addSubWindow(m_database_view);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        subWin->setWindowIcon(QIcon());
    }
    m_database_view->show();
    m_status_bar->showMessage(tr("Database View"));
}

//�򿪼��
void MainViewer::on_monitor()
{
    TraceView *traceView = new TraceView(this);
    QMdiSubWindow *subWin = ui.mdiArea->addSubWindow(traceView);
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    subWin->setWindowIcon(QIcon());
    traceView->show();
    m_status_bar->showMessage(tr("Monitor View"));
}

void MainViewer::on_ddl()
{
    if (m_ddl_view == nullptr) {
        m_ddl_view = new DdlView(this);
        QMdiSubWindow* subWin = ui.mdiArea->addSubWindow(m_ddl_view);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        subWin->setWindowIcon(QIcon());
    }
            
    m_ddl_view->show();
    m_status_bar->showMessage(tr("DDL View"));    
}

