#include "sendmessagewindow.h"
#include "ui_sendmessagewindow.h"
#include "cliLogic.h"
#include <QtDebug>

SendMessageWindow::SendMessageWindow(QWidget *parent, int _sd,User* _user,Group* _group) :
    QMainWindow(parent),
    ui(new Ui::SendMessageWindow)
{
    sd=_sd;
    user=_user;
    group=_group;
    lastMsgId=-1;
    lastData="";
    ui->setupUi(this);

    QString allMsgs=sendMsg(sd,"8 "+QString::number(group->GroupId));
    QStringList msgs=allMsgs.split(QLatin1Char('\n'));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMsgs()));
    timer->start(1000);

    verticalLayout= new QVBoxLayout();
    verticalLayout->setSpacing(0);
    for (int i=0;i<msgs.count()-1;i++){
        QStringList msg=msgs[i].split(QLatin1Char(' '));
        QString msg_txt;
        for (int j=3;j<msg.count();j++)
            msg_txt=msg_txt+msg[j]+" ";

        QLabel* usernameLabel = new QLabel();
        QLabel* dataLabel = new QLabel();
        QLabel* msg_txtLabel = new QLabel();
        usernameLabel->setText("["+msg[2]+"]");
        dataLabel->setText(msg[1]);
        msg_txtLabel->setText(msg_txt);
        if (msg[2]==user->Username){
            usernameLabel->setStyleSheet("color: green");
            usernameLabel->setAlignment(Qt::AlignRight);
            msg_txtLabel->setAlignment(Qt::AlignRight);
        }
        else{
            usernameLabel->setStyleSheet("color: blue");
            usernameLabel->setAlignment(Qt::AlignLeft);
            msg_txtLabel->setAlignment(Qt::AlignLeft);
        }

        dataLabel->setAlignment(Qt::AlignCenter);
        if (lastMsgId<msg[0].toInt())
            lastMsgId=msg[0].toInt();

        if (lastData!=msg[1]){
            verticalLayout->addWidget(dataLabel);
            lastData=msg[1];
        }
        verticalLayout->addWidget(usernameLabel);
        verticalLayout->addWidget(msg_txtLabel);
    }

    verticalLayout->addStretch();
    ui->scrollAreaWidgetContents->setLayout(verticalLayout);
    ui->scrollAreaWidgetContents->show();

}

SendMessageWindow::~SendMessageWindow(){
    delete ui;
}

void SendMessageWindow::on_send_pushButton_clicked(){
    if (ui->message_lineEdit->text()!=""){
        QString rasp=sendMsg(sd,"9 "+QString::number(group->GroupId)+" "+QString::number(user->UserId)+" "+ui->message_lineEdit->text());
        if (rasp!="Message succefully sent!")
            qDebug() <<"Sending message error!";
        else
            ui->message_lineEdit->setText("");
    }
}
void SendMessageWindow::updateMsgs(){
    QString allMsgs=sendMsg(sd,"8 "+QString::number(group->GroupId));
    QStringList msgs=allMsgs.split(QLatin1Char('\n'));

    for (int i=0;i<msgs.count()-1;i++){
        QStringList msg=msgs[i].split(QLatin1Char(' '));
        if (lastMsgId<msg[0].toInt()){

            QString msg_txt;
            for (int j=3;j<msg.count();j++)
                msg_txt=msg_txt+msg[j]+" ";

            QLabel* usernameLabel = new QLabel();
            QLabel* dataLabel = new QLabel();
            QLabel* msg_txtLabel = new QLabel();
            usernameLabel->setText("["+msg[2]+"]");
            dataLabel->setText(msg[1]);
            msg_txtLabel->setText(msg_txt);
            dataLabel->setAlignment(Qt::AlignCenter);
            if (msg[2]==user->Username){
                usernameLabel->setStyleSheet("color: green");
                usernameLabel->setAlignment(Qt::AlignRight);
                msg_txtLabel->setAlignment(Qt::AlignRight);
            }
            else{
                usernameLabel->setStyleSheet("color: blue");
                usernameLabel->setAlignment(Qt::AlignLeft);
                msg_txtLabel->setAlignment(Qt::AlignLeft);
            }

            if (lastMsgId<msg[0].toInt())
                lastMsgId=msg[0].toInt();
            if (lastData!=msg[1]){
                verticalLayout->addWidget(dataLabel);
                lastData=msg[1];
            }

            verticalLayout->addWidget(usernameLabel);
            verticalLayout->addWidget(msg_txtLabel);
            verticalLayout->addStretch();

            usernameLabel->show();
            msg_txtLabel->show();
        }
    }
}
