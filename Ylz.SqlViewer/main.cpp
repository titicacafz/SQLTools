#include "MainView.h"
#include <QApplication>
#include <QTranslator>
#include "MiniDump.h"

int main(int argc, char *argv[])
{
    //��������minidump
    MiniDump::EnableAutoDump(true);
    
    //Qt�������
    QApplication a(argc, argv);

    //���Է���
    QTranslator translator;
    translator.load(QCoreApplication::applicationDirPath()+"/ylz.sqlviewer_zh.qm");
    a.installTranslator(&translator);
    
    //���������
    MainViewer w;
    w.show();
    
    //���г���
    return a.exec();
}
