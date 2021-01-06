#include "register.h"
#include "ui_register.h"
#include "cliLogic.h"
#include "user.h"
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include <QMessageBox>
#include <QtDebug>


Register::Register(QWidget *parent,int _sd) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    sd=_sd;
    ui->setupUi(this);
    Parent=parent;
    QPixmap logo_pix("/home/iulian/RC_proj/VirtualSoc/images/logo.png");
    ui->logo_label->setPixmap(logo_pix);

    QBitmap map(279,186);
    map.fill(Qt::color0);

    QPainter painter( &map );
    painter.setBrush(Qt::color1);
    painter.drawRoundedRect( 0, 0, 279, 186,270,180);

    logo_pix.setMask(map);
    ui->logo_label->setPixmap(logo_pix);

    ui->back_pushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/Back_Arrow.png);");
}

Register::~Register()
{
    delete ui;
}

QString validateRegistration(QString username,QString password, QString confirm_password){

    if (username=="")
        return "The username is required!";

    if (password=="")
        return "The password is required!";

    if (confirm_password=="")
        return "The password confirmation is required!";

    if (username.length()>16)
        return "The username has maximum 16 characters!";

    if (!(password.length()<=16 and password.length()>=6))
        return "The password has minimum 6 characters and maximum 16!";

    if (confirm_password!=password)
        return "Password and confirm password don't match!";

    return "";

}
void Register::on_registerButton_clicked()
{
    QString username=ui->username_lineEdit->text();

    QString password=ui->password_lineEdit->text();

    QString confirm_password=ui->confirm_password_lineEdit->text();

    QString validationMsg=validateRegistration(username,password,confirm_password);

    if (validationMsg!=""){
        QMessageBox::warning(this,"Register Error",validationMsg);
        return;
    }

    QString cmd="1 " + username+ " " + password;

    QString resp =sendMsg(sd,cmd);

    if (resp=="Username already taken")
        QMessageBox::warning(this,"Registration Error","Username already taken!");
    else{
        QMessageBox::information(this,"Info","Account created!");
        hide();
        home=new Home(Parent,sd,new User(resp));
        home->show();

    }
}

void Register::on_back_pushButton_clicked()
{
    this->hide();
    Parent->show();
}
