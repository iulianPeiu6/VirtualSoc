#ifndef GUESTHOMEWINDOW_H
#define GUESTHOMEWINDOW_H

#include <QMainWindow>
#include "register.h"

namespace Ui {
class GuestHomeWindow;
}

class GuestHomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuestHomeWindow(QWidget *parent = nullptr, int _sd=0);
    ~GuestHomeWindow();

private slots:
    void on_pushButton_clicked();

    void on_back_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GuestHomeWindow *ui;
    Register* _register;
    searchWindow* _searchWindow;
    QWidget* Parent;
    int sd;
};

#endif // GUESTHOMEWINDOW_H
