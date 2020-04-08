#include "YlzSqlViewer.h"
#include <QTranslator>
#include "MiniDump.h"

int main(int argc, char *argv[])
{
    MiniDump::EnableAutoDump(true);
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(QCoreApplication::applicationDirPath()+"/ylz.sqlviewer_zh.qm");
    a.installTranslator(&translator);
    YlzSqlViewer w;
    w.show();
    return a.exec();
}
