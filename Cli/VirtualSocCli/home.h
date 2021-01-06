#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include "user.h"
#include "updateuserinfo.h"
#include "searchwindow.h"
#include "showfriendswindow.h"
#include "sendmessagewindow.h"
#include "cliLogic.h"
#include <QMessageBox>
#include <QtDebug>
#include <QCloseEvent>
#include "post.h"
#include "createpostwindow.h"
#include "showprofilewindow.h"
#include <QScrollArea>
#include "creategroupwindow.h"
#include "showmygroups.h"

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr, int _sd=0, User* _user=nullptr);
    ~Home();

private slots:
    void on_posts_refreshpushButton_clicked();
    void on_friends_refreshpushButton_clicked();
    void updateUserPage(User* _user);

private:
    Ui::Home *ui;

    int sd;
    QWidget *Parent;
    User* user;
    UpdateUserInfo* updateUserInfo;
    searchWindow* _searchWindow;
    CreateGroupWindow* createGroupWindow;
    ShowProfileWindow* showProfileWindow;
    ShowFriendsWindow* showFriendsWindow;
    SendMessageWindow* sendMessageWindow;
    CreatePostWindow* createPostWindow;
    ShowMyGroups* showMyGroups;

    int numOfUsers;
    User** users;
    QVBoxLayout* u_verticalLayout;
    QHBoxLayout** u_horizontalLayout;
    QLabel** u_activeLabel;
    QLabel** u_usernameLabel;
    QPushButton** u_sendMessage;
    QPushButton** u_seeProfile;

    int numOfPosts;
    Post** posts;
    QVBoxLayout* p_verticalLayout;
    QHBoxLayout** p_horizontalLayout;
    QLabel** p_post_titleLabel;
    QLabel** p_post_textLabel;
    QPushButton** p_delete_postPushButton;
    QPushButton** p_likePushButton;
    QLabel** p_post_likesLabel;
    QFrame** p_line;

    void closeEvent(QCloseEvent *event);
    void drawFriendsArea();
    void search_action();
    bool printUser(QString , QString);
    void drawProfile();
    void drawMenuBar();
    void create_group();
    void logout();
    void updateUser();
    void deleteUser();
    void list_Users();
    void list_Friends();
    void create_post();
    void printPosts();
    void show_groups();
    void showUpdatedUserDetails();


};

#endif // HOME_H
