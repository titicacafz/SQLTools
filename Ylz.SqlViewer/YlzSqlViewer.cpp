#include "YlzSqlViewer.h"
#include <QDesktopServices>
#include <QDockWidget>
#include <QMdiSubWindow>

#include "GlobalContext.h"
#include "SettingsView.h"
#include "DatabaseView.h"
#include "TraceView.h"
#include "DDLView.h"


YlzSqlViewer::YlzSqlViewer(QWidget *parent)
    : QMainWindow(parent),
    databaseView(nullptr),
    traceView(nullptr),
    ddlView(nullptr)
{
    QIcon icon(":/YlzSqlViewer/Resources/app.ico");
    this->setWindowIcon(icon);
    ui.setupUi(this);   
    setWindowState(Qt::WindowMaximized);

    ui.mdiArea->setViewMode(QMdiArea::TabbedView);
    ui.mdiArea->setTabsClosable(true);  //ҳ����Թر�

    connect(ui.actionMonitor, &QAction::triggered, this, &YlzSqlViewer::onMonitor);
    connect(ui.actionSettings, &QAction::triggered, this, &YlzSqlViewer::onSettings);
    connect(ui.actionLogDownload, &QAction::triggered, this, &YlzSqlViewer::onLogDownload);
    connect(ui.actionDatabase, &QAction::triggered, this, &YlzSqlViewer::onDatabase);  
    connect(ui.actionDDL, &QAction::triggered, this, &YlzSqlViewer::onDDL);

    status_bar = this->statusBar();
    status_bar->setGeometry(this->x(), this->height() - 30, this->width(), 30);          

}

void YlzSqlViewer::onSettings()
{
    SettingsView * settingView = new SettingsView(this);
    settingView->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, settingView);
}

//��־����
void YlzSqlViewer::onLogDownload()
{
    Config & config = CONTEXT.config;
    QString fullLogUrl = config.get("fullLogUrl");
    QDesktopServices::openUrl(fullLogUrl);
}

//���ݿ�鿴����
void YlzSqlViewer::onDatabase()
{    
    if (databaseView == nullptr)
    {
        databaseView = new DatabaseView(this);
        QMdiSubWindow *subWin = ui.mdiArea->addSubWindow(databaseView);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        subWin->setWindowIcon(QIcon());
    }
    databaseView->show();
    status_bar->showMessage(tr("Database View"));
}

//�򿪼��
void YlzSqlViewer::onMonitor()
{
    TraceView *traceView = new TraceView(this);
    QMdiSubWindow *subWin = ui.mdiArea->addSubWindow(traceView);
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    subWin->setWindowIcon(QIcon());
    traceView->show();
    status_bar->showMessage(tr("Monitor View"));
}

void YlzSqlViewer::onDDL()
{
    if (ddlView == nullptr) {
        ddlView = new DDLView(this);
        QMdiSubWindow* subWin = ui.mdiArea->addSubWindow(ddlView);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        subWin->setWindowIcon(QIcon());
    }
            
    ddlView->show();
    status_bar->showMessage(tr("DDL View"));    
}

