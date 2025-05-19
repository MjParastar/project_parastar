#include "bazi2nafare.h"
#include "ui_bazi2nafare.h"

#include "bazi2nafare_game.h"

#include "QPainter"
#include "QMessageBox"
#include <QRegExp>
#include "QString"
#include <string>
#include <QMessageBox>

#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"


using namespace std ;

bazi2nafare::bazi2nafare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bazi2nafare)
{
    ui->setupUi(this);

    //relate to database
    QSqlDatabase database ;
    database = QSqlDatabase::addDatabase("QSQLITE") ;
    database.setDatabaseName("C:\\Personal\\AdvancedMabani\\ProjectQt\\Database\\Player.db") ;
    database.open() ;

    ui->comboBox_Lang->addItem("Persian") ;
    ui->comboBox_Lang->addItem("English") ;

    ui->comboBox_Phone->addItem("+98") ; //iran
    ui->comboBox_Phone->addItem("+1") ; //canada
    ui->comboBox_Phone->addItem("+92") ; //pakestan
    ui->comboBox_Phone->addItem("+58") ; //venezola
    ui->comboBox_Phone->addItem("+46") ; //soed
    ui->comboBox_Phone->addItem("+84") ; //vietnam
    ui->comboBox_Phone->addItem("+48") ; //lahestan
    ui->comboBox_Phone->addItem("+31") ; //holand

    ui->comboBox_Phone->setItemData(0, QIcon(":/iranflag.png"), Qt::DecorationRole);
    ui->comboBox_Phone->setItemData(1, QIcon(":/canadaflag.png"), Qt::DecorationRole);
    ui->comboBox_Phone->setItemData(2, QIcon(":/pakestanflag.png"), Qt::DecorationRole);
    ui->comboBox_Phone->setItemData(3, QIcon(":/venezolaflag.png"), Qt::DecorationRole);
    ui->comboBox_Phone->setItemData(4, QIcon(":/soedflag.png"), Qt::DecorationRole);
    ui->comboBox_Phone->setItemData(5, QIcon(":/vietnamflag.png"), Qt::DecorationRole);
    ui->comboBox_Phone->setItemData(6, QIcon(":/lahestanflag.png"), Qt::DecorationRole);
    ui->comboBox_Phone->setItemData(7, QIcon(":/holandflag.png"), Qt::DecorationRole);

    ui->lineEdit_Phonenum->setValidator(new QIntValidator) ;
    ui->lineEdit_Balance->setValidator(new QIntValidator) ;

    ui->pushButton_eyeline_2->hide() ;

    setMaximumSize(1020,640) ;
    setMinimumSize(1020,640) ;

    show_2();

}

bazi2nafare::~bazi2nafare()
{
    delete ui;
}


void bazi2nafare::on_comboBox_Lang_activated(int index)
{
    switch(index)
    {
    case 0 :
    {
        ui->comboBox_Phone->move(152,180);
        ui->pushButton_Eye_2->move(220 , 140) ;
        ui->pushButton_eyeline_2->move(220,140) ;

        ui->num_lab->setText("کاربر اول") ;
        ui->num_lab->setStyleSheet("border : none;"
                                   "font: 10pt \"B Sara\";");

        ui->pushButton_Enroll->setText("ثبت نام") ;

        ui->Enrol_lab->setText("ثبت نام");
        ui->Enrol_lab->move(480,10);
        ui->Enrol_lab->setStyleSheet("border-right : 5px double black ;"
                                     "border-left : none ;"
                                     "border-top : none ;"
                                     "border-bottom : 3px solid black ;"
                                     "font: 25pt \"B Arshia\";");

        ui->Username_lab->setText("نام کاربری :");
        ui->Username_lab->move(360 , 100) ;

        ui->Password_lab->setText("رمز عبور :");
        ui->Password_lab->move(340 , 140) ;

        ui->Phonenum_lab->setText("تلفن همراه :");
        ui->Phonenum_lab->move(350 , 180) ;

        ui->Email_lab->setText("ایمیل :");
        ui->Email_lab->move(370 , 220) ;

        ui->Balance_lab->setText("موجودی بانکی :");
        ui->Balance_lab->move(370 , 260) ;

        ui->Kapcha_lab->setText("کپچا :");
        ui->Kapcha_lab->move(360 , 300) ;

        break ;
    }

    case 1 :
    {
        ui->comboBox_Phone->move(360 , 180);
        ui->pushButton_Eye_2->move(360 , 140) ;
        ui->pushButton_eyeline_2->move(360 , 140) ;

        ui->num_lab->setText("User 1") ;
        ui->num_lab->setStyleSheet("border : none;"
                                    "font: 15pt \"Candara\";");

        ui->pushButton_Enroll->setText("Enroll") ;

        ui->Enrol_lab->setText("   Enroll");
        ui->Enrol_lab->move(20,20);
        ui->Enrol_lab->setStyleSheet("border-left : 5px double black ;"
                "border-right : none ;"
                "border-top : none ;");

        ui->Enrol_lab->setStyleSheet("border-right : none ; border-left :5px double black ; border-bottom : 3px solid black ; font: 15pt\"Candara\";") ;

        ui->Username_lab->setText("Username :");
        ui->Username_lab->move(160 , 100) ;

        ui->Password_lab->setText("Password :");

        ui->Password_lab->move(160 , 140) ;

        ui->Phonenum_lab->setText("Phone :");
        ui->Phonenum_lab->move(160 , 180) ;

        ui->Email_lab->setText("Email :");
        ui->Email_lab->move(160 , 220) ;

        ui->Balance_lab->setText("Balance :");
        ui->Balance_lab->move(160 , 260) ;

        ui->Kapcha_lab->setText("Kapcha :");
        ui->Kapcha_lab->move(160 , 300) ;

        break ;

    }
    }
}


void bazi2nafare::on_pushButton_Eye_2_clicked()
{
    if(ui->lineEdit_Password->echoMode() == QLineEdit::Password)
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
    }

    else
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    }

    ui->pushButton_Eye_2->hide() ;
    ui->pushButton_eyeline_2->show() ;
}

void bazi2nafare::on_pushButton_eyeline_2_clicked()
{
    if(ui->lineEdit_Password->echoMode() == QLineEdit::Password)
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
    }

    else
    {
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    }

    ui->pushButton_eyeline_2->hide() ;
    ui->pushButton_Eye_2->show() ;
}



QString bazi2nafare::generateRandomString(int length)
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    QString randomString;
    for(int i=0; i<length; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }

    return randomString;
}


void bazi2nafare::on_pushButton_generate_kapcha_clicked()
{
    QPixmap pixmap(110, 50);

    pixmap.fill(Qt::gray);

    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 15, QFont::Bold));

    QString captcha = generateRandomString(5);

    generatekapcha = captcha ;

    painter.drawText(pixmap.rect(), Qt::AlignCenter, captcha);

    ui->kapcha_show->setPixmap(pixmap);
}


void bazi2nafare::show_2()
{
    QWidget::show();

    bazi2nafare::on_pushButton_generate_kapcha_clicked() ;
}

bool bazi2nafare::isValidPassword(const QString &password , int &y)
{
    if (password.isEmpty())
    {
        y++ ;
        return false;
    }

    for (QChar c : password)
    {
        if (!c.isLetterOrNumber())
        {
            y-- ;
            return false;
        }
    }
    return true;
}

bool bazi2nafare::isValidEmail(QString email , int &x)
{
    QRegExp emailRegex ("^[a-zA-Z0-9_.]+@(gmail\\.com|email\\.com|mail\\.um\\.ac)$");
    bool suffixemail = emailRegex.exactMatch(email);

    if(suffixemail == false)
    {
        x++ ;
    }

    QRegExp illegalCharactersRegex("[-+/\\\\$*#^%()]");
    bool hasIllegalCharacters = illegalCharactersRegex.indexIn(email) != -1;

    if(hasIllegalCharacters)
    {
        x-- ;
    }

    return suffixemail && !hasIllegalCharacters;
}

bool bazi2nafare::isCaptchaValid(QString userCaptcha)
{
    if (userCaptcha.length() != generatekapcha.length())
    {
        return false;
    }

    for (int i = 0; i < generatekapcha.length(); i++)
    {
        if (generatekapcha[i] != userCaptcha[i])
        {
            return false;
        }
    }


    return true;
}


int step{1} ;

void bazi2nafare::on_pushButton_Enroll_clicked()
{
    int checkarray[6] ;
    for(int i = 0 ; i < 6 ; i++)
    {
        checkarray[i] = 0 ;
    }

    string arraybox[6][2] ;
    arraybox[0][0] = "وارد کردن نام کاربری الزامی است" ;

    arraybox[1][0] = "وارد کردن رمز عبور الزامی است" ;
    arraybox[1][1] = "رمز عبور فقط میتواند شامل حروف و اعداد باشد " ;

    arraybox[2][0] = "تلفن همراه نامتعبر است" ;

    arraybox[3][0] = "ایمیل نباید شامل کاراکتر های ) ( * + - ^ % $ # / \\ و یا خالی باشد" ;
    arraybox[3][1] = "ایمیل فقط میتواند به فرمت های روبرو باشد @gmail.com , @email.com , @mail.um.ac" ;

    arraybox[4][0] = "موجودی نمیتواند صفر یا خالی باشد" ;

    arraybox[5][0] = "کپچا نامتعبر است ";

    //checking username

    QString username = ui->lineEdit_Username->text();

    int U{0} ; // U = username
    if(username.length() == 0)
    {
        U++ ;
    }

    //checking password

    QString password = ui->lineEdit_Password->text();

    bool P = false ; // P = password
    int y{0} ;
    P = isValidPassword(password , y) ;

    //checking phone number

    QMap<QString, int> countryToDigits;

    countryToDigits["+98"] = 10; //iran
    countryToDigits["+1"] = 10; //canada
    countryToDigits["+92"] = 10; //pakestan
    countryToDigits["+58"] = 7; //venezola
    countryToDigits["+46"] = 7; //soed
    countryToDigits["+84"] = 9; //vietnam
    countryToDigits["+48"] = 9; //lahestan
    countryToDigits["+31"] = 9; //holand

    QString country = ui->comboBox_Phone->currentText();
    int digits = countryToDigits[country];

    int N{0} ; // N = number

    if(ui->lineEdit_Phonenum->text().length() < digits)
    {
       N++ ;
    }

    if(ui->lineEdit_Phonenum->text().length() > digits)
    {
       N-- ;
    }


    //cheking email

    QString email = ui->lineEdit_Email->text() ;

    int x{0} ;
    bool Em = isValidEmail(email , x) ;

    int E{0} ; //E = email
    if(Em == false)
    {
        E++ ;
    }

    //cheking balance

    QString balance = ui->lineEdit_Balance->text() ;

    int a = balance.toInt() ;

    int conclusion{0} ;
    if(a == 0 || balance.isEmpty())
    {
        conclusion++ ;
    }



    //cheking kapcha

    QString userkapcha = ui->lineEdit_Kapcha->text() ;

    bool kapcha = isCaptchaValid(userkapcha) ;

    int k{0} ;
    if(kapcha == false)
    {
        k++ ;
    }

    //output

    if(U == 1)
    {
       checkarray[0]++ ;
    }

    if(P == false)
    {
       checkarray[1]++ ;
    }

    if(N == 1 || N == -1)
    {
       checkarray[2]++ ;
    }

    if(E == 1)
    {
       checkarray[3]++ ;
    }

    if(conclusion == 1)
    {
       checkarray[4]++ ;
    }

    if(k == 1)
    {
       checkarray[5]++ ;
    }


    int sum{0} ;
    for(int i = 0 ; i < 6 ; i++)
    {
        sum += checkarray[i] ;
    }


    switch(sum)
    {
        case 0 :
        {
        if(step == 1)
        {
            QMessageBox::information(this, "successful","ثبت نام کاربر اول با موفقیت انجام شد");

            QSqlQuery q ;
            QString a1 , a2 , a3 , a4 , a5 ;

            a1 = ui->lineEdit_Username->text() ;
            a2 = ui->lineEdit_Password->text() ;
            a3 = ui->lineEdit_Phonenum->text() ;
            a4 = ui->lineEdit_Email->text() ;
            a5 = ui->lineEdit_Balance->text() ;

            q.exec("INSERT INTO Player(`Username` , `Password` , `Phone number` , `Email` , `Balance`) values('"+a1+"','"+a2+"','"+a3+"','"+a4+"','"+a5+"')");


            ui->lineEdit_Username->clear() ;
            ui->lineEdit_Password->clear() ;
            ui->lineEdit_Phonenum->clear() ;
            ui->lineEdit_Email->clear() ;
            ui->lineEdit_Balance->clear() ;
            ui->lineEdit_Kapcha->clear() ;

            ui->num_lab->setText("کاربر دوم") ;

            show_2();
        }

        if(step == 2)
        {
            QSqlQuery q ;
            QString a1 , a2 , a3 , a4 , a5 ;

            a1 = ui->lineEdit_Username->text() ;
            a2 = ui->lineEdit_Password->text() ;
            a3 = ui->lineEdit_Phonenum->text() ;
            a4 = ui->lineEdit_Email->text() ;
            a5 = ui->lineEdit_Balance->text() ;

            q.exec("INSERT INTO Player(`Username` , `Password` , `Phone number` , `Email` , `Balance`) values('"+a1+"','"+a2+"','"+a3+"','"+a4+"','"+a5+"')");

            QMessageBox::information(this, "successful", "ثبت نام کاربر دوم با موفقیت انجام شد" , "شروع بازی") ;

            this->hide() ;
            bazi2nafare_game *w2 = new bazi2nafare_game ;
            w2->show() ;
        }

            step++ ;


            break ;
        }

        case 1 :
        {
            for(int i = 0 ; i < 6 ; i++)
            {
                if(checkarray[i] == 1)
                {
                    if(i == 1)
                    {
                        if(y == 1)
                        {
                            QMessageBox message ;
                            message.setText(QString::fromStdString(arraybox[1][0])) ;
                            message.exec() ;
                            break ;
                        }

                        else
                        {
                            QMessageBox message ;
                            message.setText(QString::fromStdString(arraybox[1][1])) ;
                            message.exec() ;
                            break ;
                        }
                    }

                    else if(i == 3)
                    {
                        if(x == 1)
                        {
                            QMessageBox message ;
                            message.setText(QString::fromStdString(arraybox[3][0])) ;
                            message.exec() ;
                            break ;
                        }

                        else
                        {
                            QMessageBox message ;
                            message.setText(QString::fromStdString(arraybox[3][1])) ;
                            message.exec() ;
                            break ;
                        }
                    }

                    else
                    {
                    QMessageBox message ;
                    message.setText(QString::fromStdString(arraybox[i][0])) ;
                    message.exec() ;
                    break ;
                    }

                }
            }
            break ;
        }

    case 2: {
        for (int i = 0; i < 6; i++) {
            if (checkarray[i] == 1) {
                if (i == 1) {
                    if (y == 1) {
                        for (int j = 0; j < 6; j++) {
                            if (checkarray[j] == 1) {
                                if (j == 3) {
                                    if (x == 1) {
                                        QMessageBox message;
                                        message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[3][0]));
                                        message.exec();
                                        break;
                                    } else {
                                        QMessageBox message;
                                        message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[3][1]));
                                        message.exec();
                                        break;
                                    }
                                } else {
                                    QMessageBox message;
                                    message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[j][0]));
                                    message.exec();
                                    break;
                                }
                            }
                            break;
                        }
                        break;
                    } else {
                        for (int j = 0; j < 6; j++) {
                            if (checkarray[j] == 1) {
                                if (j == 3) {
                                    if (x == 1) {
                                        QMessageBox message;
                                        message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[3][0]));
                                        message.exec();
                                        break;
                                    } else {
                                        QMessageBox message;
                                        message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[3][1]));
                                        message.exec();
                                        break;
                                    }
                                } else {
                                    QMessageBox message;
                                    message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[j][0]));
                                    message.exec();
                                    break;
                                }
                            }
                            break;
                        }
                        break;
                    }
                } else if (i == 3) {
                    if (x == 1) {
                        for (int j = i + 1; j < 6; j++) {
                            if (checkarray[j] == 1) {
                                QMessageBox message;
                                message.setText(QString::fromStdString(arraybox[3][0] + "\n" + arraybox[j][0]));
                                message.exec();
                                break;
                            }
                        }
                    } else {
                        for (int j = i + 1; j < 6; j++) {
                            if (checkarray[j] == 1) {
                                QMessageBox message;
                                message.setText(QString::fromStdString(arraybox[3][1] + "\n" + arraybox[j][0]));
                                message.exec();
                                break;
                            }
                        }
                    }
                } else {
                    for (int j = i + 1; j < 6; j++) {
                        if (checkarray[j] == 1) {
                            QMessageBox message;
                            message.setText(QString::fromStdString(arraybox[i][0] + "\n" + arraybox[j][0]));
                            message.exec();
                            break;
                        }
                    }
                }
            }
            break;
        }
    }


        case 3 :
        {
            for(int i = 0 ; i < 6 ; i++)
            {
                if(checkarray[i] == 1)
                {
                    if(i == 1)
                    {
                        if(y == 1)
                        {
                        for(int j = i+1 ; j < 6 ; j++)
                        {
                            if(checkarray[j] == 1)
                            {
                                if(j == 3)
                                {
                                    if(x == 1)
                                    {
                                    for(int k = j+1 ; k < 6 ; k++)
                                    {
                                        if(checkarray[k] == 1)
                                        {
                                            QMessageBox message ;
                                            message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0])) ;
                                            message.exec() ;
                                            break ;
                                        }
                                    }
                                    }

                                    else
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                QMessageBox message ;
                                                message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[3][1] + "\n" + arraybox[k][0])) ;
                                                message.exec() ;
                                                break ;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    for(int k = j+1 ; k < 6 ; k++)
                                    {
                                        if(checkarray[k] == 1)
                                        {
                                            if(k == 3)
                                            {
                                                if(x == 1)
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[j][0] + "\n" + arraybox[3][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                                else
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[j][0] + "\n" + arraybox[3][1])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                            else
                                            {
                                                QMessageBox message ;
                                                message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0])) ;
                                                message.exec() ;
                                                break ;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        }
                        else
                        {
                            for(int j = i+1 ; j < 6 ; j++)
                            {
                                if(checkarray[j] == 1)
                                {
                                    if(j == 3)
                                    {
                                        if(x == 1)
                                        {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                QMessageBox message ;
                                                message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0])) ;
                                                message.exec() ;
                                                break ;
                                            }
                                        }
                                        }

                                        else
                                        {
                                            for(int k = j+1 ; k < 6 ; k++)
                                            {
                                                if(checkarray[k] == 1)
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[3][1] + "\n" + arraybox[k][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                if(k == 3)
                                                {
                                                    if(x == 1)
                                                    {
                                                        QMessageBox message ;
                                                        message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[j][0] + "\n" + arraybox[3][0])) ;
                                                        message.exec() ;
                                                        break ;
                                                    }
                                                    else
                                                    {
                                                        QMessageBox message ;
                                                        message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[j][0] + "\n" + arraybox[3][1])) ;
                                                        message.exec() ;
                                                        break ;
                                                    }
                                                }
                                                else
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if(i == 3)
                    {
                        if(x == 1)
                        {
                        for(int j = i+1 ; j < 6 ; j++)
                        {
                            if(checkarray[j] == 1)
                            {
                                    for(int k = j+1 ; k < 6 ; k++)
                                    {
                                        if(checkarray[k] == 1)
                                        {
                                            QMessageBox message ;
                                            message.setText(QString::fromStdString(arraybox[3][0] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0])) ;
                                            message.exec() ;
                                            break ;
                                        }
                                    }
                            }
                        }
                        }

                         else
                            {
                            for(int j = i+1 ; j < 6 ; j++)
                            {
                                if(checkarray[j] == 1)
                                {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                QMessageBox message ;
                                                message.setText(QString::fromStdString(arraybox[3][1] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0])) ;
                                                message.exec() ;
                                                break ;
                                            }
                                        }
                                }
                            }
                            }
                    }

                    else
                    {
                        if(i == 2)
                        {
                            for(int j = i+1 ; j < 6 ; j++)
                            {
                                if(checkarray[j] == 1)
                                {
                                    if(j == 3)
                                    {
                                        if(x == 1)
                                        {
                                            for(int k = j+1 ; k < 6 ; k++)
                                            {
                                                if(checkarray[k] == 1)
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[2][0] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            for(int k = j+1 ; k < 6 ; k++)
                                            {
                                                if(checkarray[k] == 1)
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[2][0] + "\n" + arraybox[3][1] + "\n" + arraybox[k][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                        }
                                    }

                                    else
                                    {
                                        for(int k = j + 1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                QMessageBox message ;
                                                message.setText(QString::fromStdString(arraybox[2][0] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0])) ;
                                                message.exec() ;
                                                break ;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else
                        {
                            for(int j = i+1 ; j < 6 ; j++)
                            {
                                if(checkarray[j] == 1)
                                {
                                    for(int k = j+1 ; k < 6 ; k++)
                                    {
                                        if(checkarray[k] == 1)
                                        {
                                            QMessageBox message ;
                                            message.setText(QString::fromStdString(arraybox[i][0] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0])) ;
                                            message.exec() ;
                                            break ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            }


        case 4 :
        {
                for(int i = 0 ; i < 6 ; i++)
                {
                    if(checkarray[i] == 1)
                    {
                    if(i == 1)
                    {
                        if(y == 1)
                        {
                        for(int j = i+1 ; j < 6 ; j++)
                        {
                            if(checkarray[j] == 1)
                            {
                                if(j == 3)
                                {
                                    if(x == 1)
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                for(int t = k + 1 ; t < 6 ; t++)
                                                {
                                                    if(checkarray[t] == 1)
                                                    {
                                                        QMessageBox message ;
                                                        message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                        message.exec() ;
                                                        break ;
                                                    }
                                                }
                                            }
                                            break ;
                                        }
                                    }

                                    else
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                for(int t = k + 1 ; t < 6 ; t++)
                                                {
                                                    if(checkarray[t] == 1)
                                                    {
                                                        QMessageBox message ;
                                                        message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                        message.exec() ;
                                                        break ;
                                                    }
                                                }
                                            }
                                            break ;
                                        }
                                    }
                                }

                                else if(j == 2)
                                {
                                    for(int k = j+1 ; k < 6 ; k++)
                                    {
                                        if(checkarray[k] == 1)
                                        {
                                            if(k == 3)
                                            {
                                                if(x == 1)
                                                {
                                                    for(int t = k+1 ; t < 6 ; t++)
                                                    {
                                                        if(checkarray[t] == 1)
                                                        {
                                                            QMessageBox message ;
                                                            message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[2][0] + "\n" + arraybox[3][0] + "\n" + arraybox[t][0])) ;
                                                            message.exec() ;
                                                            break ;
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    for(int t = k+1 ; t < 6 ; t++)
                                                    {
                                                        if(checkarray[t] == 1)
                                                        {
                                                            QMessageBox message ;
                                                            message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[2][0] + "\n" + arraybox[3][1] + "\n" + arraybox[t][0])) ;
                                                            message.exec() ;
                                                            break ;
                                                        }
                                                    }
                                                }
                                            }

                                            else
                                            {
                                                for(int t = k+1 ; t < 6 ; t++)
                                                {
                                                    if(checkarray[t] == 1)
                                                    {
                                                        QMessageBox message ;
                                                        message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[2][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                        message.exec() ;
                                                        break ;
                                                    }
                                                }
                                            }
                                        }
                                        break ;
                                    }
                                }

                                else
                                {
                                    for(int k = j+1 ; k < 6 ; k++)
                                    {
                                        if(checkarray[k] == 1)
                                        {
                                            for(int t = k+1 ; t < 6 ; t++)
                                            {
                                                if(checkarray[t] == 1)
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[1][0] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                        }
                                        break ;
                                    }
                                }
                            }
                            break ;
                        }
                        }

                        else
                        {
                            for(int j = i+1 ; j < 6 ; j++)
                            {
                                if(checkarray[j] == 1)
                                {
                                    if(j == 3)
                                    {
                                        if(x == 1)
                                        {
                                            for(int k = j+1 ; k < 6 ; k++)
                                            {
                                                if(checkarray[k] == 1)
                                                {
                                                    for(int t = k + 1 ; t < 6 ; t++)
                                                    {
                                                        if(checkarray[t] == 1)
                                                        {
                                                            QMessageBox message ;
                                                            message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                            message.exec() ;
                                                            break ;
                                                        }
                                                    }
                                                }
                                                break ;
                                            }
                                        }

                                        else
                                        {
                                            for(int k = j+1 ; k < 6 ; k++)
                                            {
                                                if(checkarray[k] == 1)
                                                {
                                                    for(int t = k + 1 ; t < 6 ; t++)
                                                    {
                                                        if(checkarray[t] == 1)
                                                        {
                                                            QMessageBox message ;
                                                            message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                            message.exec() ;
                                                            break ;
                                                        }
                                                    }
                                                }
                                                break ;
                                            }
                                        }
                                    }

                                    else if(j == 2)
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                if(k == 3)
                                                {
                                                    if(x == 1)
                                                    {
                                                        for(int t = k+1 ; t < 6 ; t++)
                                                        {
                                                            if(checkarray[t] == 1)
                                                            {
                                                                QMessageBox message ;
                                                                message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[2][0] + "\n" + arraybox[3][0] + "\n" + arraybox[t][0])) ;
                                                                message.exec() ;
                                                                break ;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        for(int t = k+1 ; t < 6 ; t++)
                                                        {
                                                            if(checkarray[t] == 1)
                                                            {
                                                                QMessageBox message ;
                                                                message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[2][0] + "\n" + arraybox[3][1] + "\n" + arraybox[t][0])) ;
                                                                message.exec() ;
                                                                break ;
                                                            }
                                                        }
                                                    }
                                                }

                                                else
                                                {
                                                    for(int t = k+1 ; t < 6 ; t++)
                                                    {
                                                        if(checkarray[t] == 1)
                                                        {
                                                            QMessageBox message ;
                                                            message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[2][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                            message.exec() ;
                                                            break ;
                                                        }
                                                    }
                                                }
                                            }
                                            break ;
                                        }
                                    }

                                    else
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                for(int t = k+1 ; t < 6 ; t++)
                                                {
                                                    if(checkarray[t] == 1)
                                                    {
                                                        QMessageBox message ;
                                                        message.setText(QString::fromStdString(arraybox[1][1] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                        message.exec() ;
                                                        break ;
                                                    }
                                                }
                                            }
                                            break ;
                                        }
                                    }
                                }
                                break ;
                            }
                        }
                    }

                    else if(i == 3)
                    {
                        if(x == 1)
                        {
                            QMessageBox message ;
                            message.setText(QString::fromStdString(arraybox[3][0] + "\n" + arraybox[4][0] + "\n" + arraybox[5][0] + "\n" + arraybox[6][0])) ;
                            message.exec() ;
                            break ;
                        }

                        else
                        {
                            QMessageBox message ;
                            message.setText(QString::fromStdString(arraybox[3][1] + "\n" + arraybox[4][0] + "\n" + arraybox[5][0] + "\n" + arraybox[6][0])) ;
                            message.exec() ;
                            break ;
                        }
                    }

                    else
                    {
                        for(int j = i+1 ; j < 6 ; j++)
                        {
                            if(checkarray[j] == 1)
                            {
                                if(j == 3)
                                {
                                    if(x == 1)
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                for(int t = k+1 ; t < 6 ; t++)
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[i][0] + "\n" + arraybox[3][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                            break ;
                                        }
                                    }

                                    else
                                    {
                                        for(int k = j+1 ; k < 6 ; k++)
                                        {
                                            if(checkarray[k] == 1)
                                            {
                                                for(int t = k+1 ; t < 6 ; t++)
                                                {
                                                    QMessageBox message ;
                                                    message.setText(QString::fromStdString(arraybox[i][0] + "\n" + arraybox[3][1] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                    message.exec() ;
                                                    break ;
                                                }
                                            }
                                            break ;
                                        }
                                    }
                                }

                                else
                                {
                                    for(int k = j+1 ; k < 6 ; k++)
                                    {
                                        if(checkarray[k] == 1)
                                        {
                                            for(int t = k+1 ; t < 6 ; t++)
                                            {
                                                QMessageBox message ;
                                                message.setText(QString::fromStdString(arraybox[i][0] + "\n" + arraybox[j][0] + "\n" + arraybox[k][0] + "\n" + arraybox[t][0])) ;
                                                message.exec() ;
                                                break ;
                                            }
                                        }
                                        break ;
                                    }
                                }
                            }
                            break ;
                        }
                    }
                }
                    break ;
                }
                break ;
        }

        case 5 :
        case 6 :
        {
                QMessageBox::warning(this , "error" , "لطفا اطلاعات را به درستی وارد کنید") ;
                break ;
        }


    }
}
