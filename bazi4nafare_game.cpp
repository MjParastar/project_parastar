#include "bazi4nafare_game.h"
#include "ui_bazi4nafare_game.h"

bazi4nafare_game::bazi4nafare_game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bazi4nafare_game)
{
    ui->setupUi(this);
}

bazi4nafare_game::~bazi4nafare_game()
{
    delete ui;
}
