#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectmusic.h"
#include "properties.h"
#include "menu.h"
#include "member.h"
#include "room.h"
#include "about.h"
#include "game.h"
#include "scoreboard.h"
#include <QDebug>

extern Properties properties;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(),height());
    setWindowTitle("Just Beat it");
    ui->stackedWidget->addWidget(new Menu(this));
    connect(this,SIGNAL(updateAccount()),ui->stackedWidget->currentWidget(),SLOT(loginSuccess()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{
    ui->stackedWidget->addWidget(new Member(this));
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::room()
{
    ui->stackedWidget->addWidget(new Room(this));
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::about()
{
    ui->stackedWidget->addWidget(new About(this));
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::loginSuccess()
{
    formClose();
    emit updateAccount();
}

void MainWindow::selectMusic()
{
    ui->stackedWidget->addWidget(new SelectMusic(this));
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::game()
{
    ui->stackedWidget->addWidget(new Game(this));
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::scoreboard()
{
    formClose();
    ui->stackedWidget->addWidget(new ScoreBoard(this));
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::backRoom()
{
    formClose();
    emit back();
}

void MainWindow::formClose()
{
    QWidget* widget = ui->stackedWidget->currentWidget();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
    ui->stackedWidget->removeWidget(widget);
    delete widget;
}
