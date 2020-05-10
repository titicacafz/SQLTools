#include "SettingsView.h"
#include <QTextStream>
#include "GlobalContext.h"
#include "Config.h"

SettingsView::SettingsView(QWidget *parent)
    : QDockWidget(parent)
{
    ui.setupUi(this);
    setMinimumWidth(600);
    connect(ui.btn_save, &QAbstractButton::clicked, this, &SettingsView::onSave);
    load();
}

SettingsView::~SettingsView()
{
}

void SettingsView::load()
{
    //
    QString path = QCoreApplication::applicationDirPath() + "/setting.txt";
    QString displayString;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        ui.textSettings->appendPlainText(line);
        while (!line.isNull())
        {
            //         process_line(line);
            line = in.readLine();
            ui.textSettings->appendPlainText(line);
        }
    }
}

void SettingsView::onSave()
{
    QString path = QCoreApplication::applicationDirPath() + "/setting.txt";
    QString displayString;
    QFile file(path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream out(&file);        
        out << ui.textSettings->document()->toPlainText();        
        out.flush();
        file.close();
        Config & config = CONTEXT.config();
        config.load();
    }
    close();
}
