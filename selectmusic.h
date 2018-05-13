#ifndef SELECTMUSIC_H
#define SELECTMUSIC_H

#include <QWidget>

namespace Ui {
class SelectMusic;
}

class SelectMusic : public QWidget
{
    Q_OBJECT

public:
    explicit SelectMusic(QWidget *parent = 0);
    ~SelectMusic();

private:
    Ui::SelectMusic *ui;
};

#endif // SELECTMUSIC_H
