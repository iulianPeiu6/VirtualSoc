#ifndef UPDATEUSERINFO_H
#define UPDATEUSERINFO_H

#include <QMainWindow>
#include "user.h"


namespace Ui {
class UpdateUserInfo;
}

class UpdateUserInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdateUserInfo(QWidget *parent = nullptr, int _sd=0, User* _user=nullptr);

    ~UpdateUserInfo();

signals:
    void userDetailsChanged(User* _user);

private slots:
    void on_back_pushButton_clicked();
    void on_submit_pushButton_clicked();


private:
    Ui::UpdateUserInfo *ui;
    QWidget *Parent;
    int sd;
    User* user;
    QString validate(QString ,QString ,QString );
};

#endif // UPDATEUSERINFO_H
