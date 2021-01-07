#include "showmygroups.h"
#include "ui_showmygroups.h"
#include <QtDebug>

ShowMyGroups::ShowMyGroups(QWidget *parent, int _sd,User* _user) :
    QMainWindow(parent),
    ui(new Ui::ShowMyGroups)
{
    sd=_sd;
    user=_user;
    Parent=parent;
    ui->setupUi(this);

    drawGroupsArea();
}

void ShowMyGroups::drawGroupsArea(){

    QString resp=sendMsg(sd,"20 "+QString::number(user->UserId));
    QStringList groupDetails =resp.split(QLatin1Char(' '));
    QVBoxLayout* verticalLayout=new QVBoxLayout();
    qDebug() <<groupDetails.count()/4;
    groups= new Group*[groupDetails.count()/4];


    for (int i=0;i<groupDetails.count()/4;i++){
        groups[i]=new Group(groupDetails[i]+" "+groupDetails[i+1]+" "+groupDetails[i+2]+" "+groupDetails[i+3]);
        qDebug() <<"group created";
        QHBoxLayout* horizontalLayout=new QHBoxLayout();
        QLabel* groupNameLabel=new QLabel();
        groupNameLabel->setAlignment(Qt::AlignLeft);
        groupNameLabel->setText(groups[i]->GroupName);
        QPushButton* enterGroupChat=new QPushButton();
        enterGroupChat->setText("Enter Group Chat");
        connect(enterGroupChat,&QPushButton::clicked, this, [=](){      sendMessageWindow=new SendMessageWindow(this,sd,user,groups[i]);
                                                                        sendMessageWindow->show(); });
        horizontalLayout->addWidget(groupNameLabel);
        horizontalLayout->addWidget(enterGroupChat);
        verticalLayout->addLayout(horizontalLayout);
        qDebug() <<"done";
    }
    verticalLayout->addStretch();
    ui->scrollArea->setLayout(verticalLayout);
    ui->scrollArea->show();
}

ShowMyGroups::~ShowMyGroups()
{
    delete ui;
}
