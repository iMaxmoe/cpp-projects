#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "ui_loginwindow.h"
#include "masterpassword.h"
#include <QString>
#include <QMessageBox>

class RecordManager;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;
    MasterPassword* mp;
    QString masterPassoword; // 6 digit number
    QString inputPassword;

    void check_master_password();
    void enter(); // user correctly input the master keyword and press login button   

private slots:
    void on_loginButton_clicked();
};

#endif // LOGINWINDOW_H

