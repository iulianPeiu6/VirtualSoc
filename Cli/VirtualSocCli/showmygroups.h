#ifndef SHOWMYGROUPS_H
#define SHOWMYGROUPS_H

#include <QMainWindow>
#include "user.h"
#include "group.h"
#include "sendmessagewindow.h"
#include "cliLogic.h"
#include <QPushButton>

namespace Ui {
class ShowMyGroups;
}

class ShowMyGroups : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowMyGroups(QWidget *parent = nullptr, int _sd=0,User* _user=nullptr);
    ~ShowMyGroups();

private:
    Ui::ShowMyGroups *ui;
    SendMessageWindow* sendMessageWindow;
    int sd;
    User* user;
    Group** groups;
    QWidget* Parent;
    QVBoxLayout* verticalLayout;

    void drawGroupsArea();
};

#endif // SHOWMYGROUPS_H
