#include "member.h"
#include "ui_member.h"
#include <QMessageBox>
#include <QRegExp>
#include "properties.h"
#include "mysql.h"
#include "mainwindow.h"

extern Properties properties;

Member::Member(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Member)
{
    ui->setupUi(this);
    connect(this,SIGNAL(loginSuccess()),parent,SLOT(loginSuccess()));
    connect(ui->exitButton,SIGNAL(clicked()),parent,SLOT(formClose()));
    QFont font;
    font = ui->account->font();
    font.setCapitalization(QFont::AllUppercase);
    ui->account->setFont(font);
    font = ui->password->font();
    font.setCapitalization(QFont::AllUppercase);
    ui->password->setFont(font);
}

Member::~Member()
{
    delete ui;
}

void Member::on_enterButton_clicked()
{
    try
    {
        ui->account->setText(ui->account->text().toUpper());
        ui->password->setText(ui->password->text().toUpper());
        QRegExp regex("^[A-Z0-9]{5,15}$");
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
                properties.account = ui->account->text();
                emit loginSuccess();
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
                db.Query("insert into member( account , password ) values( ? , ? )" , QVector<QVariant>({ ui->account->text() , ui->password->text() }));
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
