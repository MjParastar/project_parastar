#include "bazi3nafare_game.h"
#include "ui_bazi3nafare_game.h"

#include "iostream"

#include "winner_3nafare_game.h"

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

int coin_3 = 10 ;
int worker_num_3 = 1 ;
int hen_3{0} , sheep_3{0} , cow_3{0} , wheat_3{0} , barley_3{0} , free_worker_3{1} , land_3{1} , buy_land_3{0};

int free_hen_3{0} ;
int free_sheep_3{0} ;
int free_cow_3{0} ;

int Egg_3{0} ;
int milk_cow_3{0} ;
int milk_sheep_3{0} ;
int wheat_product_3{0} ;
int barley_product_3{0} ;

int a_3 = 1 ;

bazi3nafare_game::bazi3nafare_game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bazi3nafare_game)
{
    ui->setupUi(this);

    //relate to database and display on label
    QSqlDatabase database ;
    database = QSqlDatabase::addDatabase("QSQLITE") ;
    database.setDatabaseName("C:\\Personal\\AdvancedMabani\\ProjectQt\\Database\\Player.db") ;

    if (database.open())
    {
        QSqlQuery query;
        if(a_3 == 1)
        {
            query.prepare("SELECT Username FROM Player LIMIT 1");
        }
        else if(a_3 == 2)
        {
            query.prepare("SELECT Username FROM Player LIMIT 1 OFFSET 1");
        }
        else if(a_3 == 3)
        {
            query.prepare("SELECT Username FROM Player LIMIT 1 OFFSET 2");
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



    //relate coin_3
    QSqlDatabase database_2 ;
    database = QSqlDatabase::addDatabase("QSQLITE") ;
    database.setDatabaseName("C:\\Personal\\AdvancedMabani\\ProjectQt\\Database\\coin_3.db") ;
    database.open() ;

    if(a_3 == 2)
    {
        ui->label_6->setText("   کاربر دوم") ;
    }

    if(a_3 == 3)
    {
        ui->label_6->setText("   کاربر سوم") ;
    }

    ui->lab_display_name->setAlignment(Qt::AlignCenter);

    update_coin() ;
    update_worker_num() ;

    setMaximumSize(966,529) ;
    setMinimumSize(966,529) ;


    ui->comboBox_kill->addItem("(3$)مرغ") ;
    ui->comboBox_kill->addItem("(4$)گوسفند") ;
    ui->comboBox_kill->addItem("(6$)گاو") ;

    ui->comboBox_kill->setItemData(0, QIcon(":/hen_3.png"), Qt::DecorationRole);
    ui->comboBox_kill->setItemData(1, QIcon(":/black-sheep_3.png"), Qt::DecorationRole);
    ui->comboBox_kill->setItemData(2, QIcon(":/cow_3.png"), Qt::DecorationRole);

    ui->comboBox_store->addItem("گندم($2)") ;
    ui->comboBox_store->addItem("جو($2)") ;
    ui->comboBox_store->addItem("(3$)مرغ") ;
    ui->comboBox_store->addItem("(5$)گوسفند") ;
    ui->comboBox_store->addItem("(7$)گاو") ;
    ui->comboBox_store->addItem("زمین($3)") ;
    ui->comboBox_store->addItem("(5$)کارگر") ;

    ui->comboBox_store->setItemData(0, QIcon(":/wheat_3-grains.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(1, QIcon(":/barley_3.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(2, QIcon(":/hen_3.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(3, QIcon(":/black-sheep_3.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(4, QIcon(":/cow_3.png"), Qt::DecorationRole);
    ui->comboBox_store->setItemData(5, QIcon(":/land_3.png"), Qt::DecorationRole);
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
void bazi3nafare_game::updateCountdown()
{
    countdownTime = countdownTime.addSecs(-1);
    ui->label_timer->setText(countdownTime.toString("          mm:ss"));

    if (countdownTime == QTime(0, 0))
    {
        savecoin_database() ;

        timer->stop() ;
        QMessageBox::information(this, "زمان", "پایان وقت!") ;

        if(a_3 == 1)
        {
            update_data() ;
            a_3++ ;

            this->hide() ;
            bazi3nafare_game *w2 = new bazi3nafare_game ;
            w2->show() ;
        }

        else if(a_3 == 2)
        {
            update_data() ;
            a_3++ ;

            this->hide() ;
            winner_3nafare_game *w3 = new winner_3nafare_game ;
            w3->show() ;
        }

        else
        {
            this->hide() ;
            winner_3nafare_game *w4 = new winner_3nafare_game ;
            w4->show() ;
        }
    }
}

void bazi3nafare_game::update_data()
{
    coin_3 = 10 ;
    worker_num_3 = 1 ;
    hen_3 = 0 ;
    sheep_3 = 0;
    cow_3 = 0 ;
    wheat_3 = 0 ;
    barley_3 = 0 ;
    free_worker_3 = 1;
    land_3 = 1 ;
    buy_land_3 = 0 ;
    free_hen_3 = 0 ;
    free_sheep_3 = 0 ;
    free_cow_3 = 0;
    Egg_3 = 0 ;
    milk_cow_3 = 0 ;
    milk_sheep_3 = 0 ;
    wheat_product_3 = 0 ;
    barley_product_3 = 0 ;
}

void bazi3nafare_game::savecoin_database()
{
    QString coin_3_1 = ui->lab_display_coin->text();
    QSqlQuery q ;

    q.exec("INSERT INTO WinnerPLayer(`coin_3`) values('"+coin_3_1+"')");
}

bazi3nafare_game::~bazi3nafare_game()
{
    delete ui;
}

void bazi3nafare_game::update_coin()
{
    ui->lab_display_coin->setText(QString::number(coin_3));
    ui->lab_display_coin->setAlignment(Qt::AlignCenter);
}


void bazi3nafare_game::update_worker_num()
{
    ui->lab_display_worker->setText(QString::number(worker_num_3));
    ui->lab_display_worker->setAlignment(Qt::AlignCenter);
}


void bazi3nafare_game::on_pushbutton_balance_product_clicked()
{
    QString message = "hen_3 : " + QString::number(hen_3) + "\nsheep_3 : " + QString::number(sheep_3) + "\ncow_3 : " + QString::number(cow_3) + "\nwheat_3 : " + QString::number(wheat_3) + "\nbarley_3 : " + QString::number(barley_3) + "\nfree worker : " + QString::number(free_worker_3) + "\nland_3 : " + QString::number(land_3) ;

    QMessageBox::information(this , "موجودی" , message);

}

void bazi3nafare_game::on_comboBox_store_activated(int index)
{
    switch (index)
    {
    case 0 : // wheat_3
    {
        if(coin_3 >= 2)
        {
        wheat_3 ++ ;
        coin_3 -= 2 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 1 : //barley_3
    {
        if(coin_3 >= 2)
        {
        barley_3 ++ ;
        coin_3 -= 2 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
    }

    case 2 : //hen_3
    {
        if(coin_3 >= 2)
        {
        hen_3 ++ ;
        free_hen_3 ++ ;

        coin_3 -= 3 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 3 : //sheep_3
    {
        if(coin_3 >= 5)
        {
        sheep_3 ++ ;
        free_sheep_3 ++ ;

        coin_3 -= 5 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 4 : //cow_3
    {
        if(coin_3 >= 7)
        {
        cow_3 ++ ;
        free_cow_3 ++ ;

        coin_3 -= 7 ;

        update_coin() ;

        break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 5 : //land_3
    {
        if(coin_3 >= 3)
        {
            land_3++ ;
            buy_land_3++ ;
            coin_3 -= 3 ;

            update_coin() ;

            break;
        }

        else
        {
            QMessageBox::information(this , "خطا" , "موجودی ناکافی است") ;
            break;
        }
     }

    case 6 : //free_worker_3
    {
        if(coin_3 >=5)
        {
        worker_num_3++ ;
        free_worker_3 ++ ;
        coin_3 -= 5 ;

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
void bazi3nafare_game::place_hen(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/hen_3_2.png);");
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/hen_3_2.png);");
    }
}


int b_3{0} ;

void bazi3nafare_game::place_Egg()
{
    if(b_3 == 11)
    {
    ui->combobox_11->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 12)
    {
    ui->combobox_12->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 13)
    {
    ui->combobox_13->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 14)
    {
    ui->combobox_14->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 15)
    {
    ui->combobox_15->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 16)
    {
    ui->combobox_16->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 17)
    {
    ui->combobox_17->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 21)
    {
    ui->combobox_21->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 22)
    {
    ui->combobox_22->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 23)
    {
    ui->combobox_23->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 24)
    {
    ui->combobox_24->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 25)
    {
    ui->combobox_25->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 26)
    {
    ui->combobox_26->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 27)
    {
    ui->combobox_27->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 31)
    {
    ui->combobox_31->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 32)
    {
    ui->combobox_32->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 33)
    {
    ui->combobox_33->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 34)
    {
    ui->combobox_34->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 35)
    {
    ui->combobox_35->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 36)
    {
    ui->combobox_36->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 37)
    {
    ui->combobox_37->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 41)
    {
    ui->combobox_41->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 42)
    {
    ui->combobox_42->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 43)
    {
    ui->combobox_43->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 44)
    {
    ui->combobox_44->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 45)
    {
    ui->combobox_45->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 46)
    {
    ui->combobox_46->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    else if(b_3 == 47)
    {
    ui->combobox_47->setStyleSheet("image: url(:/Egg_3(1).png);") ;
    }

    timer_takhir.start(20000) ;
    Egg_3++ ;
}


void bazi3nafare_game::place_cow(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/cow_3(1).png);");
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/cow_3(1).png);");
    }
}

int c_3{0} ;
int c_sheep_3{0} ;

void bazi3nafare_game::place_milk()
{
    if(c_3 == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/milk.png);") ;
    }

    else if(c_3 == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/milk.png);") ;
    }

    if(c_sheep_3 == 1)
    {
        timer_takhir.start(12000) ;
        c_sheep_3 -- ;
        milk_sheep_3++ ;
    }

    else
    {
        timer_takhir.start(15000) ;
        milk_cow_3++ ;
    }

}

void bazi3nafare_game::place_sheep(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/sheep_3.png);") ;
    }

    milk_sheep_3++ ;
}

int d_3{0} ;
int d_wheat_3{0} ;

void bazi3nafare_game::place_wheat_product()
{
    if(d_3 == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    else if(d_3 == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/wheat_3-sack.png);") ;
    }

    if(d_wheat_3 == 1)
    {
        timer_takhir.start(36000) ;
        d_wheat_3-- ;
        wheat_product_3++ ;
    }

    else
    {
        timer_takhir.start(20000) ;
        barley_product_3++ ;
    }
}

void bazi3nafare_game::place_wheat_plant(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

    else if(a == 47)
    {
        ui->combobox_47->setStyleSheet("image: url(:/wheat_3-plant.png);") ;
    }

}


void bazi3nafare_game::place_barley(int a)
{
    if(a == 11)
    {
        ui->combobox_11->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 12)
    {
        ui->combobox_12->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 13)
    {
        ui->combobox_13->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 14)
    {
        ui->combobox_14->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 15)
    {
        ui->combobox_15->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 16)
    {
        ui->combobox_16->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 17)
    {
        ui->combobox_17->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 21)
    {
        ui->combobox_21->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 22)
    {
        ui->combobox_22->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 23)
    {
        ui->combobox_23->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 24)
    {
        ui->combobox_24->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 25)
    {
        ui->combobox_25->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 26)
    {
        ui->combobox_26->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 27)
    {
        ui->combobox_27->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 31)
    {
        ui->combobox_31->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 32)
    {
        ui->combobox_32->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 33)
    {
        ui->combobox_33->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 34)
    {
        ui->combobox_34->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 35)
    {
        ui->combobox_35->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 36)
    {
        ui->combobox_36->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 37)
    {
        ui->combobox_37->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 41)
    {
        ui->combobox_41->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 42)
    {
        ui->combobox_42->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 43)
    {
        ui->combobox_43->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 44)
    {
        ui->combobox_44->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 45)
    {
        ui->combobox_45->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 46)
    {
        ui->combobox_46->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }

    else if(a == 47)
    {
        ui->combobox_46->setStyleSheet("image: url(:/barley_3(2).png);") ;
    }
}

void bazi3nafare_game::on_combobox_12_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_12->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 12 ;

            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_12->setCurrentText("") ;

            d_3 = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_12->setCurrentText("") ;

            b_3 = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(12) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_12->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(12) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_12->setCurrentText("") ;

            c_3 = 12 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(12) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }


        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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


void bazi3nafare_game::on_combobox_13_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_13->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_13->setCurrentText("") ;

            d_3 = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_13->setCurrentText("") ;

            b_3 = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_13->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(13) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_13->setCurrentText("") ;

            c_3 = 13 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(13) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_13->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_13->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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


void bazi3nafare_game::on_combobox_14_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_14->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_14->setCurrentText("") ;

            d_3 = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_14->setCurrentText("") ;

            b_3 = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(14) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_14->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(14) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_14->setCurrentText("") ;

            c_3 = 14 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(14) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_14->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_14->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_15_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_15->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_15->setCurrentText("") ;

            d_3 = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_15->setCurrentText("") ;

            b_3 = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(15) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_15->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(15) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_15->setCurrentText("") ;

            c_3 = 15 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(15) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_15->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_15->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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


void bazi3nafare_game::on_combobox_16_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_16->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_16->setCurrentText("") ;

            d_3 = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_16->setCurrentText("") ;

            b_3 = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(16) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_16->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(16) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_16->setCurrentText("") ;

            c_3 = 16 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(16) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_16->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_16->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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


void bazi3nafare_game::on_combobox_17_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_17->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_17->setCurrentText("") ;

            d_3 =  17 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_17->setCurrentText("") ;

            b_3 = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(17) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_17->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(17) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_17->setCurrentText("") ;

            c_3 = 17 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(17) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_17->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_17->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_11_activated(int index)
{
    switch(index)
    {
    case 1 :
    {
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_11->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_11->setCurrentText("") ;

            d_3 = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_11->setCurrentText("") ;

            b_3 = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(11) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_11->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(11) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_11->setCurrentText("") ;

            c_3 = 11 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(11) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_11->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_11->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_21_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_21->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_21->setCurrentText("") ;

            d_3 = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_21->setCurrentText("") ;

            b_3 = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3(21)));

            place_hen(21) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_21->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(21) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_21->setCurrentText("") ;

            c_3 = 21 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(21) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_21->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_21->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_22_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_22->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_22->setCurrentText("") ;

            d_3 = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_22->setCurrentText("") ;

            b_3 = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(22) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_22->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(22) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_22->setCurrentText("") ;

            c_3 = 22 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(22) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5 ;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_22->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_22->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_23_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_23->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_23->setCurrentText("") ;

            d_3 = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_23->setCurrentText("") ;

            b_3 = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(23) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_23->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(23) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_23->setCurrentText("") ;

            c_3 = 23 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(23) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_23->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_23->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_24_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_24->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_24->setCurrentText("") ;

            d_3 = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_24->setCurrentText("") ;

            b_3 = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(24) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_24->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(24) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_24->setCurrentText("") ;

            c_3 = 24 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(24) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_24->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_24->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_25_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_25->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_25->setCurrentText("") ;

            d_3 = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_25->setCurrentText("") ;

            b_3 = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(25) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_25->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(25) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_25->setCurrentText("") ;

            c_3 = 25 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(25) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_25->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_25->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_26_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_26->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_26->setCurrentText("") ;

            d_3 = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_26->setCurrentText("") ;

            b_3 = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(26) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_26->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(26) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_26->setCurrentText("") ;

            c_3 = 26 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(26) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_12->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_12->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_26->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_26->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_27_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_27->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_27->setCurrentText("") ;

            d_3 = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_27->setCurrentText("") ;

            b_3 = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(27) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_27->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(27) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_27->setCurrentText("") ;

            c_3 = 27 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(27) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_27->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_27->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_31_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_31->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_31->setCurrentText("") ;

            d_3 = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_31->setCurrentText("") ;

            b_3 = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(31) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_31->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(31) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_31->setCurrentText("") ;

            c_3 = 31 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(31) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_31->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_31->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_32_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_32->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_32->setCurrentText("") ;

            d_3 = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_32->setCurrentText("") ;

            b_3 = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(32) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_32->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(32) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_32->setCurrentText("") ;

            c_3 = 32 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(32) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_32->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_32->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_33_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_33->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_33->setCurrentText("") ;

            d_3 = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_33->setCurrentText("") ;

            b_3 = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(33) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_33->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(33) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_33->setCurrentText("") ;

            c_3 = 33 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(33) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;


                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_33->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_33->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_34_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_34->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_34->setCurrentText("") ;

            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_34->setCurrentText("") ;

            b_3 = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(34) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_34->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(34) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_34->setCurrentText("") ;

            c_3 = 34 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(34) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_34->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_34->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_35_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_35->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_35->setCurrentText("") ;

            d_3 = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_35->setCurrentText("") ;

            b_3 = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(35) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_35->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(35) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_35->setCurrentText("") ;

            c_3 = 35 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(35) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_35->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_35->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_36_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_36->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_36->setCurrentText("") ;

            d_3 = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_36->setCurrentText("") ;

            b_3 = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(36) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_36->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(36) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_36->setCurrentText("") ;

            c_3 = 36 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(36) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_36->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_36->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_37_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_37->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_37->setCurrentText("") ;

            d_3 = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_37->setCurrentText("") ;

            b_3 = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(37) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_37->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(37) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_37->setCurrentText("") ;

            c_3 = 37 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(37) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_37->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_37->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_41_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_41->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_41->setCurrentText("") ;

            d_3 = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_41->setCurrentText("") ;

            b_3 = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(41) ;

            free_hen_3 -- ;
            break;
            }

            else
            {
                QMessageBox::information(this , "خطا" , "کارگر ازاد ندارید") ;
                ui->combobox_41->setCurrentText("") ;
                break;
            }
        }

        else if(barley_product_3 >= 0)
        {
            coin_3 += 3;
            update_coin() ;

            ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
            ui->combobox_41->setCurrentText("") ;

            barley_product_3-- ;
            free_worker_3++ ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_41->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(41) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_41->setCurrentText("") ;

            c_3 = 41 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(41) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_41->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_41->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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


void bazi3nafare_game::on_combobox_42_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_42->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_42->setCurrentText("") ;

            d_3 = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_42->setCurrentText("") ;

            b_3 = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(42) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_42->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(42) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_42->setCurrentText("") ;

            c_3 = 42 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(42) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_42->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_42->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_43_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_43->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_43->setCurrentText("") ;

            d_3 = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_43->setCurrentText("") ;

            b_3 = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(43) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_43->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(43) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_43->setCurrentText("") ;

            c_3 = 43 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(43) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_43->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_43->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_44_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_44->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_44->setCurrentText("") ;

            d_3 = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_44->setCurrentText("") ;

            b_3 = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3(44)));

            place_hen(44) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_44->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(44) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_44->setCurrentText("") ;

            c_3 = 44 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(44) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_44->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_44->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_45_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_45->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_45->setCurrentText("") ;

            d_3 = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_45->setCurrentText("") ;

            b_3 = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3(45)));

            place_hen(45) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_45->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(45) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_45->setCurrentText("") ;

            c_3 = 45 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(45) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_45->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_45->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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


void bazi3nafare_game::on_combobox_46_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_46->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_46->setCurrentText("") ;

            d_3 = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_46->setCurrentText("") ;

            b_3 = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(46) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_46->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 46 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(46) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_46->setCurrentText("") ;

            c_3 = 46 ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_46->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_46->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_combobox_47_activated(int index)
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
        if(buy_land_3 >= 1)
        {
            ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;");

            buy_land_3 -- ;
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
        if(wheat_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_47->setCurrentText("") ;

            d_wheat_3 ++ ;
            d_3 = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(barley_3 >= 1)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_47->setCurrentText("") ;

            d_3 = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_wheat_product_3()));

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
        if(hen_3 - free_hen_3 >= 0 && hen_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_47->setCurrentText("") ;

            b_3 = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_Egg_3()));

            place_hen(47) ;

            free_hen_3 -- ;
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
        if(sheep_3 - free_sheep_3 >= 0 && sheep_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_47->setCurrentText("") ;

            c_sheep_3++ ;
            c_3 = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_sheep(47) ;

            free_sheep_3 -- ;
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
        if(cow_3 - free_cow_3 >= 0 && cow_3 != 0)
        {
            if(free_worker_3 != 0)
            {
            free_worker_3 -- ;
            ui->combobox_47->setCurrentText("") ;

            c_3 = 47 ;
            QTimer::singleShot(10000, this, SLOT(place_milk()));

            place_cow(47) ;

            free_cow_3 -- ;
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
        if(Egg_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 5000)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 10000 )
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 15000 )
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                Egg_3-- ;
                free_hen_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_cow_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 3000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 6000 && timer_takhir.remainingTime() > 3000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 9000 && timer_takhir.remainingTime() > 6000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 9000)
            {
                coin_3 += 4;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 15000 && timer_takhir.remainingTime() > 12000)
            {
                coin_3 += 5;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_cow_3-- ;
                free_cow_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(milk_sheep_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 4000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 8000 && timer_takhir.remainingTime() > 4000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else if (timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 8000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                milk_sheep_3-- ;
                free_sheep_3 ++ ;
                free_worker_3++ ;
            }
        }

        else if(wheat_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 12000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 24000 && timer_takhir.remainingTime() > 12000)

            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 36000 && timer_takhir.remainingTime() > 24000)
            {
                coin_3 += 3;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                wheat_product_3-- ;
                free_worker_3++ ;
            }

        }

        else if(barley_product_3 >= 1)
        {
            if(timer_takhir.remainingTime() <= 10000 && timer_takhir.remainingTime() > 0)
            {
                coin_3 += 1;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else if(timer_takhir.remainingTime() <= 20000 && timer_takhir.remainingTime() > 10000)
            {
                coin_3 += 2;
                update_coin() ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
            }

            else
            {
                QMessageBox::information(this , "فروشنده"  ,  "به علت فاسد شدن محصول 0 سکه واگذار شد") ;

                ui->combobox_47->setStyleSheet("background-color : #2ecc71 ;") ;
                ui->combobox_47->setCurrentText("") ;

                barley_product_3-- ;
                free_worker_3++ ;
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

void bazi3nafare_game::on_comboBox_kill_activated(int index)
{
    switch(index)
    {

    case 0 :
    {
        if(free_hen_3 >= 1)
        {
            coin_3 += 3 ;
            update_coin() ;
            ui->comboBox_kill->setCurrentText("") ;
            hen_3 -- ;
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
        if(free_sheep_3 >= 1)
        {
            coin_3 += 4 ;
            update_coin() ;
            ui->comboBox_kill->setCurrentText("") ;
            sheep_3 -- ;
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
        if(free_cow_3 >= 1)
        {
            coin_3 += 6 ;
            update_coin() ;
            ui->comboBox_kill->setCurrentText("") ;
            cow_3 -- ;
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

