#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include "home.h"

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr, int _sd=0);

    ~Register();

private slots:
    void on_registerButton_clicked();

    void on_back_pushButton_clicked();

private:
    Ui::Register *ui;
    int sd;
    QWidget *Parent;

    Home* home;
};

#endif // REGISTER_H
