#include "bazi2nafare_game.h"
#include "ui_bazi2nafare_game.h"

#include "winner_2nafare_game.h"

#include "iostream"

#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

#include "QPixmap"
#include "QLabel"
#include "QTimer"
#include "QTime"
#include "QMessageBox"
#include "QDebug"

#include <QtMultimedia>
#include <QDebug>
#include "QSqlError"

int coin = 10 ;
int worker_num = 1 ;
int hen{0} , sheep{0} , cow{0} , wheat{0} , barley{0} , free_worker{1} , land{1} , buy_land{0};

int free_hen{0} ;
int free_sheep{0} ;
int free_cow{0} ;

int Egg{0} ;
int milk_cow{0} ;
int milk_sheep{0} ;
int wheat_product{0} ;
int barley_product{0} ;

int a = 1 ;


bazi2nafare_game::bazi2nafare_game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bazi2nafare_game)
{
    ui->setupUi(this);

    //relate to database and display on label
    QSqlDatabase database ;
    database = QSqlDatabase::addDatabase("QSQLITE") ;
    database.setDatabaseName("C:\\Personal\\AdvancedMabani\\ProjectQt\\Database\\Player.db") ;

    if (database.open())
    {
        QSqlQuery query;
        if(a == 1)
        {
            query.prepare("SELECT Username FROM Player LIMIT 1");
        }
        else
        {
            query.prepare("SELECT Username FROM Player LIMIT 1 OFFSET 1");
        }

        if (query.exec() && query.next())
        {
            QString name = query.value(0).toString();
            ui->lab_display_name->setText(name);
        }
        else
        {
            qDebug() << query.lastError();
        }
    }
    else
    {
        qDebug() << database.lastError();
    }


    //relate coin
    QSqlDatabase database_2 ;
    database = QSqlDatabase::addDatabase("QSQLITE") ;
    database.setDatabaseName("C:\\Personal\\AdvancedMabani\\ProjectQt\\Database\\coin.db") ;
    database.open() ;

    if(a == 2)
    {
        ui->label_6->setText("   کاربر دوم") ;

    }

    ui->lab_display_name->setAlignment(Qt::AlignCenter);

    update_coin() ;

    update_worker_num() ;

    setMaximumSize(966,529) ;
    setMinimumSize(966,529) ;


    ui->comboBox_kill->addItem("(3$)مرغ") ;
    ui->comboBox_kill->addItem("(4$)گوسفند") ;
    ui->comboBox_kill->addItem("(6$)گاو") ;

    ui->comboBox_kill->setItemData(0, QIcon(":/hen.png"), Qt::DecorationRole);
    ui->comboBox_kill->setItemData(1, QIcon(":/black-sheep.png"), Qt::DecorationRole);
    ui->comboBox_kill->setItemData(2, QIcon(":/cow.png"), Qt::DecorationRole);

    ui->comboBox_store->addItem("گندم($2)") ;
    ui->comboBox_store->addItem("جو($2)") ;
    ui->comboBox_store->addItem("(3$)مرغ") ;
    ui->comboBox_store->addItem("(5$)گوسفند") ;
    ui->comboBox_store->addItem("(7$)گاو") ;
    ui->comboBox_store->addItem("زمین($3)") ;
    ui->comboBox_store->addItem("(5$)کارگر") ;

    ui->comboBox_store->setItemData(0, QIcon(":/wheat-grains.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(1, QIcon(":/barley.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(2, QIcon(":/hen.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(3, QIcon(":/black-sheep.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(4, QIcon(":/cow.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(5, QIcon(":/land.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(6, QIcon(":/worker.png"), Qt::DecorationRole);


    //timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    timer->start(1000);

    countdownTime.setHMS(0, 3, 0); // 3 دقیقه
    ui->label_timer->setText(countdownTime.toString("          mm:ss"));

      ui->combobox_11->addItem("") ;
      ui->combobox_11->addItem("کاشت گندم") ;
      ui->combobox_11->addItem("کاشت جو") ;
      ui->combobox_11->addItem("مرغ") ;
      ui->combobox_11->addItem("گوسفند") ;
      ui->combobox_11->addItem("گاو") ;
      ui->combobox_11->addItem("برداشت") ;

      ui->combobox_12->addItem("") ;
      ui->combobox_12->addItem("خرید زمین") ;
      ui->combobox_12->addItem("کاشت گندم") ;
      ui->combobox_12->addItem("کاشت جو") ;
      ui->combobox_12->addItem("مرغ") ;
      ui->combobox_12->addItem("گوسفند") ;
      ui->combobox_12->addItem("گاو") ;
      ui->combobox_12->addItem("برداشت") ;

      ui->combobox_13->addItem("") ;
      ui->combobox_13->addItem("خرید زمین") ;
      ui->combobox_13->addItem("کاشت گندم") ;
      ui->combobox_13->addItem("کاشت جو") ;
      ui->combobox_13->addItem("مرغ") ;
      ui->combobox_13->addItem("گوسفند") ;
      ui->combobox_13->addItem("گاو") ;
      ui->combobox_13->addItem("برداشت") ;

      ui->combobox_14->addItem("") ;
      ui->combobox_14->addItem("خرید زمین") ;
      ui->combobox_14->addItem("کاشت گندم") ;
      ui->combobox_14->addItem("کاشت جو") ;
      ui->combobox_14->addItem("مرغ") ;
      ui->combobox_14->addItem("گوسفند") ;
      ui->combobox_14->addItem("گاو") ;
      ui->combobox_14->addItem("برداشت") ;

      ui->combobox_15->addItem("") ;
      ui->combobox_15->addItem("خرید زمین") ;
      ui->combobox_15->addItem("کاشت گندم") ;
      ui->combobox_15->addItem("کاشت جو") ;
      ui->combobox_15->addItem("مرغ") ;
      ui->combobox_15->addItem("گوسفند") ;
      ui->combobox_15->addItem("گاو") ;
      ui->combobox_15->addItem("برداشت") ;

      ui->combobox_16->addItem("") ;
      ui->combobox_16->addItem("خرید زمین") ;
      ui->combobox_16->addItem("کاشت گندم") ;
      ui->combobox_16->addItem("کاشت جو") ;
      ui->combobox_16->addItem("مرغ") ;
      ui->combobox_16->addItem("گوسفند") ;
      ui->combobox_16->addItem("گاو") ;
      ui->combobox_16->addItem("برداشت") ;

      ui->combobox_17->addItem("") ;
      ui->combobox_17->addItem("خرید زمین") ;
      ui->combobox_17->addItem("کاشت گندم") ;
      ui->combobox_17->addItem("کاشت جو") ;
      ui->combobox_17->addItem("مرغ") ;
      ui->combobox_17->addItem("گوسفند") ;
      ui->combobox_17->addItem("گاو") ;
      ui->combobox_17->addItem("برداشت") ;

      ui->combobox_21->addItem("") ;
      ui->combobox_21->addItem("خرید زمین") ;
      ui->combobox_21->addItem("کاشت گندم") ;
      ui->combobox_21->addItem("کاشت جو") ;
      ui->combobox_21->addItem("مرغ") ;
      ui->combobox_21->addItem("گوسفند") ;
      ui->combobox_21->addItem("گاو") ;
      ui->combobox_21->addItem("برداشت") ;

      ui->combobox_22->addItem("") ;
      ui->combobox_22->addItem("خرید زمین") ;
      ui->combobox_22->addItem("کاشت گندم") ;
      ui->combobox_22->addItem("کاشت جو") ;
      ui->combobox_22->addItem("مرغ") ;
      ui->combobox_22->addItem("گوسفند") ;
      ui->combobox_22->addItem("گاو") ;
      ui->combobox_22->addItem("برداشت") ;

      ui->combobox_23->addItem("") ;
      ui->combobox_23->addItem("خرید زمین") ;
      ui->combobox_23->addItem("کاشت گندم") ;
      ui->combobox_23->addItem("کاشت جو") ;
      ui->combobox_23->addItem("مرغ") ;
      ui->combobox_23->addItem("گوسفند") ;
      ui->combobox_23->addItem("گاو") ;
      ui->combobox_23->addItem("برداشت") ;

      ui->combobox_24->addItem("") ;
      ui->combobox_24->addItem("خرید زمین") ;
      ui->combobox_24->addItem("کاشت گندم") ;
      ui->combobox_24->addItem("کاشت جو") ;
      ui->combobox_24->addItem("مرغ") ;
      ui->combobox_24->addItem("گوسفند") ;
      ui->combobox_24->addItem("گاو") ;
      ui->combobox_24->addItem("برداشت") ;

      ui->combobox_25->addItem("") ;
      ui->combobox_25->addItem("خرید زمین") ;
      ui->combobox_25->addItem("کاشت گندم") ;
      ui->combobox_25->addItem("کاشت جو") ;
      ui->combobox_25->addItem("مرغ") ;
      ui->combobox_25->addItem("گوسفند") ;
      ui->combobox_25->addItem("گاو") ;
      ui->combobox_25->addItem("برداشت") ;

      ui->combobox_26->addItem("") ;
      ui->combobox_26->addItem("خرید زمین") ;
      ui->combobox_26->addItem("کاشت گندم") ;
      ui->combobox_26->addItem("کاشت جو") ;
      ui->combobox_26->addItem("مرغ") ;
      ui->combobox_26->addItem("گوسفند") ;
      ui->combobox_26->addItem("گاو") ;
      ui->combobox_26->addItem("برداشت") ;

      ui->combobox_27->addItem("") ;
      ui->combobox_27->addItem("خرید زمین") ;
      ui->combobox_27->addItem("کاشت گندم") ;
      ui->combobox_27->addItem("کاشت جو") ;
      ui->combobox_27->addItem("مرغ") ;
      ui->combobox_27->addItem("گوسفند") ;
      ui->combobox_27->addItem("گاو") ;
      ui->combobox_27->addItem("برداشت") ;

      ui->combobox_31->addItem("") ;
      ui->combobox_31->addItem("خرید زمین") ;
      ui->combobox_31->addItem("کاشت گندم") ;
      ui->combobox_31->addItem("کاشت جو") ;
      ui->combobox_31->addItem("مرغ") ;
      ui->combobox_31->addItem("گوسفند") ;
      ui->combobox_31->addItem("گاو") ;
      ui->combobox_31->addItem("برداشت") ;

      ui->combobox_32->addItem("") ;
      ui->combobox_32->addItem("خرید زمین") ;
      ui->combobox_32->addItem("کاشت گندم") ;
      ui->combobox_32->addItem("کاشت جو") ;
      ui->combobox_32->addItem("مرغ") ;
      ui->combobox_32->addItem("گوسفند") ;
      ui->combobox_32->addItem("گاو") ;
      ui->combobox_32->addItem("برداشت") ;

      ui->combobox_33->addItem("") ;
      ui->combobox_33->addItem("خرید زمین") ;
      ui->combobox_33->addItem("کاشت گندم") ;
      ui->combobox_33->addItem("کاشت جو") ;
      ui->combobox_33->addItem("مرغ") ;
      ui->combobox_33->addItem("گوسفند") ;
      ui->combobox_33->addItem("گاو") ;
      ui->combobox_33->addItem("برداشت") ;

      ui->combobox_34->addItem("") ;
      ui->combobox_34->addItem("خرید زمین") ;
      ui->combobox_34->addItem("کاشت گندم") ;
      ui->combobox_34->addItem("کاشت جو") ;
      ui->combobox_34->addItem("مرغ") ;
      ui->combobox_34->addItem("گوسفند") ;
      ui->combobox_34->addItem("گاو") ;
      ui->combobox_34->addItem("برداشت") ;

      ui->combobox_35->addItem("") ;
      ui->combobox_35->addItem("خرید زمین") ;
      ui->combobox_35->addItem("کاشت گندم") ;
      ui->combobox_35->addItem("کاشت جو") ;
      ui->combobox_35->addItem("مرغ") ;
      ui->combobox_35->addItem("گوسفند") ;
      ui->combobox_35->addItem("گاو") ;
      ui->combobox_35->addItem("برداشت") ;

      ui->combobox_36->addItem("") ;
      ui->combobox_36->addItem("خرید زمین") ;
      ui->combobox_36->addItem("کاشت گندم") ;
      ui->combobox_36->addItem("کاشت جو") ;
      ui->combobox_36->addItem("مرغ") ;
      ui->combobox_36->addItem("گوسفند") ;
      ui->combobox_36->addItem("گاو") ;
      ui->combobox_36->addItem("برداشت") ;

      ui->combobox_37->addItem("") ;
      ui->combobox_37->addItem("خرید زمین") ;
      ui->combobox_37->addItem("کاشت گندم") ;
      ui->combobox_37->addItem("کاشت جو") ;
      ui->combobox_37->addItem("مرغ") ;
      ui->combobox_37->addItem("گوسفند") ;
      ui->combobox_37->addItem("گاو") ;
      ui->combobox_37->addItem("برداشت") ;

      ui->combobox_41->addItem("") ;
      ui->combobox_41->addItem("خرید زمین") ;
      ui->combobox_41->addItem("کاشت گندم") ;
      ui->combobox_41->addItem("کاشت جو") ;
      ui->combobox_41->addItem("مرغ") ;
      ui->combobox_41->addItem("گوسفند") ;
      ui->combobox_41->addItem("گاو") ;
      ui->combobox_41->addItem("برداشت") ;

      ui->combobox_42->addItem("") ;
      ui->combobox_42->addItem("خرید زمین") ;
      ui->combobox_42->addItem("کاشت گندم") ;
      ui->combobox_42->addItem("کاشت جو") ;
      ui->combobox_42->addItem("مرغ") ;
      ui->combobox_42->addItem("گوسفند") ;
      ui->combobox_42->addItem("گاو") ;
      ui->combobox_42->addItem("برداشت") ;

      ui->combobox_43->addItem("") ;
      ui->combobox_43->addItem("خرید زمین") ;
      ui->combobox_43->addItem("کاشت گندم") ;
      ui->combobox_43->addItem("کاشت جو") ;
      ui->combobox_43->addItem("مرغ") ;
      ui->combobox_43->addItem("گوسفند") ;
      ui->combobox_43->addItem("گاو") ;
      ui->combobox_43->addItem("برداشت") ;

      ui->combobox_44->addItem("") ;
      ui->combobox_44->addItem("خرید زمین") ;
      ui->combobox_44->addItem("کاشت گندم") ;
      ui->combobox_44->addItem("کاشت جو") ;
      ui->combobox_44->addItem("مرغ") ;
      ui->combobox_44->addItem("گوسفند") ;
      ui->combobox_44->addItem("گاو") ;
      ui->combobox_44->addItem("برداشت") ;

      ui->combobox_45->addItem("") ;
      ui->combobox_45->addItem("خرید زمین") ;
      ui->combobox_45->addItem("کاشت گندم") ;
      ui->combobox_45->addItem("کاشت جو") ;
      ui->combobox_45->addItem("مرغ") ;
      ui->combobox_45->addItem("گوسفند") ;
      ui->combobox_45->addItem("گاو") ;
      ui->combobox_45->addItem("برداشت") ;

      ui->combobox_46->addItem("") ;
      ui->combobox_46->addItem("خرید زمین") ;
      ui->combobox_46->addItem("کاشت گندم") ;
      ui->combobox_46->addItem("کاشت جو") ;
      ui->combobox_46->addItem("مرغ") ;
      ui->combobox_46->addItem("گوسفند") ;
      ui->combobox_46->addItem("گاو") ;
      ui->combobox_46->addItem("برداشت") ;

      ui->combobox_47->addItem("") ;
      ui->combobox_47->addItem("خرید زمین") ;
      ui->combobox_47->addItem("کاشت گندم") ;
      ui->combobox_47->addItem("کاشت جو") ;
      ui->combobox_47->addItem("مرغ") ;
      ui->combobox_47->addItem("گوسفند") ;
      ui->combobox_47->addItem("گاو") ;
      ui->combobox_47->addItem("برداشت") ;
}

// timer
void bazi2nafare_game::updateCountdown()
{
    countdownTime = countdownTime.addSecs(-1);
    ui->label_timer->setText(countdownTime.toString("          mm:ss"));

    if (countdownTime == QTime(0, 0))
    {
        savecoin_database() ;

        timer->stop() ;
        QMessageBox::information(this, "زمان", "پایان وقت!") ;

        if(a == 1)
        {
            update_data() ;
            a++ ;

            this->hide() ;
            bazi2nafare_game *w3 = new bazi2nafare_game ;
            w3->show() ;
        }

        else
        {
            this->hide() ;
            winner_2nafare_game *w2 = new winner_2nafare_game ;
            w2->show() ;
        }
    }
}

void bazi2nafare_game::update_data()
{
    coin = 10 ;
    worker_num = 1 ;
    hen = 0 ;
    sheep = 0;
    cow = 0 ;
    wheat = 0 ;
    barley = 0 ;
    free_worker = 1;
    land = 1 ;
    buy_land = 0 ;
    free_hen = 0 ;
    free_sheep = 0 ;
    free_cow = 0;
    Egg = 0 ;
    milk_cow = 0 ;
    milk_sheep = 0 ;
    wheat_product = 0 ;
    barley_product = 0 ;
}

void bazi2nafare_game::savecoin_database()
{
    QString coin_1 = ui->lab_display_coin->text();
    QSqlQuery q ;

    q.exec("INSERT INTO WinnerPLayer(`coin`) values('"+coin_1+"')");
}


bazi2nafare_game::~bazi2nafare_game()
{
    delete ui;
}


void bazi2nafare_game::update_coin()
{
    ui->lab_display_coin->setText(QString::number(coin));
    ui->lab_display_coin->setAlignment(Qt::AlignCenter);
}


void bazi2nafare_game::update_worker_num()
{
    ui->lab_display_worker->setText(QString::number(worker_num));
    ui->lab_display_worker->setAlignment(Qt::AlignCenter);
}


void bazi2nafare_game::on_pushbutton_balance_product_clicked()
{
    QString message = "Hen : " + QString::number(hen) + "\nsheep : " + QString::number(sheep) + "\ncow : " + QString::number(cow) + "\nwheat : " + QString::number(wheat) + "\nbarley : " + QString::number(barley) + "\nfree worker : " + QString::number(free_worker) + "\nland : " + QString::number(land) ;

    QMessageBox::information(this , "موجودی" , message);

}

void bazi2nafare_game::on_comboBox_store_activated(int index)
{
    switch (index)
    {
    case 0 : // wheat
    {
        if(coin >= 2)
        {
        wheat ++ ;
        coin -= 2 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 1 : //barley
    {
        if(coin >= 2)
        {
        barley ++ ;
        coin -= 2 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
    }

    case 2 : //hen
    {
        if(coin >= 2)
        {
        hen ++ ;
        free_hen ++ ;

        coin -= 3 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 3 : //sheep
    {
        if(coin >= 5)
        {
        sheep ++ ;
        free_sheep ++ ;

        coin -= 5 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 4 : //cow
    {
        if(coin >= 7)
        {
        cow ++ ;
        free_cow ++ ;

        coin -= 7 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 5 : //land
    {
        if(coin >= 3)
        {
            land++ ;
            buy_land++ ;
            coin -= 3 ;

            update_coin() ;

            break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 6 : //free_worker
    {
        if(coin >=5)
        {
        worker_num++ ;
        free_worker ++ ;
        coin -= 5 ;

        update_coin() ;
        update_worker_num() ;
        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    }
}

// function marbut be morgh
void bazi2nafare_game::place_hen(int a)
{   
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/hen_2.png);");
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/hen_2.png);");
    }
}


int b{0} ;

void bazi2nafare_game::place_Egg()
{
    if(b == 11)
    {
    ui->combobox_11->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 12)
    {
    ui->combobox_12->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 13)
    {
    ui->combobox_13->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 14)
    {
    ui->combobox_14->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 15)
    {
    ui->combobox_15->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 16)
    {
    ui->combobox_16->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 17)
    {
    ui->combobox_17->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 21)
    {
    ui->combobox_21->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 22)
    {
    ui->combobox_22->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 23)
    {
    ui->combobox_23->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 24)
    {
    ui->combobox_24->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 25)
    {
    ui->combobox_25->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 26)
    {
    ui->combobox_26->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 27)
    {
    ui->combobox_27->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 31)
    {
    ui->combobox_31->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 32)
    {
    ui->combobox_32->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 33)
    {
    ui->combobox_33->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 34)
    {
    ui->combobox_34->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 35)
    {
    ui->combobox_35->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 36)
    {
    ui->combobox_36->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 37)
    {
    ui->combobox_37->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 41)
    {
    ui->combobox_41->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 42)
    {
    ui->combobox_42->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 43)
    {
    ui->combobox_43->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 44)
    {
    ui->combobox_44->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 45)
    {
    ui->combobox_45->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 46)
    {
    ui->combobox_46->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    else if(b == 47)
    {
    ui->combobox_47->setStyleSheet("image: url(:/egg(1).png);") ;
    }

    timer_takhir.start(20000) ;
    Egg++ ;
}


void bazi2nafare_game::place_cow(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/cow(1).png);");
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/cow(1).png);");
    }
}

int c{0} ;
int c_sheep{0} ;

void bazi2nafare_game::place_milk()
{
    if(c == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/milk.png);") ;
    }

    if(c_sheep == 1)
    {
        timer_takhir.start(12000) ;
        c_sheep -- ;
        milk_sheep++ ;
    }

    else
    {
        timer_takhir.start(15000) ;
        milk_cow++ ;
    }

}

void bazi2nafare_game::place_sheep(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/sheep.png);") ;
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/sheep.png);") ;
    }

    milk_sheep++ ;
}

int d{0} ;
int d_wheat{0} ;

void bazi2nafare_game::place_wheat_product()
{
    if(d == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    else if(d == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/wheat-sack.png);") ;
    }

    if(d_wheat == 1)
    {
        timer_takhir.start(36000) ;
        d_wheat-- ;
        wheat_product++ ;
    }

    else
    {
        timer_takhir.start(20000) ;
        barley_product++ ;
    }
}

void bazi2nafare_game::place_wheat_plant(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/wheat-plant.png);") ;
    }

}


void bazi2nafare_game::place_barley(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/barley(2).png);") ;
    }

    else if(a == 47)
    {
        ui->combobox_46->setStyleSheet("image: url(:/barley(2).png);") ;
    }
}


void bazi2nafare_game::on_combobox_12_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        QColor color = ui->combobox_12->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_12->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_12->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_12->setCurrentText("") ;
            break;
        }
        }

    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_12->setCurrentText("") ;

            d_wheat ++ ;
            d = 12 ;

            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(12) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_12->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_12->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_12->setCurrentText("") ;

            d = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(12) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_12->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_12->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_12->setCurrentText("") ;

            b = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(12) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_12->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_12->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_12->setCurrentText("") ;

            c_sheep++ ;
            c = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(12) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_12->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_12->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_12->setCurrentText("") ;

            c = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(12) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_12->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_12->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }


        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        { 
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_12->setCurrentText("") ;
        }
    }

    }
}


void bazi2nafare_game::on_combobox_13_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        QColor color = ui->combobox_13->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_13->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_13->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_13->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_13->setCurrentText("") ;

            d_wheat ++ ;
            d = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(13) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_13->setCurrentText("") ;
            break;
        }

    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_13->setCurrentText("") ;

            d = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(13) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_13->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_13->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_13->setCurrentText("") ;

            b = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            free_hen -- ;
            place_hen(13) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_13->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_13->setCurrentText("") ;
            break;
        }
    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_13->setCurrentText("") ;

            c_sheep++ ;
            c = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(13) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_13->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_13->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_13->setCurrentText("") ;

            c = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(13) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_13->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_13->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_13->setCurrentText("") ;
        }
    }

    }
}


void bazi2nafare_game::on_combobox_14_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        QColor color = ui->combobox_14->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_14->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_14->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_14->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_14->setCurrentText("") ;

            d_wheat ++ ;
            d = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(14) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_14->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_14->setCurrentText("") ;
            break;
        }

    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_14->setCurrentText("") ;

            d = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(14) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_14->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_14->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_14->setCurrentText("") ;

            b = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(14) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_14->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_14->setCurrentText("") ;
            break;
        }
    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_14->setCurrentText("") ;

            c_sheep++ ;
            c = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(14) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_14->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_14->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_14->setCurrentText("") ;

            c = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(14) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_14->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_14->setCurrentText("") ;
            break;
        }

    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_14->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_15_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        QColor color = ui->combobox_15->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_15->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_15->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_15->setCurrentText("") ;
            break;
        }
        }

    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_15->setCurrentText("") ;

            d_wheat ++ ;
            d = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(15) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_15->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_15->setCurrentText("") ;
            break;
        }

    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_15->setCurrentText("") ;

            d = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(15) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_15->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_15->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_15->setCurrentText("") ;

            b = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(15) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_15->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_15->setCurrentText("") ;
            break;
        }
    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_15->setCurrentText("") ;

            c_sheep++ ;
            c = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(15) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_15->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_15->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_15->setCurrentText("") ;

            c = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(15) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_15->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_15->setCurrentText("") ;
            break;
        }

    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_15->setCurrentText("") ;
        }
    }

    }
}


void bazi2nafare_game::on_combobox_16_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        QColor color = ui->combobox_16->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_16->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_16->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_16->setCurrentText("") ;
            break;
        }
        }

    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_16->setCurrentText("") ;

            d_wheat ++ ;
            d = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(16) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_16->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_16->setCurrentText("") ;
            break;
        }

    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_16->setCurrentText("") ;

            d = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(16) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_16->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_16->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_16->setCurrentText("") ;

            b = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(16) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_16->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_16->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_16->setCurrentText("") ;

            c_sheep++ ;
            c = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(16) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_16->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_16->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_16->setCurrentText("") ;

            c = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(16) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_16->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_16->setCurrentText("") ;
            break;
        }

    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_16->setCurrentText("") ;
        }
    }

    }
}


void bazi2nafare_game::on_combobox_17_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        QColor color = ui->combobox_17->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_17->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_17->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_17->setCurrentText("") ;
            break;
        }
        }

    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_17->setCurrentText("") ;

            d_wheat ++ ;
            d = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(17) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_17->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_17->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_17->setCurrentText("") ;

            d =  17 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(17) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_17->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_17->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_17->setCurrentText("") ;

            b = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(17) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_17->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_17->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_17->setCurrentText("") ;

            c_sheep++ ;
            c = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(17) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_17->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_17->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_17->setCurrentText("") ;

            c = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(17) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_17->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_17->setCurrentText("") ;
            break;
        }

    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_17->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_11_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_11->setCurrentText("") ;

            d_wheat ++ ;
            d = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(11) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_11->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_11->setCurrentText("") ;
            break;
        }
    }

    case 2 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_11->setCurrentText("") ;

            d = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(11) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_11->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_11->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_11->setCurrentText("") ;

            b = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(11) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_11->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_11->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_11->setCurrentText("") ;

            c_sheep++ ;
            c = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(11) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_11->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_11->setCurrentText("") ;
            break;
        }
    }

    case 5 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_11->setCurrentText("") ;

            c = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(11) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_11->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_11->setCurrentText("") ;
            break;
        }

    }

    case 6 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_11->setCurrentText("") ;
        }

    }
    }
}

void bazi2nafare_game::on_combobox_21_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_21->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_21->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_21->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_21->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_21->setCurrentText("") ;

            d_wheat ++ ;
            d = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(21) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_21->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_21->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_21->setCurrentText("") ;

            d = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(21) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_21->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_21->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_21->setCurrentText("") ;

            b = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg(21)));

            place_hen(21) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_21->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_21->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_21->setCurrentText("") ;

            c_sheep++ ;
            c = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(21) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_21->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_21->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_21->setCurrentText("") ;

            c = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(21) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_21->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_21->setCurrentText("") ;
            break;
        }

    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_21->setCurrentText("") ;
        }
    }
    }
}

void bazi2nafare_game::on_combobox_22_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_22->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_22->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_22->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_22->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_22->setCurrentText("") ;

            d_wheat ++ ;
            d = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(22) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_22->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_22->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_22->setCurrentText("") ;

            d = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(22) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_22->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_22->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_22->setCurrentText("") ;

            b = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(22) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_22->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_22->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_22->setCurrentText("") ;

            c_sheep++ ;
            c = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(22) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_22->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_22->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_22->setCurrentText("") ;

            c = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(22) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_22->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_22->setCurrentText("") ;
            break;
        }

    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5 ;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_22->setCurrentText("") ;
        }
    }
    }
}

void bazi2nafare_game::on_combobox_23_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_23->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_23->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_23->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_23->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_23->setCurrentText("") ;

            d_wheat ++ ;
            d = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(23) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_23->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_23->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_23->setCurrentText("") ;

            d = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(23) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_23->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_23->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_23->setCurrentText("") ;

            b = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(23) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_23->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_23->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_23->setCurrentText("") ;

            c_sheep++ ;
            c = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(23) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_23->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_23->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_23->setCurrentText("") ;

            c = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(23) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_23->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_23->setCurrentText("") ;
            break;
        }

    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_23->setCurrentText("") ;
        }
    }
    }
}

void bazi2nafare_game::on_combobox_24_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_24->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_24->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_24->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_24->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_24->setCurrentText("") ;

            d_wheat ++ ;
            d = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(24) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_24->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_24->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_24->setCurrentText("") ;

            d = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(24) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_24->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_24->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_24->setCurrentText("") ;

            b = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(24) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_24->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_24->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_24->setCurrentText("") ;

            c_sheep++ ;
            c = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(24) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_24->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_24->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_24->setCurrentText("") ;

            c = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(24) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_24->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_24->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_24->setCurrentText("") ;
        }
    }
    }
}

void bazi2nafare_game::on_combobox_25_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_25->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_25->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_25->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_25->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_25->setCurrentText("") ;

            d_wheat ++ ;
            d = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(25) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_25->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_25->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_25->setCurrentText("") ;

            d = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(25) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_25->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_25->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_25->setCurrentText("") ;

            b = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(25) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_25->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_25->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_25->setCurrentText("") ;

            c_sheep++ ;
            c = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(25) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_25->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_25->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_25->setCurrentText("") ;

            c = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(25) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_25->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_25->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_25->setCurrentText("") ;
        }
    }
    }

}

void bazi2nafare_game::on_combobox_26_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_26->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_26->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_26->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_26->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_26->setCurrentText("") ;

            d_wheat ++ ;
            d = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(26) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_26->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_26->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_26->setCurrentText("") ;

            d = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(26) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_26->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_26->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_26->setCurrentText("") ;

            b = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(26) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_26->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_26->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_26->setCurrentText("") ;

            c_sheep++ ;
            c = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(26) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_26->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_26->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_26->setCurrentText("") ;

            c = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(26) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_26->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_26->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_26->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_27_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        QColor color = ui->combobox_27->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_27->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_27->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_27->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_27->setCurrentText("") ;

            d_wheat ++ ;
            d = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(27) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_27->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_27->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_27->setCurrentText("") ;

            d = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(27) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_27->setCurrentText("") ;;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_27->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_27->setCurrentText("") ;

            b = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(27) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_27->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_27->setCurrentText("") ;

            c_sheep++ ;
            c = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(27) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_27->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_27->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_27->setCurrentText("") ;

            c = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(27) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_27->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_27->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_27->setCurrentText("") ;
        }
    }


    }
}

void bazi2nafare_game::on_combobox_31_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_31->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_31->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_31->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_31->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_31->setCurrentText("") ;

            d_wheat ++ ;
            d = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(31) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_31->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_31->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_31->setCurrentText("") ;

            d = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(31) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_31->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_31->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_31->setCurrentText("") ;

            b = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(31) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_31->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_31->setCurrentText("") ;
            break;
        }


    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_31->setCurrentText("") ;

            c_sheep++ ;
            c = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(31) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_31->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_31->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_31->setCurrentText("") ;

            c = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(31) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_31->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_31->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_31->setCurrentText("") ;
        }
    }
    }
}

void bazi2nafare_game::on_combobox_32_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_32->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_32->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_32->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_32->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_32->setCurrentText("") ;

            d_wheat ++ ;
            d = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(32) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_32->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_32->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_32->setCurrentText("") ;

            d = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(32) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_32->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_32->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_32->setCurrentText("") ;

            b = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(32) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_32->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_32->setCurrentText("") ;
            break;
        }


    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_32->setCurrentText("") ;

            c_sheep++ ;
            c = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(32) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_32->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_32->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_32->setCurrentText("") ;

            c = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(32) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_32->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_32->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_32->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_33_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_33->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_33->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_33->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_33->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_33->setCurrentText("") ;

            d_wheat ++ ;
            d = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(33) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_33->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_33->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_33->setCurrentText("") ;

            d = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(33) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_33->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_33->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_33->setCurrentText("") ;

            b = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(33) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_33->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_33->setCurrentText("") ;
            break;
        }



    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_33->setCurrentText("") ;

            c_sheep++ ;
            c = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(33) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_33->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_33->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_33->setCurrentText("") ;

            c = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(33) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_33->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_33->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_33->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_34_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_34->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_34->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_34->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_34->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_34->setCurrentText("") ;

            d_wheat ++ ;
            d = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(34) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_34->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_34->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_34->setCurrentText("") ;

            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(34) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_34->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_34->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_34->setCurrentText("") ;

            b = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(34) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_34->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_34->setCurrentText("") ;
            break;
        }



    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_34->setCurrentText("") ;

            c_sheep++ ;
            c = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(34) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_34->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_34->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_34->setCurrentText("") ;

            c = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(34) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_34->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_34->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_34->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_35_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_35->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_35->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_35->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_35->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_35->setCurrentText("") ;

            d_wheat ++ ;
            d = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(35) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_35->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_35->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_35->setCurrentText("") ;

            d = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(35) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_35->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_35->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_35->setCurrentText("") ;

            b = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(35) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_35->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_35->setCurrentText("") ;
            break;
        }


    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_35->setCurrentText("") ;

            c_sheep++ ;
            c = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(35) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_35->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_35->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_35->setCurrentText("") ;

            c = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(35) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_35->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_35->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_35->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_36_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_36->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_36->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_36->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_36->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_36->setCurrentText("") ;

            d_wheat ++ ;
            d = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(36) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_36->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_36->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_36->setCurrentText("") ;

            d = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(36) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_36->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_36->setCurrentText("") ;

            b = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(36) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_36->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_36->setCurrentText("") ;
            break;
        }

    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_36->setCurrentText("") ;

            c_sheep++ ;
            c = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(36) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_36->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_36->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_36->setCurrentText("") ;

            c = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(36) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_36->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_36->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_36->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_37_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_37->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_37->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_37->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_37->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_37->setCurrentText("") ;

            d_wheat ++ ;
            d = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(37) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_37->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_37->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_37->setCurrentText("") ;

            d = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(37) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_37->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_37->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_37->setCurrentText("") ;

            b = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(37) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_37->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_37->setCurrentText("") ;
            break;
        }



    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_37->setCurrentText("") ;

            c_sheep++ ;
            c = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(37) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_37->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_37->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_37->setCurrentText("") ;

            c = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(37) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_37->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_37->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_37->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_41_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_41->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_41->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_41->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_41->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_41->setCurrentText("") ;

            d_wheat ++ ;
            d = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(41) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_41->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_41->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_41->setCurrentText("") ;

            d = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(41) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_41->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_41->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_41->setCurrentText("") ;

            b = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(41) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_41->setCurrentText("") ;
                break;
            }
        }

        else if(barley_product >= 0)
        {
            coin += 3;
            update_coin() ;

            ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
            ui->combobox_41->setCurrentText("") ;

            barley_product-- ;
            free_worker++ ;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_41->setCurrentText("") ;
            break;
        }



    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_41->setCurrentText("") ;

            c_sheep++ ;
            c = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(41) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_41->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_41->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_41->setCurrentText("") ;

            c = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(41) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_41->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_41->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_41->setCurrentText("") ;
        }
    }

    }
}


void bazi2nafare_game::on_combobox_42_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_42->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_42->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_42->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_42->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_42->setCurrentText("") ;

            d_wheat ++ ;
            d = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(42) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_42->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_42->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_42->setCurrentText("") ;

            d = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(42) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_42->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_42->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_42->setCurrentText("") ;

            b = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(42) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_42->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_42->setCurrentText("") ;
            break;
        }


    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_42->setCurrentText("") ;

            c_sheep++ ;
            c = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(42) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_42->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_42->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_42->setCurrentText("") ;

            c = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(42) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_42->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_42->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_42->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_43_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_43->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_43->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_43->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_43->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_43->setCurrentText("") ;

            d_wheat ++ ;
            d = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(43) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_43->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_43->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_43->setCurrentText("") ;

            d = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(43) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_43->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_43->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_43->setCurrentText("") ;

            b = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(43) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_43->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_43->setCurrentText("") ;
            break;
        }



    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_43->setCurrentText("") ;

            c_sheep++ ;
            c = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(43) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_43->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_43->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_43->setCurrentText("") ;

            c = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(43) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_43->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_43->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_43->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_44_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_44->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_44->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_44->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_44->setCurrentText("") ;
            break;
        }
        }
    }

    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_44->setCurrentText("") ;

            d_wheat ++ ;
            d = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(44) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_44->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_44->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_44->setCurrentText("") ;

            d = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(44) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_44->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_44->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_44->setCurrentText("") ;

            b = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg(44)));

            place_hen(44) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_44->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_44->setCurrentText("") ;
            break;
        }



    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_44->setCurrentText("") ;

            c_sheep++ ;
            c = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(44) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_44->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_44->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_44->setCurrentText("") ;

            c = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(44) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_44->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_44->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_44->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_45_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_45->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_45->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_45->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_45->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_45->setCurrentText("") ;

            d_wheat ++ ;
            d = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(45) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_45->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_45->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_45->setCurrentText("") ;

            d = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(45) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_45->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_45->setCurrentText("") ;
            break;
        }
    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_45->setCurrentText("") ;

            b = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg(45)));

            place_hen(45) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_45->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_45->setCurrentText("") ;
            break;
        }


    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_45->setCurrentText("") ;

            c_sheep++ ;
            c = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(45) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_45->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_45->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_45->setCurrentText("") ;

            c = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(45) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_45->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_45->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_45->setCurrentText("") ;
        }
    }

    }
}


void bazi2nafare_game::on_combobox_46_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_46->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_46->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_46->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_46->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_46->setCurrentText("") ;

            d_wheat ++ ;
            d = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(46) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_46->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_46->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_46->setCurrentText("") ;

            d = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(46) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_46->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_46->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_46->setCurrentText("") ;

            b = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(46) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_46->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_46->setCurrentText("") ;
            break;
        }


    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_46->setCurrentText("") ;

            c_sheep++ ;
            c = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(46) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_46->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_46->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_46->setCurrentText("") ;

            c = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(46) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_46->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_46->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_46->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_combobox_47_activated(int index)
{
    switch(index)
    {

    case 1 :
    {
        QColor color = ui->combobox_47->palette().color(QPalette::Button);
        QColor desiredColor("#2ecc71");

        if(color == desiredColor)
        {
            QMessageBox::information(this , "خطا" , "قبلا این زمین را خریداری کرده اید") ;
            ui->combobox_47->setCurrentText("") ;
            break ;
        }

        else
        {
        if(buy_land >= 1)
        {
            ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;");

            buy_land -- ;
            ui->combobox_47->setCurrentText("") ;

            break;
        }
        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه زمین خریداری کنید") ;
            ui->combobox_47->setCurrentText("") ;
            break;
        }
        }
    }


    case 2 :
    {
        if(wheat >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_47->setCurrentText("") ;

            d_wheat ++ ;
            d = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_wheat_plant(47) ;

            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_47->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گندم خریداری کنید") ;
            ui->combobox_47->setCurrentText("") ;
            break;
        }
    }

    case 3 :
    {
        if(barley >= 1)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_47->setCurrentText("") ;

            d = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product()));

            place_barley(47) ;

            break;

            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_47->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه جو خریداری کنید") ;
            ui->combobox_47->setCurrentText("") ;
            break;
        }

    }

    case 4 :
    {
        if(hen - free_hen >= 0 && hen != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_47->setCurrentText("") ;

            b = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg()));

            place_hen(47) ;

            free_hen -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_47->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه مرغ خریداری کنید") ;
            ui->combobox_47->setCurrentText("") ;
            break;
        }



    }

    case 5 :
    {
        if(sheep - free_sheep >= 0 && sheep != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_47->setCurrentText("") ;

            c_sheep++ ;
            c = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(47) ;

            free_sheep -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_47->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گوسفند خریداری کنید") ;
            ui->combobox_47->setCurrentText("") ;
            break;
        }
    }

    case 6 :
    {
        if(cow - free_cow >= 0 && cow != 0)
        {
            if(free_worker != 0)
            {
            free_worker -- ;
            ui->combobox_47->setCurrentText("") ;

            c = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(47) ;

            free_cow -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_47->setCurrentText("") ;
                break;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "از فروشگاه گاو خریداری کنید") ;
            ui->combobox_47->setCurrentText("") ;
            break;
        }
    }

    case 7 :
    {
        if(Egg >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg-- ;
                free_hen ++ ;
                free_worker++ ;
            }
        }

        else if(milk_cow >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin += 4;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin += 5;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow-- ;
                free_cow ++ ;
                free_worker++ ;
            }
        }

        else if(milk_sheep >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep-- ;
                free_sheep ++ ;
                free_worker++ ;
            }
        }

        else if(wheat_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product-- ;
                free_worker++ ;
            }

        }

        else if(barley_product >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                barley_product-- ;
                free_worker++ ;
            }
        }

        else
        {
            QMessageBox::information(this , "خطا" , "ایتمی برای برداشت وجود ندارد") ;
            ui->combobox_47->setCurrentText("") ;
        }
    }

    }
}

void bazi2nafare_game::on_comboBox_kill_activated(int index)
{
    switch(index)
    {

    case 0 :
    {
        if(free_hen >= 1)
        {
            coin += 3 ;
            update_coin() ;
            ui->comboBox_kill->setCurrentText("") ;
            hen -- ;
            break ;
        }

        else
        {
            QMessageBox::information(this , "قصاب" , "مرغ ازادی وجود ندارد") ;
            break ;
        }
    }

    case 1 :
    {
        if(free_sheep >= 1)
        {
            coin += 4 ;
            update_coin() ;
            ui->comboBox_kill->setCurrentText("") ;
            sheep -- ;
            break ;
        }

        else
        {
            QMessageBox::information(this , "قصاب" , "گوسفند ازادی وجود ندارد") ;
            break ;
        }

    }

    case 2 :
    {
        if(free_cow >= 1)
        {
            coin += 6 ;
            update_coin() ;
            ui->comboBox_kill->setCurrentText("") ;
            cow -- ;
            break ;
        }

        else
        {
            QMessageBox::information(this , "قصاب" , "گاو ازادی وجود ندارد") ;
            break ;
        }
    }

    }
}

