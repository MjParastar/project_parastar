#ifndef BAZI2NAFARE_H
#define BAZI2NAFARE_H

#include <QDialog>

namespace Ui
{
class bazi2nafare;
}

class bazi2nafare : public QDialog
{
    Q_OBJECT

public:
    explicit bazi2nafare(QWidget *parent = nullptr);
    ~bazi2nafare();

public slots:

    void on_comboBox_Lang_activated(int index) ;

    void on_pushButton_Eye_2_clicked() ;

    void on_pushButton_generate_kapcha_clicked() ;

    void on_pushButton_Enroll_clicked() ;

    void on_pushButton_eyeline_2_clicked() ;

private slots:
    QString generateRandomString(int length) ;

    bool isValidPassword(const QString &password , int &y);

    bool isValidEmail(QString email , int &x);

    bool isCaptchaValid(QString userCaptcha);

    void show_2() ;


    private:
    Ui::bazi2nafare *ui;
    QString generatekapcha ;
};

#endif // BAZI2NAFARE_H

