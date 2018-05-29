#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Room;
}

class Room : public QWidget
{
    Q_OBJECT

public:
    explicit Room(QWidget *parent = 0);
    ~Room();

private slots:
    void on_roomList_doubleClicked(const QModelIndex &index);
    void on_leader_textChanged(const QString &arg1);
    void timeout();
    void on_createButton_clicked();
    void on_refreshButton_clicked();
    void on_leaveButton_clicked();
    void on_startButton_clicked();

private:
    Ui::Room *ui;
    QTimer timer;
    void refreshRoom();
    void refreshPlayer();
    void leave();
};

#endif // ROOM_H
