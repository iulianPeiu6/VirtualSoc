#ifndef SHOWFRIENDSWINDOW_H
#define SHOWFRIENDSWINDOW_H

#include <QMainWindow>
#include "cliLogic.h"
#include "user.h"
#include "group.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "cliLogic.h"
#include "showprofilewindow.h"

namespace Ui {
class ShowFriendsWindow;
}

class ShowFriendsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowFriendsWindow(QWidget *parent = nullptr, int _sd=0,User* _user=nullptr);
    ~ShowFriendsWindow();

public slots:
    void search_action();

private:
    Ui::ShowFriendsWindow *ui;
    ShowProfileWindow* showProfileWindow;
    int numOfUsers;
    QVBoxLayout* verticalLayout;
    QHBoxLayout** horizontalLayout;
    QLabel** activeLabel;
    QLabel** usernameLabel;
    QPushButton** seeProfile;

    int sd;
    QWidget* Parent;
    User* user;
    User** users;
    bool printUser(QString,QString);
};

#endif // SHOWFRIENDSWINDOW_H
