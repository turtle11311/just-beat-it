#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "member.h"
#include "about.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(),height());
    setWindowTitle("Just Beat it");
    ui->stackedWidget->addWidget(new Menu(this));    
    connect(this,SIGNAL(setAccount(QString)),ui->stackedWidget->currentWidget(),SLOT(setAccount(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{
    ui->stackedWidget->addWidget(new Member(this));
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::room()
{
    //ui->stackedWidget->addWidget(new Room(this));
    //ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::about()
{
    ui->stackedWidget->addWidget(new About(this));
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::loginSuccess(QString account)
{
    formClose();
    emit setAccount(account);
}

void MainWindow::formClose()
{
    QWidget* widget = ui->stackedWidget->currentWidget();
    ui->stackedWidget->removeWidget(widget);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}
