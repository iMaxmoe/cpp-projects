#include <ChangeMasterPassword.h>
#include <QCloseEvent>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QValidator>

ChangeMasterPassword::ChangeMasterPassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterWindow)
{
    ui->setupUi(this);
    // length constraint
    this->ui->password->setMaxLength(6);
    this->ui->reinPassword->setMaxLength(6);
    // only integers
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this->ui->password );
    this->ui->password->setValidator( validator );
    QValidator *validator2 = new QRegExpValidator(regx, this->ui->reinPassword );
    this->ui->reinPassword->setValidator( validator2 );
    checked = false;
    reinChecked = false;

    connect(this->ui->confirmButton,&QPushButton::clicked,this,&ChangeMasterPassword::confirm_clicked);
    connect(this->ui->revealInput,&QPushButton::clicked,this,&ChangeMasterPassword::revealInput);
    connect(this->ui->revealReinput,&QPushButton::clicked,this,&ChangeMasterPassword::revealReinput);
}

ChangeMasterPassword::~ChangeMasterPassword() = default;

void ChangeMasterPassword::confirm_clicked(){
    QString masterPassword = this->ui->password->text();
    QString masterReinpassword = this->ui->reinPassword->text();
    if (masterPassword==""||masterReinpassword==""){
        QMessageBox::information(this,tr("warning"),tr("Please Fill in All the Blanks!"));
    }
    else if (masterPassword != masterReinpassword){
        QMessageBox::information(this,tr("warning"),tr("Two Passwords Input are different!"));
    }
    else if (masterPassword.length() != 6){
        QMessageBox::information(this,tr("warning"),tr("Master Password Should Have Exactly 6 Digits!"));
    }
    else{
        emit confirmed(masterPassword); // send to listwindow to call it to show again
        delete this;
    }
}

void ChangeMasterPassword::closeEvent(QCloseEvent* event){
    emit masterClosed();
}

void ChangeMasterPassword::revealInput(){
    if (checked){
        ui->revealInput->setChecked(false);
        checked = false;
    }
    else{
        ui->revealInput->setChecked(true);
        checked = true;
    }
    if (this->ui->password->echoMode()==QLineEdit::Password)
        this->ui->password->setEchoMode(QLineEdit::Normal); // before click it's password, change to normal
    else
        this->ui->password->setEchoMode(QLineEdit::Password);
}
void ChangeMasterPassword::revealReinput(){
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
