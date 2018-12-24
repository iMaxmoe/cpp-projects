#include "LoginWindow.h"
#include "ListWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow),
    mp(new MasterPassword),
    inputPassword()
{
    ui->setupUi(this);
    ui->masterPassword->setPlaceholderText("Input your master password: ");
    masterPassoword = mp->get_master_password();
}

LoginWindow::~LoginWindow() // login window will be deleted when we leave list window
{
    delete mp;
    delete ui;
}

void LoginWindow::enter(){
    QMessageBox::information(this,tr("Reminder"), tr("It may take some time to login..."));
    ListWindow* listWindow = new ListWindow;
    listWindow->show();
    delete this;
}

void LoginWindow::on_loginButton_clicked(){
    // check whether the input master password is correct
    inputPassword = ui->masterPassword->text();
    check_master_password();
}

void LoginWindow::check_master_password() {
    QMessageBox msb;
    //connect(msb, &LoginWindow::msgbox_closed, this, &LoginWindow::msgbox_closed_handler);
    if (masterPassoword == nullptr) {
        msb.setText("First Time Log in. Please Change the Master Password ASAP.");
        msb.exec();
        enter();
    }
    else if (masterPassoword != inputPassword) {
        msb.setText("Invalid Master Password!");
        msb.exec();
    }
    else
        enter();
}
