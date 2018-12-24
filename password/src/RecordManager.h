#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QString>
#include <vector>
#include "account.h"
#include "bank.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>

using namespace std;

class RecordManager
{
public:
    RecordManager();
    void update_record(Bank*); // write records into the file
    vector<Account*>& get_all_record() {return records;}

private:
    QString currentPath = QCoreApplication::applicationDirPath();
    vector<Account*> records; // each line "loginname:...accountname:...password:..."
    QString encryptRecords(QString s);
    QString decryptRecords(QString s);
    int BASE = 128;
};
#endif // RECORDMANAGER_H
