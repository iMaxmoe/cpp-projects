#include "AddWindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QRegExpValidator>
#include <QValidator>

AddWindow::AddWindow(QWidget *parent, Bank* bank) :
    QMainWindow(parent),
    ui(new Ui::AddWindow)
{
    ui->setupUi(this);
    myBank = bank;
    // maxlength restraint
    this->ui->password->setMaxLength(20);
    this->ui->reinPassword->setMaxLength(20);
    // input type constraint
    QRegExp regx("[a-zA-Z0-9]+$");
    checked = false;
    reinChecked = false;
    QValidator *validator = new QRegExpValidator(regx, this->ui->accountInput );
    this->ui->accountInput->setValidator( validator );
    QValidator *validator2 = new QRegExpValidator(regx, this->ui->loginInput );
    this->ui->loginInput->setValidator( validator2 );
    QRegExp regx1("[a-zA-Z0-9,./?;:`~!@#$%^&*-_=+\\|<>]+$");
    QValidator *validator3 = new QRegExpValidator(regx1, this->ui->password );
    this->ui->password->setValidator( validator3 );
    connect(this->ui->createButton,&QPushButton::clicked,this,&AddWindow::added);
    connect(this->ui->revealInput,&QPushButton::clicked,this,&AddWindow::revealInput);
    connect(this->ui->revealReinput,&QPushButton::clicked,this,&AddWindow::revealReinput);
}

AddWindow::~AddWindow()
{
    delete this;
}

void AddWindow::closeEvent(QCloseEvent* event){
    emit closed();
}
void AddWindow::added(){
    QString login = this->ui->loginInput->text();
    QString account = this->ui->accountInput->text();
    QString password = this->ui->password->text();
    QString reinPassword = this->ui->reinPassword->text();
    if (login==""||account==""||password==""||reinPassword==""){
        QMessageBox::information(this,tr("Warning"),tr("Please Fill in All the Blanks!"));
    }
    else if (password != reinPassword){
        QMessageBox::information(this,tr("Warning"),tr("Two Passwords Input are Different!"));
    }
    else{
        Account* temp = nullptr;
        myBank->find_record(login, temp);
        if (temp) {
            QMessageBox::information(this,tr("Reminder"), tr("You cannot add the same account twice!"));
            return;
        }
        emit saved(login, account, password); // send to listwindow to call it to show again
        QMessageBox::information(this,tr("Reminder"), tr("Account Successfully Added!"));
        this->hide();
        this->closed();
    }
}
void AddWindow::revealInput(){
    if (!checked){
        ui->revealInput->setChecked(true);
        checked = true;
    }
    else{
        ui->revealInput->setChecked(false);
        checked = false;
    }
    if (this->ui->password->echoMode()==QLineEdit::Password)
        this->ui->password->setEchoMode(QLineEdit::Normal); // before click it's password, change to normal
    else
        this->ui->password->setEchoMode(QLineEdit::Password);
}
void AddWindow::revealReinput(){
    if (!reinChecked){
        ui->revealReinput->setChecked(true);
        reinChecked = true;
    }

    else{
        ui->revealReinput->setChecked(false);
        reinChecked = false;
    }
    if (this->ui->reinPassword->echoMode()==QLineEdit::Password)
        this->ui->reinPassword->setEchoMode(QLineEdit::Normal);// before click it's password, change to normal
    else
        this->ui->reinPassword->setEchoMode(QLineEdit::Password);
}
