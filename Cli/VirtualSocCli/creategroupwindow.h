#ifndef CREATEGROUPWINDOW_H
#define CREATEGROUPWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "cliLogic.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QMessageBox>

namespace Ui {
class CreateGroupWindow;
}

class CreateGroupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateGroupWindow(QWidget *parent = nullptr, int _sd=0, User* _user=nullptr);
    ~CreateGroupWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateGroupWindow *ui;
    int sd;
    User* user;
    int numOfUsers;
    User** users;

    QVBoxLayout* verticalLayout;
    QHBoxLayout** horizontalLayout;
    QLabel** usernameLabel;
    QCheckBox** selectCheckBox;
    void drawCandidatesArea();
};

#endif // CREATEGROUPWINDOW_H
