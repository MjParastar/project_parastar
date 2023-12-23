#ifndef BAZI4NAFARE_H
#define BAZI4NAFARE_H

#include <QMainWindow>

namespace Ui {
class bazi4nafare;
}

class bazi4nafare : public QMainWindow
{
    Q_OBJECT

public:
    explicit bazi4nafare(QWidget *parent = nullptr);
    ~bazi4nafare();

public slots:
    void on_comboBox_Lang_4_activated(int index) ;

    void on_pushButton_eye_4_clicked() ;

    void on_pushButton_eyeline_4_clicked() ;

    void on_pushButton_generate_kapcha_clicked() ;

private slots:
    QString generateRandomString(int length) ;

    void show_4() ;

    bool isValidPassword(const QString &password , int &y) ;

    bool isValidEmail(QString email , int &x) ;

    bool isCaptchaValid(QString userCaptcha);

    void on_pushButton_Enroll_4_clicked();


private:
    Ui::bazi4nafare *ui;
    QString generatekapcha ;
};

#endif // BAZI4NAFARE_H
