#include "MainView.h"
#include <QApplication>
#include <QTranslator>
#include "MiniDump.h"

int main(int argc, char *argv[])
{
    //��������minidump
    MiniDump::EnableAutoDump(true);
    
    //Qt�������
    QApplication app(argc, argv);

    //���Է���
    QTranslator translator;
    translator.load(QCoreApplication::applicationDirPath()+"/ylz.sqlviewer_zh.qm");
    app.installTranslator(&translator);
    
    //���������
    MainViewer win;
    win.show();
    
    //���г���
    return app.exec();
}
