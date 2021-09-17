#include "MainView.h"
#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{

    //Qt程序对象
    QApplication app(argc, argv);

    //语言翻译
    QTranslator translator;
    bool ret = translator.load(QCoreApplication::applicationDirPath() + "/ylz.sqlviewer_zh.qm");
    app.installTranslator(&translator);

    //主窗体对象
    MainViewer win;
    win.show();

    //运行程序
    return app.exec();
}