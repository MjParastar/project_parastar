#ifndef WINNER_2NAFARE_GAME_H
#define WINNER_2NAFARE_GAME_H

#include <QMainWindow>

namespace Ui {
class winner_2nafare_game;
}

class winner_2nafare_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit winner_2nafare_game(QWidget *parent = nullptr);
    ~winner_2nafare_game();

private:
    Ui::winner_2nafare_game *ui;
};

#endif // WINNER_2NAFARE_GAME_H
