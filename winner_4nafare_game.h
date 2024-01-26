#ifndef WINNER_4NAFARE_GAME_H
#define WINNER_4NAFARE_GAME_H

#include <QMainWindow>

namespace Ui {
class winner_4nafare_game;
}

class winner_4nafare_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit winner_4nafare_game(QWidget *parent = nullptr);
    ~winner_4nafare_game();

private:
    Ui::winner_4nafare_game *ui;
};

#endif // WINNER_4NAFARE_GAME_H
