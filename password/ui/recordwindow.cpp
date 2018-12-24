#include "RecordWindow.h"
#include <QCloseEvent>
#include <QMessageBox>

RecordWindow::RecordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecordWindow)
{
    ui->setupUi(this);
    connect(this->ui->backButton,&QPushButton::clicked,this,&RecordWindow::backButton_clicked);
    connect(this->ui->deleteButton,&QPushButton::clicked,this,&RecordWindow::deleteButton_clicked);
}

RecordWindow::~RecordWindow() = default;

void RecordWindow::closeEvent(QCloseEvent* event){
    emit RecordClosed();
}

void RecordWindow::backButton_clicked(){
    emit RecordClosed();
    this->hide();
}
void RecordWindow::deleteButton_clicked(){
    QString name = ui->loginLabel->text();
    emit deleted(name);//send to ListWindow
    QMessageBox mb;
    mb.setText("Login Successufully Deleted!");
    mb.exec();
    this->hide();
}

void RecordWindow::editButton_clicked(){}

void RecordWindow::change_login_name_label(QString s) {
    ui->loginLabel->setText(s);
}

void RecordWindow::change_account_label(QString s) {
    ui->accountLabel->setText(s);
}

void RecordWindow::change_password_label(QString s) {
    ui->passwordLabel->setText(s);
}
