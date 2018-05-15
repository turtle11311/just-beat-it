#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    connect(ui->exitButton,SIGNAL(clicked()),parent,SLOT(formClose()));
}

About::~About()
{
    delete ui;
}
