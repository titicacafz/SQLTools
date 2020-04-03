#include "YlzSqlViewer.h"
#include <QDesktopServices>
#include <QDockWidget>
#include <QMdiSubWindow>

#include "GlobalContext.h"
#include "SettingsView.h"
#include "DatabaseView.h"
#include "TraceView.h"


YlzSqlViewer::YlzSqlViewer(QWidget *parent)
    : QMainWindow(parent)
{
    QIcon icon(":/YlzSqlViewer/Resources/app.ico");
    this->setWindowIcon(icon);
    ui.setupUi(this);   
    setWindowState(Qt::WindowMaximized);

    ui.mdiArea->setViewMode(QMdiArea::TabbedView);
    ui.mdiArea->setTabsClosable(true);  //页面可以关闭

    connect(ui.actionMonitor, &QAction::triggered, this, &YlzSqlViewer::onMonitor);
    connect(ui.actionSettings, &QAction::triggered, this, &YlzSqlViewer::onSettings);
    connect(ui.actionLogDownload, &QAction::triggered, this, &YlzSqlViewer::onLogDownload);
    connect(ui.actionDatabase, &QAction::triggered, this, &YlzSqlViewer::onDatabase);    

    status_bar = this->statusBar();
    status_bar->setGeometry(this->x(), this->height() - 30, this->width(), 30);
}

void YlzSqlViewer::onSettings()
{
    //打开配置文件  
    SettingsView * settingView = new SettingsView(this);
    settingView->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, settingView);
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
    QMdiSubWindow *subWin = ui.mdiArea->addSubWindow(databaseView);
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    subWin->setWindowIcon(QIcon());
    databaseView->show();
    status_bar->showMessage(tr("Database View"));
}

//打开监控
void YlzSqlViewer::onMonitor()
{
    TraceView *traceView = new TraceView(this);
    QMdiSubWindow *subWin = ui.mdiArea->addSubWindow(traceView);
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    subWin->setWindowIcon(QIcon());
    traceView->show();
    status_bar->showMessage(tr("Monitor View"));
}
