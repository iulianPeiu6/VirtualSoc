#ifndef CREATEPOSTWINDOW_H
#define CREATEPOSTWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QMessageBox>
#include "cliLogic.h"

namespace Ui {
class CreatePostWindow;
}

class CreatePostWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreatePostWindow(QWidget *parent = nullptr, int _sd=0, User* _user=nullptr);
    ~CreatePostWindow();

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::CreatePostWindow *ui;

    int sd;
    QWidget *Parent;
    User* user;
    QString validate(QString ,QString );
};

#endif // CREATEPOSTWINDOW_H
