#include "firstpage.h"
#include "ui_firstpage.h"
#include "QMessageBox"

#include "bazi2nafare.h"
#include "bazi3nafare.h"
#include "bazi4nafare.h"

FirstPage::FirstPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FirstPage)
{
    ui->setupUi(this);

    ui->comboBox_number_player->addItem("   دو نفره");
    ui->comboBox_number_player->addItem("   سه نفره");
    ui->comboBox_number_player->addItem("   چهارنفره");

    ui->comboBox_theme->addItem("  default") ;
    ui->comboBox_theme->addItem("  theme1") ;
    ui->comboBox_theme->addItem("  theme2") ;
    ui->comboBox_theme->addItem("  theme3") ;

    setMaximumSize(800,520) ;
    setMinimumSize(800,520) ;

}

FirstPage::~FirstPage()
{
    delete ui;
}

//style of theme

void FirstPage::on_comboBox_theme_activated(int index)
{
    switch(index)
    {
    case 0 :
    {
        ui->GB_FirstPage->setStyleSheet("background-color : white ; border : 2px solid #3d3d3d ;") ;
        break ;
    }

    case 1 :
    {
        ui->GB_FirstPage->setStyleSheet("background-color : #BDC581 ; border : 2px solid #3d3d3d ;") ;
        break ;
    }

    case 2 :
    {
        ui->GB_FirstPage->setStyleSheet("background-color : #4a69bd ; border : 2px solid #3d3d3d ;") ;
        break ;
    }

    case 3 :
    {
        ui->GB_FirstPage->setStyleSheet("background-color : #82589F ; border : 2px solid #3d3d3d ;") ;
        break ;
    }

    }
}

void FirstPage::on_comboBox_number_player_activated(int index)
{
    switch(index)
    {

    case 0 : //bazi2nafare
    {
        QMessageBox::information(this , "اطلاعیه بازی دو نفره","شرکت کنندگان ابتدا باید فرم ثبت نام را پر کنند","فهمیدم");
        this->hide() ;
        bazi2nafare *w2 = new bazi2nafare ;
        w2->show() ;
        break ;
    }

    case 1 : //bazi3nafare
    {
        QMessageBox::information(this , "اطلاعیه بازی سه نفره","شرکت کنندگان به ترتیب باید در بازی ثبت نام کنند","فهمیدم");
        this->hide() ;
        bazi3nafare *w2 = new bazi3nafare ;
        w2->show() ;
        break ;
    }

    case 2 : //bazi4nafare
    {
        QMessageBox::information(this , "اطلاعیه بازی چهار نفره","شرکت کنندگان به ترتیب باید در بازی ثبت نام کنند","فهمیدم");
        this->hide() ;
        bazi4nafare *w2 = new bazi4nafare ;
        w2->show() ;
        break ;
    }

    }
}
