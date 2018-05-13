#include "mainwindow.h"
#include "youtubesearch.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    YoutubeSearch yt("surfing", "AIzaSyDt1RCrwqcxYTdr7uK5lICnURqczbYoTto", &w);
    yt.search(10);
    w.show();

    return app.exec();
}
