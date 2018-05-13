#include "selectmusic.h"
#include "mainwindow.h"
#include "ui_selectmusic.h"

SelectMusic::SelectMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectMusic)
{
    ui->setupUi(this);
}

SelectMusic::~SelectMusic()
{
    delete ui;
}
