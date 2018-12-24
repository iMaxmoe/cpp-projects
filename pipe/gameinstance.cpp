#include <QFile>
#include <QString>
#include <QObject>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTextStream>
#include <ctype.h>
#include <QDebug>
#include <QQueue>
#include <QTime>
#include <QTimer>
#include <QCoreApplication>
#include "gameinstance.h"
#include "gamewindow.h"

const QString map_path = ":/resources/maps/maps.txt";

GameInstance::GameInstance(int _level, int _min_step):
    game_gui(new GameWindow(nullptr)),
    used_step(0),
    min_step(_min_step),
    level(_level),
    time(30),
    id(-1000),
    result(-1)
{
    game_gui -> show();
    game_gui -> set_lcd(GameWindow::USED_STEP_LCD, 0);
    game_gui -> set_lcd(GameWindow::MIN_STEP_LCD, _min_step == -1 ? 999 : _min_step);
    game_gui -> set_lcd(GameWindow::LEVEL_LCD, _level);
    game_gui -> set_lcd(GameWindow::TIMER, 30);
    load_map(_level);
    connect(game_gui -> get_done_button(), SIGNAL(clicked()), this, SLOT(on_done_button_clicked()));
    connect(game_gui -> restart(), SIGNAL(clicked()), this, SLOT(on_restart_clicked()));
    connect(game_gui -> timemode(), SIGNAL(clicked()), this, SLOT(on_timemode_clicked()));
    connect(game_gui, SIGNAL(closed()), this, SLOT(quit()));
    t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(terminate()));
}

void GameInstance::init_block(int _type, int _orientation, int _y, int _x)
{
    Block* ret = new Block(game_gui, _y, _x, this, _type, _orientation);
    connect(ret, SIGNAL(clicked()), ret, SLOT(pressed()));
    blocks[_y][_x] = ret;
}

void GameInstance::quit()
{
    emit game_over();
}

void GameInstance::load_map(int dest_level)
{
    QFile file(":/resources/maps/maps.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QChar map[128]; //8*8*2
    int num = 0;
    while (!in.atEnd()) {
        QChar temp = in.read(1).at(0);
        if(temp == '[') dest_level--;
        if(dest_level == 0) {
            if(temp.isDigit()) map[num++] = temp;
            if(temp == ']') break;
        }
    }

    int m = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            init_block(map[m].digitValue(),map[m+1].digitValue(), i, j);
            m+=2;
        }
    }
}

GameInstance::~GameInstance()
{
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++)
            delete blocks[i][j];
    }
    this->game_gui->~GameWindow();
}

void GameInstance::block_pressed(int y, int x)
{
    blocks[y][x]->rotate();
    if (blocks[y][x]->get_type()!= 4)
        used_step++;
    this->game_gui->set_lcd(GameWindow::USED_STEP_LCD, used_step);
}

void GameInstance::add_neighbors(QQueue<Block*> &series, QQueue<Block*> &q, bool (&checked)[MAP_SIZE][MAP_SIZE], bool &success, bool &end) {
    Block* temp = q.dequeue();
    series.enqueue(temp);
    int y = temp->get_y(), x = temp->get_x();
    if (temp->is_down_open()) {
        if(y == 7) {success = false; return;}
        else if(blocks[y+1][x]->is_up_open()) {
            if(!checked[y+1][x]) {
                q.enqueue(blocks[y+1][x]);
                checked[y+1][x] = true;
            }
        }
        else {success = false; return;}
    }
    if (temp->is_up_open()) {
        if(y == 0) {success = false; return;}
        else if(blocks[y-1][x]->is_down_open()) {
            if(!checked[y-1][x]) {
                q.enqueue(blocks[y-1][x]);
                checked[y-1][x] = true;
            }
        }
        else {success = false; return;}
    }
    if (temp->is_left_open()) {
        if (x == 0 && y == 0);
        else if(x == 0) {success = false; return;}
        else if(blocks[y][x-1]->is_right_open()) {
            if(!checked[y][x-1]) {
                q.enqueue(blocks[y][x-1]);
                checked[y][x-1] = true;
            }
        }
        else {success = false; return;}
    }
    if (temp->is_right_open()) {
        if (x == 7 && y == 7) end = true;
        else if(x == 7) {success = false; return;}
        else if(blocks[y][x+1]->is_left_open()) {
            if(!checked[y][x+1]) {
                q.enqueue(blocks[y][x+1]);
                checked[y][x+1] = true;
            }
        }
        else {success = false; return;}
    }
}

int GameInstance::get_result()
{
    bool end = false;
    bool success = true;
    bool checked[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++)
            checked[i][j] = false;
    }

    QQueue<Block*> q;
    if (blocks[0][0]->is_left_open()) {
        q.enqueue(blocks[0][0]);
    }
    else success = false;
    while (q.size() != 0) {
      if (success == false) break;
        add_neighbors(series,q,checked,success, end);
    }

    if (success && !end) result = -2;
    if (success && end) result = used_step;
    return result;
}

void GameInstance::flow() {
    Block* temp = series.dequeue();
    temp->set_highlighted(true);
    temp->set_image(temp->get_path());
}

void GameInstance::delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(200);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents);
}

void GameInstance::on_done_button_clicked()
{
    if (id != -1000) {killTimer(id); delete t;}
    result = get_result();
    if (result != -1 && result != -2) {
        while (series.size() != 0) {
           flow();
           delay();
        }
        this->game_gui->set_outlet(true);
        QMessageBox::information(nullptr, "Pipes", "Congratulations!");
    }
    else if (result == -2) QMessageBox::information(nullptr, "Pipes", "It seems that water can not flow into the outlet.\nGame over!");
    else QMessageBox::information(nullptr, "Pipes", "There is leakage in the maze.\nGame over!");
    game_over();
}

int GameInstance::fetch_result() {
    return result;
}

void GameInstance::on_restart_clicked() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++)
            delete blocks[i][j];
    };
    load_map(level);
    used_step = 0;
    game_gui->set_lcd(GameWindow::USED_STEP_LCD, 0);
}

void GameInstance::on_timemode_clicked() {
    game_gui->set_lcd(GameWindow::TIMER, time);
    id = startTimer(1000);
    t->start(time*1000);
}

void GameInstance::timerEvent(QTimerEvent* event) {
    game_gui->set_lcd(GameWindow::TIMER, --time);
}

void GameInstance::terminate(){
    killTimer(id);
    delete t;
    QMessageBox::information(nullptr, "Pipes", "Time out!\nYou Lose!");
    game_over();
}
