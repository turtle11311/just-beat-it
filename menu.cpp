#include "menu.h"
#include "ui_menu.h"

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

void Menu::setAccount(QString account)
{
    ui->account->setText(account);
    ui->account->setVisible(true);
    ui->logoutLink->setVisible(true);
    ui->mainButton->setText("開始遊戲");
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_logoutLink_linkActivated(const QString &link)
{
    ui->account->setVisible(false);
    ui->logoutLink->setVisible(false);
    ui->mainButton->setText("登入");
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
