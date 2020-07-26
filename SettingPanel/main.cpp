#include "settingpanel.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    bool b = translator.load("settingpanel.qm",":/");
    qDebug() << b ;
    a.installTranslator(&translator);

    SettingPanel w;
    w.show();

    return a.exec();
}
