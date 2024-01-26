#ifndef BAZI3NAFARE_GAME_H
#define BAZI3NAFARE_GAME_H

#include <QMainWindow>
#include "QTime"
#include "QTimer"
#include <QtMultimedia>

namespace Ui {
class bazi3nafare_game;
}

class bazi3nafare_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit bazi3nafare_game(QWidget *parent = nullptr);
    ~bazi3nafare_game();

private slots :
    void updateCountdown();

    void on_pushbutton_balance_product_clicked();

    void on_comboBox_store_activated(int index);

    void update_coin() ;

    void update_worker_num() ;

    void place_hen(int a) ;

    void place_Egg() ;

    void place_cow(int a) ;

    void place_milk() ;

    void place_sheep(int a) ;

    void place_wheat_product() ;

    void place_wheat_plant(int a) ;

    void place_barley(int a) ;

    void on_combobox_12_activated(int index);

    void on_combobox_13_activated(int index);

    void on_combobox_14_activated(int index);

    void on_combobox_15_activated(int index);

    void on_combobox_16_activated(int index);

    void on_combobox_17_activated(int index);

    void on_combobox_11_activated(int index);

    void on_combobox_21_activated(int index) ;

    void on_combobox_22_activated(int index) ;

    void on_combobox_23_activated(int index) ;

    void on_combobox_24_activated(int index) ;

    void on_combobox_25_activated(int index) ;

    void on_combobox_26_activated(int index) ;

    void on_combobox_27_activated(int index) ;

    void on_combobox_31_activated(int index) ;

    void on_combobox_32_activated(int index) ;

    void on_combobox_33_activated(int index) ;

    void on_combobox_34_activated(int index) ;

    void on_combobox_35_activated(int index) ;

    void on_combobox_36_activated(int index) ;

    void on_combobox_37_activated(int index) ;

    void on_combobox_41_activated(int index) ;

    void on_combobox_42_activated(int index) ;

    void on_combobox_43_activated(int index) ;

    void on_combobox_44_activated(int index) ;

    void on_combobox_45_activated(int index) ;

    void on_combobox_46_activated(int index) ;

    void on_combobox_47_activated(int index) ;

    void on_comboBox_kill_activated(int index);

    void savecoin_database() ;

    void update_data() ;

private:
    Ui::bazi3nafare_game *ui;

    QTimer *timer;
    QTime countdownTime;

    QTimer timer_takhir ;
};

#endif // BAZI3NAFARE_GAME_H
