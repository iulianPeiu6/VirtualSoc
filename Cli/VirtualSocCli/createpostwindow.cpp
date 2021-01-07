#include "createpostwindow.h"
#include "ui_createpostwindow.h"

CreatePostWindow::CreatePostWindow(QWidget *parent, int _sd, User* _user) :
    QMainWindow(parent),
    ui(new Ui::CreatePostWindow)
{
    Parent=parent;
    sd=_sd;
    user=_user;

    ui->setupUi(this);
    ui->public_radioButton->click();
}

CreatePostWindow::~CreatePostWindow()
{
    delete ui;
}


QString CreatePostWindow::validate(QString post_title,QString post_text){

    if (post_title=="")
        return "The title is required!";

    if (post_text=="")
        return "The text is required!";

    if (post_title.length()>32)
        return "The title has maximum 32 characters!";

    if (post_text.length()>4096)
        return "The text has maximum 4096 characters!";

    return "";

}

void CreatePostWindow::on_create_pushButton_clicked()
{
    QString title=ui->post_title_lineEdit->text();

    QString text=ui->post_text_lineEdit->text();


    QString validationMsg=validate(title,text);

    if (validationMsg!=""){
        QMessageBox::warning(this,"Create Error",validationMsg);
        return;
    }

    QString visibility;

    if (ui->private_radioButton->isChecked())
        visibility="private";
    else
        visibility="public";

    QString cmd="14 " + title + "~" + text + "~" + visibility + "~" +QString::number(user->UserId);

    QString resp =sendMsg(sd,cmd);

    if (resp=="Post created!"){
        QMessageBox::information(this,"Info","Post successfully created!");
        close();
        Parent->show();
    }
}

