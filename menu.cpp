#include "menu.h"
#include "properties.h"
#include "ui_menu.h"
#include "mysql.h"
#include <QMessageBox>

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
   try
    {
        MySQL db;
        db.Query("update member set login=1 where account=?" , QVector<QVariant>{ properties.account });
        ui->account->setText(properties.account);
        ui->account->setVisible(true);
        ui->logoutLink->setVisible(true);
        ui->mainButton->setText("遊戲大廳");
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}

void Menu::logout()
{
    try
    {
        if(!properties.account.isEmpty())
        {
            MySQL db;
            db.Query("update member set login=0 where account=?" , QVector<QVariant>{ properties.account });
            ui->account->setText("");
            ui->account->setVisible(false);
            ui->logoutLink->setVisible(false);
            ui->mainButton->setText("登入");
            properties.account = "";
        }
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}

Menu::~Menu()
{
    logout();
    delete ui;
}


void Menu::on_logoutLink_linkActivated(const QString)
{
    logout();
}

void Menu::on_mainButton_clicked()
{
    if(!properties.account.isEmpty())
    {
        emit room();
    }
    else
    {
        emit login();
    }
}
