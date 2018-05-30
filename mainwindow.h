#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

signals:
    void updateAccount();
    void back();

private slots:
    void login();
    void room();
    void about();
    void loginSuccess();
    void formClose();
    void selectMusic();   
    void game();
    void scoreboard();
    void backRoom();
};

#endif // MAINWINDOW_H
