#ifndef BAZI3NAFARE_H
#define BAZI3NAFARE_H

#include <QDialog>

namespace Ui {
class bazi3nafare;
}

class bazi3nafare : public QDialog
{
    Q_OBJECT

public:
    explicit bazi3nafare(QWidget *parent = nullptr);
    ~bazi3nafare();

public slots:
    void on_comboBox_Lang_3_activated(int index) ;

    void on_pushButton_Eye_3_clicked() ;

    void on_pushButton_generate_kapcha_clicked() ;

    void on_pushButton_eyeline_3_clicked() ;

private slots:
    QString generateRandomString(int length) ;

    void show_3() ;

    bool isValidPassword(const QString &password , int &y) ;

    bool isValidEmail(QString email , int &x) ;

    bool isCaptchaValid(QString userCaptcha);

    void on_pushButton_Enroll_3_clicked();

private:
    Ui::bazi3nafare *ui;
    QString generatekapcha ;
};

#endif // BAZI3NAFARE_H
