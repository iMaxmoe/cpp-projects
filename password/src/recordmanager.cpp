#include "RecordManager.h"
#include "infint.h"
#include "rsa.h"
#include <QDebug>

QString RecordManager::encryptRecords(QString s){
    RSA rsa;
    InfInt c = 0;
    for(int i = 0; i < s.length(); i++){
        c = c * BASE + s[i].unicode();
    }
    InfInt m = rsa.encrypt(c);
    return m.toQString();
}

QString RecordManager::decryptRecords(QString s){
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

RecordManager::RecordManager(): records(){
    QFile record(currentPath+"/record.txt");
    record.open(QIODevice::ReadWrite);
    // Read the records and store them in the library
    while (!record.atEnd()) {
        QString temp = record.readLine();
        temp = temp.simplified();
        QString tempPassword = record.readLine();
        tempPassword = tempPassword.simplified();
        QString combined = temp+" "+decryptRecords(tempPassword);
        Account* ac = new Account(combined);
        records.push_back(ac);
    }
}

void print_vector(vector<Account*> v) {
    for (int i = 0; i < v.size(); i++) {
        qDebug() << v[i];
    }
}

void RecordManager::update_record(Bank* bk) {
    QFile record(currentPath+"/record.txt");
    record.open(QIODevice::ReadWrite| QIODevice::Truncate);
    records.clear();
    bk->output_bank(records);
    QTextStream out(&record);
    for (unsigned int i = 0; i < records.size(); i++) {
        QString temp = records.at(i)->toString();
        out << temp << "\n";
        QString tempPassword = records.at(i)->get_password();
        out << encryptRecords(tempPassword) << "\n";
    }
    record.close();
}
