#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QFont>

#include "Player.h"

namespace Ui {
class GameWindow;
}

class Square;
class ChessGame;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr, ChessGame* _chess_game=nullptr);
    ~GameWindow();

    ChessGame* get_chess_game() const;
    void set_current_player(Player player);
    Square* get_square(int row, int col) const;
    void set_highlighted(int row, int col, bool value, std::string color="black"); // set which square to be highlighted
    void reset_highlighted();
    void set_piece(int row, int col, char i); // set the text(i.e. icon) of the chess piece
    void show_checkmate_label();
    void show_stalemate_label();
    char get_promotion_choice(Player player);

private:
    void closeEvent(QCloseEvent *event);
    void make_grid();

    Ui::GameWindow *ui; // Main UI window
    Square* square[8][8]; // Square has interactive functions
    ChessGame* chess_game; // Game logic

signals:
    void closed();
};

#endif // GAMEWINDOW_H
