#include "explorewindow.h"
#include "ui_explorewindow.h"
#include "cliLogic.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QtDebug>

ExploreWindow::ExploreWindow(QWidget *parent, int _sd, User* _user) :
    QMainWindow(parent),
    ui(new Ui::ExploreWindow)
{
    sd=_sd;
    Parent=parent;
    user= _user;

    ui->setupUi(this);

    QString resp=sendMsg(sd,"6 " + QString::number(user->UserId));

    QStringList usersDetails = resp.split(QLatin1Char(' '));

    int numOfUsers=usersDetails.count()/7;

    QVBoxLayout* verticalLayout=new QVBoxLayout();
    QHBoxLayout* horizontalLayout[numOfUsers];
    QLabel* activeLabel[numOfUsers];
    QLabel* usernameLabel[numOfUsers];
    QPushButton* SeeProfile[numOfUsers];

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
        usernameLabel[i]->setText(usersDetails[i*7+1]);
        horizontalLayout[i]->addWidget(usernameLabel[i]);
        horizontalLayout[i]->addWidget(activeLabel[i]);
        horizontalLayout[i]->addWidget(SeeProfile[i]);
        verticalLayout->addLayout(horizontalLayout[i]);
    }
    ui->scrollAreaWidgetContents_2->setLayout(verticalLayout);
    ui->scrollAreaWidgetContents_2->show();

    connect(ui->search_pushButton, SIGNAL(clicked()), this, SLOT(search_action(numOfUsers,horizontalLayout)));


}

ExploreWindow::~ExploreWindow()
{

    delete ui;
}

void ExploreWindow::search_action(int numOfUsers,QHBoxLayout* horizontalLayout[])
{
    qDebug() <<ui->search_lineEdit->text();
//    QString part_username=ui->search_lineEdit->text();

//    for (int i=0;i<numOfUsers;i++){
//        if (ui->usernameLabel[i]->text().contains(part_username))
//            ui->usernameLabel[i];
//    }
}
