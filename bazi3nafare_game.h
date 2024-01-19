#ifndef BAZI3NAFARE_GAME_H
#define BAZI3NAFARE_GAME_H

#include <QMainWindow>

namespace Ui {
class bazi3nafare_game;
}

class bazi3nafare_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit bazi3nafare_game(QWidget *parent = nullptr);
    ~bazi3nafare_game();

private:
    Ui::bazi3nafare_game *ui;
};

#endif // BAZI3NAFARE_GAME_H
