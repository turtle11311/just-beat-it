#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectmusic.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(new SelectMusic(this));
    setWindowTitle("Just Beat it");
}

MainWindow::~MainWindow()
{
    delete ui;
}
