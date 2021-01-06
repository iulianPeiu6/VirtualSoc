#ifndef SENDMESSAGEWINDOW_H
#define SENDMESSAGEWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "group.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

namespace Ui {
class SendMessageWindow;
}

class SendMessageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SendMessageWindow(QWidget *parent = nullptr, int _sd=0,User* _user=nullptr,Group* _group=nullptr);
    ~SendMessageWindow();

private slots:
    void on_send_pushButton_clicked();
    void updateMsgs();

private:
    Ui::SendMessageWindow *ui;
    int sd;
    int lastMsgId;
    QString lastData;
    QWidget* Parent;
    User* user;
    Group* group;
    QVBoxLayout* verticalLayout;
};

#endif // SENDMESSAGEWINDOW_H
