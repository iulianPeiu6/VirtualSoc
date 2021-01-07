#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "home.h"
#include "register.h"
#include "user.h"
#include "guesthomewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int _sd=0);
    ~MainWindow();

private slots:

    void on_loginButton_clicked();

    void on_create_accButton_clicked();

    void on_guestButton_clicked();

private:
    Ui::MainWindow *ui;
    int sd;
    User* user;
    Home* home;
    Register* _register;
    GuestHomeWindow* guestHomeWindow;
};
#endif // MAINWINDOW_H
