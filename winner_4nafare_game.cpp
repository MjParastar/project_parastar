#include "winner_4nafare_game.h"
#include "ui_winner_4nafare_game.h"

#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

winner_4nafare_game::winner_4nafare_game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::winner_4nafare_game)
{
    ui->setupUi(this);

    //relate coin database
    QSqlDatabase database ;
    database = QSqlDatabase::addDatabase("QSQLITE") ;
    database.setDatabaseName("C:\\Personal\\AdvancedMabani\\ProjectQt\\Database\\coin.db") ;
    database.open() ;

    if (database.open())
    {
        QSqlQuery query("SELECT coin FROM WinnerPlayer LIMIT 2");
        QVector<int> coins;
        while (query.next())
        {
            coins.push_back(query.value(0).toInt());
        }

        std::sort(coins.begin(), coins.end(), std::greater<int>());

        ui->oneperson_label->setText(QString::number(coins[0]));
        ui->oneperson_label->setAlignment(Qt::AlignCenter);

        ui->twoperson_label->setText(QString::number(coins[1]));
        ui->twoperson_label->setAlignment(Qt::AlignCenter);

        ui->threeperson_label->setText(QString::number(coins[2]));
        ui->threeperson_label->setAlignment(Qt::AlignCenter);

        ui->fourperson_label->setText(QString::number(coins[3]));
        ui->fourperson_label->setAlignment(Qt::AlignCenter);
    }

    setMaximumSize(757,550) ;
    setMinimumSize(757,550) ;
}

winner_4nafare_game::~winner_4nafare_game()
{
    delete ui;
}
