#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QString>

class Account {
    QString loginName = nullptr;
    QString accountName = nullptr;
    QString password = nullptr;

public:
    Account* left;
    Account* right;
    Account(QString l, QString a, QString p); // create account from addWindow
    Account(QString); // read from the record and create new account
    QString& get_login_name() {return loginName;}
    QString& get_account_name() {return accountName;}
    QString& get_password() {return password;}
    QString toString();
    int height;
};
#endif // ACCOUNT_H
