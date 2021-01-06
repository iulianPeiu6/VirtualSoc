#include "showfriendswindow.h"
#include "ui_showfriendswindow.h"


ShowFriendsWindow::ShowFriendsWindow(QWidget *parent, int _sd,User* _user) :
    QMainWindow(parent),
    ui(new Ui::ShowFriendsWindow)
{
    sd=_sd;
    Parent=parent;
    user=_user;
    ui->setupUi(this);

    ui->search_pushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/searchIcon.png);");
    QString resp=sendMsg(sd,"18 " + QString::number(user->UserId));

    QStringList usersDetails = resp.split(QLatin1Char(' '));

    numOfUsers=usersDetails.count()/7;
    users= new User*[numOfUsers];

    verticalLayout=new QVBoxLayout();
    horizontalLayout = new QHBoxLayout*[numOfUsers] ;
    activeLabel=new QLabel*[numOfUsers];
    usernameLabel=new QLabel*[numOfUsers];
    seeProfile= new QPushButton*[numOfUsers];

    for (int i=0;i<numOfUsers;i++){
        users[i]=new User(  usersDetails[i*7]+" "+
                            usersDetails[i*7+1]+" "+
                            usersDetails[i*7+2]+" "+
                            usersDetails[i*7+3]+" "+
                            usersDetails[i*7+4]+" "+
                            usersDetails[i*7+5]+" "+
                            usersDetails[i*7+6]);

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

        seeProfile[i] = new QPushButton();
        seeProfile[i]->setText("See profile");
        usernameLabel[i]->setText(usersDetails[i*7+1]);
        horizontalLayout[i]->addWidget(usernameLabel[i]);
        horizontalLayout[i]->addWidget(activeLabel[i]);
        horizontalLayout[i]->addWidget(seeProfile[i]);
        verticalLayout->addLayout(horizontalLayout[i]);
        connect(seeProfile[i],&QPushButton::clicked, this, [=](){   showProfileWindow = new ShowProfileWindow(this,sd,user,users[i]);
                                                                    showProfileWindow->show(); });
    }
    verticalLayout->addStretch();
    ui->scrollAreaWidgetContents->setLayout(verticalLayout);
    ui->scrollAreaWidgetContents->show();



    connect(ui->search_lineEdit,&QLineEdit::textChanged, this,&ShowFriendsWindow::search_action);

}

ShowFriendsWindow::~ShowFriendsWindow()
{
    delete ui;
}

bool ShowFriendsWindow::printUser(QString s1, QString s2){
    if (s1.length()<s2.length())
        return false;
    return (s1.mid(0,s2.length())==s2);
}
void ShowFriendsWindow::search_action()
{
    QString part_username=ui->search_lineEdit->text();

    for (int i=0;i<numOfUsers;i++){
        if (printUser(usernameLabel[i]->text(),part_username)){
            usernameLabel[i]->show();
            activeLabel[i]->show();
            seeProfile[i]->show();
        }
        else{
            usernameLabel[i]->hide();
            activeLabel[i]->hide();
            seeProfile[i]->hide();
        }
    }
}

