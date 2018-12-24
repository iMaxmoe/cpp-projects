#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <QPushButton>

using std::string;

class GameInstance;

class Block : public QPushButton
{
    Q_OBJECT

 public:
    Block(QWidget* _parent = nullptr,
          int _y = 0,
          int _x = 0,
          GameInstance* _host_game = nullptr,
          int _type = 0,
          int _orientation = 0);

    void rotate();
    void set_highlighted(bool value);
    void set_image(string path);

    string get_path();
    bool get_highlighted() const;
    int get_orientation() const;
    int get_type() const;
    int get_x() const;
    int get_y() const;
    bool is_right_open();
    bool is_left_open();
    bool is_up_open();
    bool is_down_open();
    bool check_right_neighbor(Block*);
    bool check_left_neighbor(Block*);
    bool check_up_neighbor(Block*);
    bool check_down_neighbor(Block*);

 private:
    static const int NORMAL_X = 117;
    static const int NORMAL_Y = 146;
    static const int BUTTON_HEIGHT = 58;
    static const int BUTTON_WIDTH = 58;

    GameInstance *host_game;
    int x;
    int y;

    bool highlighted;
    int orientation;
    int type;

 private slots:
    void pressed();
};

#endif // BLOCK_H
