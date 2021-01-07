#include "guesthomewindow.h"
#include "ui_guesthomewindow.h"

GuestHomeWindow::GuestHomeWindow(QWidget *parent, int _sd) :
    QMainWindow(parent),
    ui(new Ui::GuestHomeWindow)
{
    sd=_sd;
    Parent=parent;
    ui->setupUi(this);
    ui->back_pushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/Back_Arrow.png);");
}

GuestHomeWindow::~GuestHomeWindow(){
    delete ui;
}

void GuestHomeWindow::on_pushButton_clicked(){
    this->hide();
    _register=new Register(this,sd);
    _register->show();
}

void GuestHomeWindow::on_back_pushButton_clicked(){
    this->hide();
    Parent->show();
}

void GuestHomeWindow::on_pushButton_2_clicked(){
    _searchWindow=new searchWindow(this,sd,nullptr);
    _searchWindow->show();
}
