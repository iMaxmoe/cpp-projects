#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QString>

class RecordManager
{
 public:
    RecordManager();
    int get_record(int level);
    int get_num_of_levels();
    void update_record(int level, int value);

 private:
    static const int MAX_LEVEL = 3;
    static int num_of_levels;
    static const QString record_dir;
    static const QString record_path;
    int records[MAX_LEVEL + 1];
};

#endif // RECORDMANAGER_H
