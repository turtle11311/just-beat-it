#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

signals:
    void login();
    void room();

private slots:
    void setAccount(QString account);
    void on_logoutLink_linkActivated(const QString &link);
    void on_mainButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
