#include "YlzSqlViewer.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(QCoreApplication::applicationDirPath()+"/ylz.sqlviewer_zh.qm");
    a.installTranslator(&translator);
    YlzSqlViewer w;
    w.show();
    return a.exec();
}
