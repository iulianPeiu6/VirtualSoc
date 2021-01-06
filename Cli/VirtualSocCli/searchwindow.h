#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "cliLogic.h"
#include "showprofilewindow.h"

namespace Ui {
class searchWindow;
}

class searchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchWindow(QWidget *parent = nullptr, int _sd=0,User* _user=nullptr);



    ~searchWindow();

public slots:
    void search_action();

private:
    Ui::searchWindow *ui;
    ShowProfileWindow* showProfileWindow;
    int sd;
    QWidget* Parent;
    User* user;

    int numOfUsers;
    QVBoxLayout* verticalLayout;
    QHBoxLayout** horizontalLayout;
    QLabel** activeLabel;
    QLabel** usernameLabel;
    QPushButton** SeeProfile;
    bool printUser(QString, QString);
};

#endif // SEARCHWINDOW_H
