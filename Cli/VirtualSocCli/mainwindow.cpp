#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cliLogic.h"
#include <QtDebug>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, int _sd)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    sd=_sd;

    ui->setupUi(this);

    QPixmap pix("/home/iulian/RC_proj/VirtualSoc/images/logo.png");
    ui->logo_label->setPixmap(pix);

    QBitmap map(279,186);
    map.fill(Qt::color0);

    QPainter painter( &map );
    painter.setBrush(Qt::color1);
    painter.drawRoundedRect( 0, 0, 279, 186,270,180);

    pix.setMask(map);
    ui->logo_label->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    sendMsg(sd,"0 quit");
    closeConn(sd);
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString username=ui->username_lineEdit->text();

    if (username==""){
        QMessageBox::warning(this,"Authentication Error","The username is required");
        return ;
    }

    QString password=ui->password_lineEdit->text();

    if (password==""){
        QMessageBox::warning(this,"Authentication Error","The password is required");
        return ;
    }

    QString cmd="2 " + username+ " " + password;

    QString resp =sendMsg(sd,cmd);

    if (resp=="Wrong username or password")
        QMessageBox::warning(this,"Login Error","Wrong username or password");
    else{
        this->hide();
        user=new User(resp);
        home=new Home(this,sd,user);
        home->show();
    }

}

void MainWindow::on_create_accButton_clicked()
{
    this->hide();
    _register=new Register(this,sd);
    _register->show();
}

void MainWindow::on_guestButton_clicked(){

    this->hide();
    guestHomeWindow=new GuestHomeWindow(this,sd);
    guestHomeWindow->show();
}
