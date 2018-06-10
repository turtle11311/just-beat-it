#ifndef MEMBER_H
#define MEMBER_H

#include <QWidget>

namespace Ui {
class Member;
}

class Member : public QWidget
{
    Q_OBJECT

public:
    explicit Member(QWidget *parent = 0);
    ~Member();

signals:
    void loginSuccess();

private slots:
    void on_enterButton_clicked();
    void on_registerLink_linkActivated(const QString);

private:
    Ui::Member *ui;
};

#endif // MEMBER_H
