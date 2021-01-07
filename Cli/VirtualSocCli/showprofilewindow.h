#ifndef SHOWPROFILEWINDOW_H
#define SHOWPROFILEWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QMessageBox>
#include <QtDebug>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "post.h"
#include "group.h"
#include "cliLogic.h"
#include "sendmessagewindow.h"

namespace Ui {
class ShowProfileWindow;
}

class ShowProfileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowProfileWindow(QWidget *parent = nullptr, int _sd=0, User* _user=nullptr, User* _profile=nullptr);

    int sd;
    QWidget *Parent;
    User* user;
    User* profile;
    ~ShowProfileWindow();

private slots:
    void on_friendship_pushButton_clicked();

private:
    Ui::ShowProfileWindow *ui;
    SendMessageWindow* sendMessageWindow;
    ShowProfileWindow* showProfileWindow;
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
    int lastIdPost;

    void drawFriendsArea();
    void search_action();
    bool printUser(QString , QString);
    void drawProfile();
    void drawMenuBar();
    void printPosts();
};

#endif // SHOWPROFILEWINDOW_H
