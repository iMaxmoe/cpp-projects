#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>

#include "recordmanager.h"

const QString RecordManager::record_dir =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/comp2012h_pipes";
const QString RecordManager::record_path =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/comp2012h_pipes/record.txt";

int RecordManager::num_of_levels = 0;

RecordManager::RecordManager()
{
    if (!QDir(record_path).exists()){
        QDir().mkpath(record_path);
        QFile file(record_path);
        file.open(QIODevice::ReadWrite);
        QTextStream writer(&file);
        for (int i = 0; i < MAX_LEVEL; i++)
            writer << "-1"<< endl;
        file.close();
    }
    QFile file(record_path);
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);
    int i = 0;
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        records[i++] = line.toInt();
        num_of_levels++;
    }
    file.close();
}

int RecordManager::get_record(int level)
{
    return records[level-1];
}

int RecordManager::get_num_of_levels()
{
    return num_of_levels;
}

void RecordManager::update_record(int level, int value)
{
    records[level-1] = value;
    QFile file(record_path);
    file.open(QIODevice::ReadWrite);
    file.resize(0);
    QTextStream out(&file);
    for (int i = 0; i < MAX_LEVEL; i++) {
        out << records[i]<< endl;
    }
    file.close();
}
