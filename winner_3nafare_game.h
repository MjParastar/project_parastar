#ifndef WINNER_3NAFARE_GAME_H
#define WINNER_3NAFARE_GAME_H

#include <QMainWindow>

namespace Ui {
class winner_3nafare_game;
}

class winner_3nafare_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit winner_3nafare_game(QWidget *parent = nullptr);
    ~winner_3nafare_game();

private:
    Ui::winner_3nafare_game *ui;
};

#endif // WINNER_3NAFARE_GAME_H
