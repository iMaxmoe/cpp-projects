#include "masterpassword.h"
#include "infint.h"
#include "rsa.h"

MasterPassword::MasterPassword() {
    QFile mp(currentPath+"/masterpassword.txt");
    mp.open(QIODevice::ReadWrite);
    // First read the master password
    if (mp.atEnd()) masterPassword = nullptr;
    else masterPassword = decryptRecords(mp.readLine().simplified());
}

QString MasterPassword::encryptRecords(QString s){
    RSA rsa;
    InfInt c = 0;
    for(int i = 0; i < s.length(); i++){
        c = c * BASE + s[i].unicode();
    }
    InfInt m = rsa.encrypt(c);
    return m.toQString();
}

QString MasterPassword::decryptRecords(QString s){
    RSA rsa;
    InfInt c, m = 0;
    QString ans = "";
    for(int i = 0; i < s.length(); i++){
        m = m * 10 + (s[i].unicode() - '0');
    }
    c = rsa.decrypt(m);
    while(c > 0){
        QChar ch = (c % BASE).toInt();
        ans = ans + ch;
        c /= BASE;
    }
    QString rtn = "";
    for(int i = ans.length() - 1; i >= 0; i--){
        rtn = rtn + ans[i];
    }
    return rtn;
}

void MasterPassword::update_master_password() {
    QFile mp(currentPath+"/masterpassword.txt");
    mp.open(QIODevice::ReadWrite | QIODevice::Truncate);
    QTextStream out(&mp);
    out << encryptRecords(masterPassword);
    mp.close();
}
