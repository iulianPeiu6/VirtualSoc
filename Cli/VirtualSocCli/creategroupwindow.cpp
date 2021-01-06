#include "creategroupwindow.h"
#include "ui_creategroupwindow.h"

CreateGroupWindow::CreateGroupWindow(QWidget *parent, int _sd, User* _user) :
    QMainWindow(parent),
    ui(new Ui::CreateGroupWindow)
{
    sd=_sd;
    user=_user;
    ui->setupUi(this);
    drawCandidatesArea();
}

void CreateGroupWindow::drawCandidatesArea(){
    QString resp=sendMsg(sd,"7 " + QString::number(user->UserId));

    QStringList usersDetails = resp.split(QLatin1Char(' '));

    numOfUsers=usersDetails.count()/7;
    users= new User*[numOfUsers];

    verticalLayout=new QVBoxLayout();
    horizontalLayout = new QHBoxLayout*[numOfUsers];
    usernameLabel=new QLabel*[numOfUsers];
    selectCheckBox=new QCheckBox*[numOfUsers];

    for (int i=0;i<numOfUsers;i++){
        users[i]=new User(  usersDetails[i*7]+" "+
                            usersDetails[i*7+1]+" "+
                            usersDetails[i*7+2]+" "+
                            usersDetails[i*7+3]+" "+
                            usersDetails[i*7+4]+" "+
                            usersDetails[i*7+5]+" "+
                            usersDetails[i*7+6]);

        horizontalLayout[i]= new QHBoxLayout();
        usernameLabel[i] = new QLabel();
        selectCheckBox[i] =new QCheckBox();

        usernameLabel[i]->setText(usersDetails[i*7+1]);
        horizontalLayout[i]->addWidget(selectCheckBox[i]);
        horizontalLayout[i]->addWidget(usernameLabel[i]);


        verticalLayout->addLayout(horizontalLayout[i]);
    }
    verticalLayout->addStretch();
    ui->scrollAreaWidgetContents->setLayout(verticalLayout);
    ui->scrollAreaWidgetContents->show();
}
CreateGroupWindow::~CreateGroupWindow()
{
    delete ui;
}

void CreateGroupWindow::on_pushButton_clicked(){

    if (ui->lineEdit->text()==""){
        QMessageBox::warning(this,"Create Error","Please insert a group name!");
        return ;
    }
    QString membersIds="{";
    int groupSize=0;
    for (int i=0;i<numOfUsers;i++)
        if (selectCheckBox[i]->checkState()==Qt::Checked){
            groupSize++;
            membersIds=membersIds+QString::number(users[i]->UserId)+",";
        }
    membersIds=membersIds+QString::number(user->UserId)+"}";
    if (groupSize<2)
        QMessageBox::warning(this,"Create Error","Please select at least 2 group members!");
    else{
        QString resp=sendMsg(sd,"19 "+ui->lineEdit->text()+" "+membersIds);
        this->close();
    }
}
