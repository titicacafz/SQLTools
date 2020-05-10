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
    databaseView(nullptr),
    traceView(nullptr),
    ddlView(nullptr)
{
    QIcon icon(":/YlzSqlViewer/Resources/app.ico");
    this->setWindowIcon(icon);
    ui.setupUi(this);   
    setWindowState(Qt::WindowMaximized);

    ui.mdiArea->setViewMode(QMdiArea::TabbedView);
    ui.mdiArea->setTabsClosable(true);  //页面可以关闭

    connect(ui.actionMonitor, &QAction::triggered, this, &MainViewer::onMonitor);
    connect(ui.actionSettings, &QAction::triggered, this, &MainViewer::onSettings);
    connect(ui.actionLogDownload, &QAction::triggered, this, &MainViewer::onLogDownload);
    connect(ui.actionDatabase, &QAction::triggered, this, &MainViewer::onDatabase);  
    connect(ui.actionDDL, &QAction::triggered, this, &MainViewer::onDDL);

    status_bar = this->statusBar();
    status_bar->setGeometry(this->x(), this->height() - 30, this->width(), 30);          

}

void MainViewer::onSettings()
{
    SettingsView * settingView = new SettingsView(this);
    settingView->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, settingView);
}

//日志下载
void MainViewer::onLogDownload()
{
    Config & config = CONTEXT.config();
    QString fullLogUrl = config.get("fullLogUrl");
    QDesktopServices::openUrl(fullLogUrl);
}

//数据库查看界面
void MainViewer::onDatabase()
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

//打开监控
void MainViewer::onMonitor()
{
    TraceView *traceView = new TraceView(this);
    QMdiSubWindow *subWin = ui.mdiArea->addSubWindow(traceView);
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    subWin->setWindowIcon(QIcon());
    traceView->show();
    status_bar->showMessage(tr("Monitor View"));
}

void MainViewer::onDDL()
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

