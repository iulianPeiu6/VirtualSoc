#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "cliLogic.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QtDebug>
#include <QLineEdit>

searchWindow::searchWindow(QWidget *parent, int _sd, User* _user) :
    QMainWindow(parent),
    ui(new Ui::searchWindow)
{
    sd=_sd;
    Parent=parent;
    user= _user;

    ui->setupUi(this);

    ui->search_pushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/searchIcon.png);");
    QString resp=sendMsg(sd,"6 " + QString::number(user->UserId));

    QStringList usersDetails = resp.split(QLatin1Char(' '));

    numOfUsers=usersDetails.count()/7;

    verticalLayout=new QVBoxLayout();
    horizontalLayout = new QHBoxLayout*[numOfUsers] ;
    activeLabel=new QLabel*[numOfUsers];
    usernameLabel=new QLabel*[numOfUsers];
    SeeProfile= new QPushButton*[numOfUsers];

    for (int i=0;i<numOfUsers;i++){

        horizontalLayout[i]= new QHBoxLayout();

        usernameLabel[i] = new QLabel();
        activeLabel[i]= new QLabel();
        if (usersDetails[i*7+6]=="true"){
            activeLabel[i]->setText("Online");
            activeLabel[i]->setStyleSheet("color: green");
        }
        else{
            activeLabel[i]->setText("Offline");
            activeLabel[i]->setStyleSheet("color: red");
        }

        SeeProfile[i] = new QPushButton();
        SeeProfile[i]->setText("See profile");
        connect(SeeProfile[i],&QPushButton::clicked, this, [=](){   showProfileWindow = new ShowProfileWindow(this,sd,user,new User(usersDetails[i*7]+" "+
                                                                                                                                    usersDetails[i*7+1]+" "+
                                                                                                                                    usersDetails[i*7+2]+" "+
                                                                                                                                    usersDetails[i*7+3]+" "+
                                                                                                                                    usersDetails[i*7+4]+" "+
                                                                                                                                    usersDetails[i*7+5]+" "+
                                                                                                                                    usersDetails[i*7+6]));
                                                                    showProfileWindow->show(); });
        usernameLabel[i]->setText(usersDetails[i*7+1]);
        horizontalLayout[i]->addWidget(usernameLabel[i]);
        horizontalLayout[i]->addWidget(activeLabel[i]);
        horizontalLayout[i]->addWidget(SeeProfile[i]);
        verticalLayout->addLayout(horizontalLayout[i]);
    }
    verticalLayout->addStretch();
    ui->scrollAreaWidgetContents_2->setLayout(verticalLayout);
    ui->scrollAreaWidgetContents_2->show();
    connect(ui->search_lineEdit,&QLineEdit::textChanged, this,&searchWindow::search_action);
}

searchWindow::~searchWindow()
{
    delete ui;
}

bool searchWindow::printUser(QString s1, QString s2){
    if (s1.length()<s2.length())
        return false;
    return (s1.mid(0,s2.length())==s2);
}
void searchWindow::search_action()
{
    QString part_username=ui->search_lineEdit->text();

    for (int i=0;i<numOfUsers;i++){
        if (printUser(usernameLabel[i]->text(),part_username)){
            usernameLabel[i]->show();
            activeLabel[i]->show();
            SeeProfile[i]->show();
        }
        else{
            usernameLabel[i]->hide();
            activeLabel[i]->hide();
            SeeProfile[i]->hide();
        }
    }
}
