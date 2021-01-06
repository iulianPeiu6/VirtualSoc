#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent,int _sd, User* _user) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    sd=_sd;
    user=_user;
    Parent=parent;
    u_verticalLayout=nullptr;


    ui->setupUi(this);
    ui->search_pushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/searchIcon.png);");
    ui->posts_refreshpushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/refresh_icon.png);");
    ui->friends_refreshpushButton->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/refresh_icon.png);");
    ui->post_biglabel->setStyleSheet(" color: blue;");

    drawMenuBar();
    drawProfile();
    drawFriendsArea();
    printPosts();


}

void Home::drawFriendsArea(){

    QString resp=sendMsg(sd,"7 " + QString::number(user->UserId));

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
        connect(u_seeProfile[i],&QPushButton::clicked, this, [=](){

                                                                        showProfileWindow = new ShowProfileWindow(this,sd,user,users[i]);
                                                                        showProfileWindow->show(); });
    }
    u_verticalLayout->addStretch();
    ui->friends_scrollAreaWidgetContents->setLayout(u_verticalLayout);
    ui->friends_scrollAreaWidgetContents->show();

    connect(ui->search_lineEdit,&QLineEdit::textChanged, this,&Home::search_action);
}
void Home::drawProfile(){
    ui->current_username_info_label->setText(user->Username);
    ui->current_access_info_label->setText(user->UserVisibility);
    ui->current_registration_info_label->setText("\t"+user->RegistrationDate);
    if (user->Admin)
        ui->current_user_type_info_label->setText("Admin");
    else
        ui->current_user_type_info_label->setText("Ordinary user");

}

void Home::drawMenuBar(){

    QMenu* user_menu= ui->menubar->addMenu("Account");
    QAction* editUserAction=user_menu->addAction("Edit profile");
    QAction* delete_userAction=user_menu->addAction("Delete my account");
    QAction* logoutAction=user_menu->addAction("Logout");

    connect(logoutAction,&QAction::triggered, this,&Home::logout);
    connect(delete_userAction,&QAction::triggered, this,&Home::deleteUser);
    connect(editUserAction,&QAction::triggered, this,&Home::updateUser);

    QMenu* social_menu= ui->menubar->addMenu("Social");
    QAction* show_all_usersAction=social_menu->addAction("Find users");
    QAction* show_all_friendsAction=social_menu->addAction("Show my friend requests");
    QAction* show_my_groupsAction=social_menu->addAction("Show my groups");
    QAction* create_new_postAction=social_menu->addAction("Create new post");
    QAction* create_new_groupAction=social_menu->addAction("Create new group");


    connect(show_all_usersAction,&QAction::triggered, this,&Home::list_Users);
    connect(show_all_friendsAction,&QAction::triggered, this,&Home::list_Friends);
    connect(create_new_postAction,&QAction::triggered, this,&Home::create_post);
    connect(create_new_groupAction,&QAction::triggered, this,&Home::create_group);
    connect(show_my_groupsAction,&QAction::triggered, this,&Home::show_groups);
}

void Home::printPosts(){
    QString resp=sendMsg(sd,"11 " + QString::number(user->UserId));

    QStringList postsDetails = resp.split(QLatin1Char('~'));

    numOfPosts=postsDetails.count()/7;
    posts= new Post*[numOfPosts];

    p_verticalLayout=new QVBoxLayout();
    p_horizontalLayout=new QHBoxLayout*[numOfPosts];
    p_post_titleLabel=new QLabel*[numOfPosts];
    p_post_textLabel=new QLabel*[numOfPosts];
    p_delete_postPushButton=new QPushButton*[numOfPosts];
    p_likePushButton=new QPushButton*[numOfPosts];
    p_post_likesLabel=new QLabel*[numOfPosts];
    p_line=new QFrame*[numOfPosts];

    for (int i=0;i<numOfPosts;i++){

        posts[i]=new Post(  postsDetails[i*7]+"~"
                            +postsDetails[i*7+1]+"~"
                            +postsDetails[i*7+2]+"~"
                            +postsDetails[i*7+3]+"~"
                            +postsDetails[i*7+4]+"~"
                            +postsDetails[i*7+5]+"~"
                            +postsDetails[i*7+6]);

            p_horizontalLayout[i]=new QHBoxLayout();
            p_post_titleLabel[i]= new QLabel();
            p_post_textLabel[i]= new QLabel();
            p_post_likesLabel[i]= new QLabel();
            p_delete_postPushButton[i]= new QPushButton();
            p_likePushButton[i]= new QPushButton();
            p_line[i]=new QFrame();

            p_post_titleLabel[i]->setText(posts[i]->PostTitle+" ("+posts[i]->PostDate+")");
            p_post_titleLabel[i]->setStyleSheet("color:blue; font-size:20px;");

            p_post_textLabel[i]->setText(posts[i]->PostText);
            p_post_textLabel[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            p_post_textLabel[i]->setWordWrap(true);

            p_post_likesLabel[i]->setText(QString::number(posts[i]->Likes));
            p_delete_postPushButton[i]->setMaximumHeight(35);
            p_delete_postPushButton[i]->setMaximumWidth(35);
            p_delete_postPushButton[i]->setMinimumHeight(35);
            p_delete_postPushButton[i]->setMinimumWidth(35);
            p_delete_postPushButton[i]->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/delete_icon.png);");

            p_likePushButton[i]->setMaximumHeight(35);
            p_likePushButton[i]->setMaximumWidth(35);
            p_likePushButton[i]->setMinimumHeight(35);
            p_likePushButton[i]->setMinimumWidth(35);
            p_likePushButton[i]->setStyleSheet("border-image:url(/home/iulian/RC_proj/VirtualSoc/images/like_icon.png);");

            connect(p_likePushButton[i],&QPushButton::clicked, this, [=](){     QString updateLikesMsg=sendMsg(sd,"13 "+QString::number(posts[i]->PostId));
                p_post_likesLabel[i]->setText(QString::number(p_post_likesLabel[i]->text().toInt()+1));
                p_post_likesLabel[i]->show(); });

            connect(p_delete_postPushButton[i],&QPushButton::clicked, this, [=](){      QString deletePostMsg=sendMsg(sd,"12 "+QString::number(posts[i]->PostId));
                p_post_titleLabel[i]->hide();
                p_post_textLabel[i]->hide();
                p_post_likesLabel[i]->hide();
                p_delete_postPushButton[i]->hide();
                p_post_likesLabel[i]->hide();
                p_likePushButton[i]->hide();
                p_post_likesLabel[i]->hide(); });
            p_line[i]->setFrameShape(QFrame::HLine);
            p_line[i]->setFrameShadow(QFrame::Sunken);

            p_horizontalLayout[i]->addWidget(p_delete_postPushButton[i]);
            p_horizontalLayout[i]->addWidget(p_post_likesLabel[i]);
            p_horizontalLayout[i]->addWidget(p_likePushButton[i]);

            p_verticalLayout->addWidget(p_post_titleLabel[i]);
            p_verticalLayout->addWidget(p_post_textLabel[i]);

            p_verticalLayout->addLayout(p_horizontalLayout[i]);
            if (i<numOfPosts-1)
                p_verticalLayout->addWidget(p_line[i]);

    }
    p_verticalLayout->addStretch();
    ui->posts_scrollArea->setLayout(p_verticalLayout);
    ui->posts_scrollArea->show();

}


void Home::logout(){
    sendMsg(sd,"4 "+user->Username);
    user=nullptr;
    hide();
    Parent->show();
}

void Home::updateUser(){

    hide();
    updateUserInfo= new UpdateUserInfo(this,sd,user);
    connect(updateUserInfo,SIGNAL(userDetailsChanged(User*)),this, SLOT(updateUserPage(User* )));
    updateUserInfo->show();

}
void Home::updateUserPage(User* _user){
    user=_user;

    ui->current_username_info_label->setText(_user->Username);
    ui->current_access_info_label->setText(_user->UserVisibility);
    ui->current_registration_info_label->setText(_user->RegistrationDate);
    if (_user->Admin)
        ui->current_user_type_info_label->setText("Admin");
    else
        ui->current_user_type_info_label->setText("Ordinary user");
}


void Home::deleteUser(){

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QString resp=sendMsg(sd,"5 " +QString::number(user->UserId));
        hide();
        Parent->show();
        QMessageBox::information(this,"Info","Account deleted!");
    }

}

void Home::list_Users(){
    _searchWindow= new searchWindow(this,sd,user);
    _searchWindow->show();
}
void Home::list_Friends(){
    showFriendsWindow= new ShowFriendsWindow(this,sd,user);
    showFriendsWindow->show();
}

void Home::create_post(){
    createPostWindow= new CreatePostWindow(this,sd,user);
    createPostWindow->show();
}

void Home::create_group(){
    createGroupWindow= new CreateGroupWindow(this,sd,user);
    createGroupWindow->show();
}
void Home::show_groups(){
    showMyGroups= new ShowMyGroups(this,sd,user);
    showMyGroups->show();
}

Home::~Home(){

    delete ui;
}

void Home::closeEvent(QCloseEvent *event){
    sendMsg(sd,"4 "+user->Username);
    event->accept();
}

bool Home::printUser(QString s1, QString s2){
    if (s1.length()<s2.length())
        return false;
    return (s1.mid(0,s2.length())==s2);
}
void Home::search_action()
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


void Home::on_posts_refreshpushButton_clicked(){
    delete p_verticalLayout;
    for (int i=0;i<numOfPosts;i++){
        p_post_titleLabel[i]->hide();
        p_post_textLabel[i]->hide();
        p_delete_postPushButton[i]->hide();
        p_likePushButton[i]->hide();
        p_post_likesLabel[i]->hide();
        p_line[i]->hide();
    }
    delete[] p_horizontalLayout;
    delete[] p_post_titleLabel;
    delete[] p_post_textLabel;
    delete[] p_delete_postPushButton;
    delete[] p_likePushButton;
    delete[] p_post_likesLabel;
    delete[] p_line;
    printPosts();

}

void Home::on_friends_refreshpushButton_clicked(){
    delete u_verticalLayout;
    for (int i=0;i<numOfUsers;i++){
        u_activeLabel[i]->hide();
        u_usernameLabel[i]->hide();
        u_sendMessage[i]->hide();
        u_seeProfile[i]->hide();
    }
    delete[] u_horizontalLayout;
    delete[] u_activeLabel;
    delete[] u_usernameLabel;
    delete[] u_sendMessage;
    delete[] u_seeProfile;
    drawFriendsArea();
}
