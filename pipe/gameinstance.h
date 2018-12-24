#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <QString>
#include <QObject>
#include <QQueue>
#include "block.h"

class GameWindow;

class GameInstance : public QObject
{
    Q_OBJECT

 public:
    GameInstance(int _level, int _min_step);
    ~GameInstance();
    void block_pressed(int y, int x);
    int get_result();
    static const int MAP_SIZE = 8;
    void add_neighbors(QQueue<Block*> &series, QQueue<Block*> &q, bool (&checked)[MAP_SIZE][MAP_SIZE], bool &, bool &);
    int fetch_result();
    void restart();

 private:
    static const QString map_path;
    Block *blocks[MAP_SIZE][MAP_SIZE]; // 2D array of blocks
    GameWindow *game_gui;
    int used_step;
    int min_step;
    int level;
    int time;
    int id;
    int result;
    QTimer* t;
    QQueue<Block*> series;
    void init_block(int _type, int _orientation, int _y, int _x);
    void load_map(int dest_level);
    void delay();

 signals:
    void game_over();

 private slots:
    void on_restart_clicked();
    void on_done_button_clicked();
    void on_timemode_clicked();
    void quit();
    void flow();
    void terminate();

 protected:
    void timerEvent(QTimerEvent *event);
};


#endif // GAMEINSTANCE_H
