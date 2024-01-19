#ifndef BAZI4NAFARE_GAME_H
#define BAZI4NAFARE_GAME_H

#include <QMainWindow>

namespace Ui {
class bazi4nafare_game;
}

class bazi4nafare_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit bazi4nafare_game(QWidget *parent = nullptr);
    ~bazi4nafare_game();

private:
    Ui::bazi4nafare_game *ui;
};

#endif // BAZI4NAFARE_GAME_H
