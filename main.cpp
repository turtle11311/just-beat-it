#include "mainwindow.h"
#include "properties.h"
#include <QApplication>

Properties properties;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
