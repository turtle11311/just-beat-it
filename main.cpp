#include "mainwindow.h"
#include "youtubesearch.h"
#include "properties.h"
#include <QApplication>

Properties properties;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    YoutubeSearch yt("surfing", "AIzaSyDt1RCrwqcxYTdr7uK5lICnURqczbYoTto", &w);
    w.show();

    return app.exec();
}
