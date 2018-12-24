#include "account.h"
#include <QRegExp>
#include <QStringList>

Account::Account(QString l, QString a, QString p): loginName(l), accountName(a), password(p), height(0), left(nullptr), right(nullptr) {}

Account::Account(QString raw): height(0), left(nullptr), right(nullptr){
    QStringList temp = raw.split(' ', QString::SkipEmptyParts);
    this->loginName = temp.at(0);
    this->accountName = temp.at(1);
    this->password = temp.at(2);
}

QString Account::toString() {
    return loginName+" "+accountName;
}

