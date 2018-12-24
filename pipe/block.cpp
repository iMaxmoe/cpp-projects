#include "block.h"
#include "gameinstance.h"
#include <string>
#include <sstream>
#include <QPushButton>
#include <QDebug>

using std::string;
using std::ostringstream;

Block::Block(QWidget *_parent,
             int _y,
             int _x,
             GameInstance *_host_game,
             int _type,
             int _orientation):
    QPushButton(_parent),
    host_game(_host_game),
    x(_x),
    y(_y),
    highlighted(false),
    orientation(_orientation),
    type(_type)
{
    setText("");
    setAutoFillBackground(true);
    setFlat(true);
    setGeometry(QRect(NORMAL_X + BUTTON_WIDTH * _x, NORMAL_Y + BUTTON_HEIGHT * _y, BUTTON_WIDTH, BUTTON_HEIGHT));
    setStyleSheet("border: none");
    set_image(get_path());
    setVisible(true);
}

string Block::get_path()
{
    ostringstream buf;
    if (highlighted) {
        buf << ":/resources/images/blocks_jpg/block" << type << "_" << orientation << "_f.jpg";
    } else {
        buf << ":/resources/images/blocks_jpg/block" << type << "_" << orientation << ".jpg";
    }
    return buf.str();
}

void Block::set_image(string path)
{
    setStyleSheet(QString::fromStdString("border-image: url(\"" + path + "\");"));
}

void Block::pressed()
{
    host_game -> block_pressed(y, x);
}

void Block::rotate()
{
    switch (orientation) {
        case 0: orientation = 1; break;
        case 1: orientation = 2; break;
        case 2: orientation = 3; break;
        case 3: orientation = 0; break;
    }
    set_image(get_path());
}

void Block::set_highlighted(bool value)
{
    highlighted = value;
}

bool Block::get_highlighted() const
{
    return highlighted;
}

int Block::get_orientation() const
{
    return orientation;
}

int Block::get_type() const
{
    return type;
}

bool Block::is_right_open() {
    if ((type == 0 && orientation == 0) || (type == 0 && orientation == 1) ||
        (type == 0 && orientation == 3) || (type == 1 && orientation == 0) ||
        (type == 1 && orientation == 1) || (type == 2 && orientation == 0) ||
        (type == 2 && orientation == 2) || (type == 3))
    return true;
    return false;
}

bool Block::is_left_open() {
    if ((type == 0 && orientation == 1) || (type == 0 && orientation == 2) ||
        (type == 0 && orientation == 3) || (type == 1 && orientation == 2) ||
        (type == 1 && orientation == 3) || (type == 2 && orientation == 0) ||
        (type == 2 && orientation == 2) || (type == 3))
    return true;
    return false;
}

bool Block::is_up_open() {
    if ((type == 0 && orientation == 0) || (type == 0 && orientation == 2) ||
        (type == 0 && orientation == 3) || (type == 1 && orientation == 0) ||
        (type == 1 && orientation == 3) || (type == 2 && orientation == 1) ||
        (type == 2 && orientation == 3) || (type == 3))
    return true;
    return false;
}

bool Block::is_down_open() {
    if ((type == 0 && orientation == 0) || (type == 0 && orientation == 1) ||
        (type == 0 && orientation == 2) || (type == 1 && orientation == 1) ||
        (type == 1 && orientation == 2) || (type == 2 && orientation == 1) ||
        (type == 2 && orientation == 3) || (type == 3))
    return true;
    return false;
}

int Block::get_x() const {return x;}
int Block::get_y() const {return y;}

