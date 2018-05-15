#include "member.h"
#include "ui_member.h"
#include <QMessageBox>
#include <QRegExp>
#include "mysql.h"
#include "mainwindow.h"

Member::Member(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Member)
{
    ui->setupUi(this);
    connect(this,SIGNAL(loginSuccess(QString)),parent,SLOT(loginSuccess(QString)));
    connect(ui->exitButton,SIGNAL(clicked()),parent,SLOT(formClose()));
}

Member::~Member()
{
    delete ui;
}

void Member::on_enterButton_clicked()
{
    try
    {
        QRegExp regex("^[a-zA-Z0-9]{5,15}$");
        if(!regex.exactMatch(ui->account->text()) || !regex.exactMatch(ui->password->text()))
        {
            QMessageBox::critical(this,"","帳號密碼須為長度5~15英數組合");
            return;
        }
        MySQL db;
        QVector<QVector<QVariant>> result;
        if(ui->registerLink->isVisible())
        {
            result = db.Query("select count(*) from member where account=? and password=?" , QVector<QVariant>({ ui->account->text() , ui->password->text() }));
            if(result[0][0].toInt() == 1)
            {
                emit loginSuccess(ui->account->text());
            }
            else
            {
                QMessageBox::critical(this,"","帳號不存在或密碼錯誤");
            }
        }
        else
        {
            result = db.Query("select count(*) from member where account=?" , QVector<QVariant>({ ui->account->text() }));
            if(result[0][0].toInt() == 1)
            {
                QMessageBox::critical(this,"","帳號已存在");
            }
            else
            {
                result = db.Query("insert into member( account , password ) values( ? , ? )" , QVector<QVariant>({ ui->account->text() , ui->password->text() }));
                QMessageBox::information(this,"","註冊成功");
                emit ui->exitButton->click();
            }
        }
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}

void Member::on_registerLink_linkActivated(const QString &link)
{
    ui->enterButton->setText("註冊");
    ui->account->setText("");
    ui->password->setText("");
    ui->registerLink->setVisible(false);
}
