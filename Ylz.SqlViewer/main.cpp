#include "MainView.h"
#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{

    //Qt�������
    QApplication app(argc, argv);

    //���Է���
    QTranslator translator;
    bool ret = translator.load(QCoreApplication::applicationDirPath() + "/ylz.sqlviewer_zh.qm");
    app.installTranslator(&translator);

    //���������
    MainViewer win;
    win.show();

    //���г���
    return app.exec();
}