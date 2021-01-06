#ifndef EXPLOREWINDOW_H
#define EXPLOREWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QHBoxLayout>

namespace Ui {
class ExploreWindow;
}

class ExploreWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExploreWindow(QWidget *parent = nullptr, int _sd=0,User* _user=nullptr);
    int sd;
    QWidget* Parent;
    User* user;
    ~ExploreWindow();

private slots:
    void search_action(int numOfUsers,QHBoxLayout* horizontalLayout[]);

private:
    Ui::ExploreWindow *ui;
};

#endif // EXPLOREWINDOW_H
