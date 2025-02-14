#include "./src/ui/MainWindow.h"

#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QMap<QString, int>>("QMap<QString, int>");
    MainWindow w;
    w.show();
    return a.exec();
}
