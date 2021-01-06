#include "updateuserinfo.h"
#include "ui_updateuserinfo.h"
#include <QMessageBox>
#include "cliLogic.h"
#include <QtDebug>

UpdateUserInfo::UpdateUserInfo(QWidget *parent,int _sd,User* _user) :
    QMainWindow(parent),
    ui(new Ui::UpdateUserInfo)
{
    Parent=parent;
    sd=_sd;
    user=_user;

    ui->setupUi(this);
    ui->back_pushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/Back_Arrow.png);");

    ui->username_lineEdit->setText(user->Username);
    ui->password_lineEdit->setText(user->Password);
    if (user->UserVisibility=="public")
        ui->public_radioButton->click();
    else
        ui->private_radioButton->click();



}



UpdateUserInfo::~UpdateUserInfo()
{
    delete ui;
}

void UpdateUserInfo::on_back_pushButton_clicked()
{
    this->close();
    Parent->show();
}

QString UpdateUserInfo::validate(QString username,QString password, QString confirm_password){

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

void UpdateUserInfo::on_submit_pushButton_clicked()
{
    QString username=ui->username_lineEdit->text();

    QString password=ui->password_lineEdit->text();

    QString confirm_password=ui->confirm_password_lineEdit->text();

    QString validationMsg=validate(username,password,confirm_password);

    if (validationMsg!=""){
        QMessageBox::warning(this,"Edit Error",validationMsg);
        return;
    }

    QString visibility;

    if (ui->private_radioButton->isChecked())
        visibility="private";
    else
        visibility="public";

    QString cmd="3 " + QString::number(user->UserId) + " " + username + " " + visibility + " " + password;

    QString resp =sendMsg(sd,cmd);

    if (resp=="Username already taken")
        QMessageBox::warning(this,"Edit Error","Username already taken!");
    else{
        emit(userDetailsChanged(new User(resp)));
        QMessageBox::information(this,"Info","Account successfully updated!");

        close();

        Parent->show();
    }
}
