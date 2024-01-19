#include "bazi3nafare_game.h"
#include "ui_bazi3nafare_game.h"

bazi3nafare_game::bazi3nafare_game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bazi3nafare_game)
{
    ui->setupUi(this);
}

bazi3nafare_game::~bazi3nafare_game()
{
    delete ui;
}
