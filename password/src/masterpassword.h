#ifndef MASTERPASSWORD_H
#define MASTERPASSWORD_H

#include <QString>
#include <vector>
#include "account.h"
#include "bank.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>

using namespace std;

class MasterPassword
{
public:
    MasterPassword();
    void update_master_password(); // write master password into the file
    void change_master_password(QString newPassword) {masterPassword = newPassword;}
    QString get_master_password() {return masterPassword;}

private:
    QString currentPath = QCoreApplication::applicationDirPath();
    QString masterPassword;
    QString encryptRecords(QString s);
    QString decryptRecords(QString s);
    int BASE = 128;
};

#endif // MASTERPASSWORD_H
