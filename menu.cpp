#include "menu.h"
#include "properties.h"
#include "ui_menu.h"

extern Properties properties;

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(this,SIGNAL(login()),parent,SLOT(login()));
    connect(this,SIGNAL(room()),parent,SLOT(room()));
    connect(ui->aboutButton,SIGNAL(clicked()),parent,SLOT(about()));
    connect(ui->exitButton,SIGNAL(clicked()),parent,SLOT(close()));
    ui->account->setVisible(false);
    ui->logoutLink->setVisible(false);
}

void Menu::loginSuccess()
{
    ui->account->setText(properties.account);
    ui->account->setVisible(true);
    ui->logoutLink->setVisible(true);
    ui->mainButton->setText("遊戲大廳");
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_logoutLink_linkActivated(const QString)
{
    ui->account->setText("");
    ui->account->setVisible(false);
    ui->logoutLink->setVisible(false);
    ui->mainButton->setText("登入");
    properties.account = "";
}

void Menu::on_mainButton_clicked()
{
    if(ui->logoutLink->isVisible())
    {
        emit room();
    }
    else
    {
        emit login();
    }
}
