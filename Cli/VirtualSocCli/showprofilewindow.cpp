#include "showprofilewindow.h"
#include "ui_showprofilewindow.h"

ShowProfileWindow::ShowProfileWindow(QWidget *parent, int _sd, User* _user, User* _profile) :
    QMainWindow(parent),
    ui(new Ui::ShowProfileWindow)
{

    sd= _sd;
    user=_user;
    profile=_profile;
    lastIdPost=-1;

    ui->setupUi(this);

    ui->post_biglabel->setStyleSheet(" color: blue;");
    ui->search_pushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/searchIcon.png);");
    drawProfile();
    drawFriendsArea();
    p_verticalLayout=new QVBoxLayout();
    printPosts();
    ui->posts_scrollArea->setLayout(p_verticalLayout);
    ui->posts_scrollArea->show();


}

void ShowProfileWindow::drawProfile(){
    ui->current_username_info_label->setText(profile->Username);
    ui->current_access_info_label->setText(profile->UserVisibility);
    ui->current_registration_info_label->setText("\t"+profile->RegistrationDate);
    if (profile->Admin)
        ui->current_user_type_info_label->setText("Admin");
    else
        ui->current_user_type_info_label->setText("Ordinary user");
    if (profile->ActiveStatus){
        ui->current_active_status_info_label->setText("online");
        ui->current_active_status_info_label->setStyleSheet("color: green;");
    }
    else{
        ui->current_active_status_info_label->setText("offline");
        ui->current_active_status_info_label->setStyleSheet("color: red;");
    }

    QString friendshipType=sendMsg(sd,"15 " +QString::number(user->UserId) + " " +QString::number(profile->UserId) );
    ui->friendship_pushButton->setText(friendshipType);

}

void ShowProfileWindow::drawFriendsArea(){

    QString resp=sendMsg(sd,"7 " + QString::number(profile->UserId));

    QStringList usersDetails = resp.split(QLatin1Char(' '));

    numOfUsers=usersDetails.count()/7;
    users= new User*[numOfUsers];

    u_verticalLayout=new QVBoxLayout();
    u_horizontalLayout = new QHBoxLayout*[numOfUsers] ;
    u_activeLabel=new QLabel*[numOfUsers];
    u_usernameLabel=new QLabel*[numOfUsers];
    u_seeProfile= new QPushButton*[numOfUsers];
    u_sendMessage= new QPushButton*[numOfUsers];

    for (int i=0;i<numOfUsers;i++){
        users[i]=new User(  usersDetails[i*7]+" "+
                            usersDetails[i*7+1]+" "+
                            usersDetails[i*7+2]+" "+
                            usersDetails[i*7+3]+" "+
                            usersDetails[i*7+4]+" "+
                            usersDetails[i*7+5]+" "+
                            usersDetails[i*7+6]);

        u_horizontalLayout[i]= new QHBoxLayout();

        u_usernameLabel[i] = new QLabel();
        u_activeLabel[i]= new QLabel();
        if (usersDetails[i*7+6]=="true"){
            u_activeLabel[i]->setText("Online");
            u_activeLabel[i]->setStyleSheet("color: green");
        }
        else{
            u_activeLabel[i]->setText("Offline");
            u_activeLabel[i]->setStyleSheet("color: red");
        }

        u_sendMessage[i] = new QPushButton();
        u_seeProfile[i] = new QPushButton();
        u_seeProfile[i]->setText("See profile");
        u_sendMessage[i]->setText("Send Message");
        u_usernameLabel[i]->setText(usersDetails[i*7+1]);
        u_horizontalLayout[i]->addWidget(u_usernameLabel[i]);
        u_horizontalLayout[i]->addWidget(u_activeLabel[i]);
        u_horizontalLayout[i]->addWidget(u_sendMessage[i]);
        u_horizontalLayout[i]->addWidget(u_seeProfile[i]);
        u_verticalLayout->addLayout(u_horizontalLayout[i]);
        connect(u_sendMessage[i],&QPushButton::clicked, this, [=](){  QString groupDetails=sendMsg(sd,"10 "+QString::number(user->UserId)+" "+QString::number(users[i]->UserId));
                                                                    Group* group=new Group(groupDetails);
                                                                    sendMessageWindow = new SendMessageWindow(this,sd,user,group);
                                                                    sendMessageWindow->show(); });
    }
    u_verticalLayout->addStretch();
    ui->friends_scrollAreaWidgetContents->setLayout(u_verticalLayout);
    ui->friends_scrollAreaWidgetContents->show();

    connect(ui->search_lineEdit,&QLineEdit::textChanged, this,&ShowProfileWindow::search_action);
}

void ShowProfileWindow::printPosts(){
    QString resp=sendMsg(sd,"11 " + QString::number(profile->UserId));

    QStringList postsDetails = resp.split(QLatin1Char('~'));

    numOfPosts=postsDetails.count()/7;
    posts= new Post*[numOfPosts];

    for (int i=0;i<numOfPosts;i++){

        posts[i]=new Post(postsDetails[i*7]+"~"+postsDetails[i*7+1]+"~"+postsDetails[i*7+2]+"~"+postsDetails[i*7+3]+"~"+postsDetails[i*7+4]+"~"+postsDetails[i*7+5]+"~"+postsDetails[i*7+6]);

        if (lastIdPost<posts[i]->PostId){
            QHBoxLayout* p_horizontalLayout;
            QLabel* p_post_titleLabel;
            QLabel* p_post_textLabel;
            QPushButton* p_likePushButton;
            QLabel* p_post_likesLabel;

            p_horizontalLayout=new QHBoxLayout();
            p_post_titleLabel= new QLabel();
            p_post_textLabel= new QLabel();
            p_post_likesLabel= new QLabel();
            p_likePushButton= new QPushButton();

            p_post_titleLabel->setText(posts[i]->PostTitle+" ("+posts[i]->PostDate+")");
            p_post_titleLabel->setStyleSheet("color:blue; font-size:20px;");

            p_post_textLabel->setText(posts[i]->PostText);
            p_post_textLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            p_post_textLabel->setWordWrap(true);

            p_post_likesLabel->setText(QString::number(posts[i]->Likes));


            p_likePushButton->setMaximumHeight(35);
            p_likePushButton->setMaximumWidth(35);
            p_likePushButton->setMinimumHeight(35);
            p_likePushButton->setMinimumWidth(35);
            p_likePushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/like_icon.png);");

            connect(p_likePushButton,&QPushButton::clicked, this, [=](){        QString updateLikesMsg=sendMsg(sd,"13 "+QString::number(posts[i]->PostId));
                                                                                p_post_likesLabel->setText(QString::number(p_post_likesLabel->text().toInt()+1));
                                                                                p_post_likesLabel->show(); });

            QFrame *line;
            line = new QFrame();
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);

            p_horizontalLayout->addWidget(p_likePushButton);
            p_horizontalLayout->addWidget(p_post_likesLabel);

            if (i!=0)
                p_verticalLayout->addWidget(line);
            p_verticalLayout->addWidget(p_post_titleLabel);
            p_verticalLayout->addWidget(p_post_textLabel);
            p_verticalLayout->addLayout(p_horizontalLayout);
            lastIdPost=posts[i]->PostId;
        }

    }
    p_verticalLayout->addStretch();

}

bool ShowProfileWindow::printUser(QString s1, QString s2){
    if (s1.length()<s2.length())
        return false;
    return (s1.mid(0,s2.length())==s2);
}
void ShowProfileWindow::search_action()
{
    QString part_username=ui->search_lineEdit->text();

    for (int i=0;i<numOfUsers;i++){
        if (printUser(u_usernameLabel[i]->text(),part_username)){
            u_usernameLabel[i]->show();
            u_activeLabel[i]->show();
            u_seeProfile[i]->show();
            u_sendMessage[i]->show();
        }
        else{
            u_usernameLabel[i]->hide();
            u_activeLabel[i]->hide();
            u_seeProfile[i]->hide();
            u_sendMessage[i]->hide();
        }
    }
}


ShowProfileWindow::~ShowProfileWindow(){
    delete ui;
}

void ShowProfileWindow::on_friendship_pushButton_clicked(){

    if (ui->friendship_pushButton->text()=="Accept friend request"){
        QString resp=sendMsg(sd,"16 "+QString::number(user->UserId)+" "+QString::number(profile->UserId)+" 1");
        ui->friendship_pushButton->setText("Delete friend from friendlist");
    }
    else if (ui->friendship_pushButton->text()=="Cancel friend request"){
        QString resp=sendMsg(sd,"17 "+QString::number(user->UserId)+" "+QString::number(profile->UserId));
        ui->friendship_pushButton->setText("Send friend request");
    }
    else if (ui->friendship_pushButton->text()=="Send friend request"){
        QString resp=sendMsg(sd,"16 "+QString::number(user->UserId)+" "+QString::number(profile->UserId)+" 0");
        ui->friendship_pushButton->setText("Cancel friend request");
    }
    else if (ui->friendship_pushButton->text()=="Delete friend from friendlist"){
        QString resp=sendMsg(sd,"17 "+QString::number(user->UserId)+" "+QString::number(profile->UserId));
        ui->friendship_pushButton->setText("Send friend request");
    }
}
