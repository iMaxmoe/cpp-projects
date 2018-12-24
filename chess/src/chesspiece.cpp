#include "ChessPiece.h"

ChessPiece::ChessPiece(Player player, int row, int col, ChessPiece* (*chessBoard)[8][8])
: player(player), row(row), col(col), previousRow(row), previousCol(col),
  chessBoard(chessBoard){}

int ChessPiece::getRow() const {return row;}
int ChessPiece::getCol() const {return col;}
bool ChessPiece::isEnemyChessPiece(const ChessPiece* const chessPiece) const {
    return (chessPiece->player == this->player)? false: true;
}

bool ChessPiece::checkPotential(int row, int col) const {
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;
    if ((*chessBoard)[row][col] == nullptr || isEnemyChessPiece((*chessBoard)[row][col]))
        return true;
    return false;
}

ChessPiece* ChessPiece::move(int row, int col) {
    // the enemy chess is eaten
    (*chessBoard)[row][col] = this;
    // remove current one
    (*chessBoard)[this->row][this->col] = nullptr;
    // change the current chesspiece
    this->row = row; this->col = col;
}

void ChessPiece::potentialMove(int row, int col) { // shallow move LOL
    // store previous info
    previousRow = this->row; previousCol = this->col;
    potentialCapturedChessPiece = (*chessBoard)[row][col];
    // move as usual
    (*chessBoard)[row][col] = this;
    (*chessBoard)[this->row][this->col] = nullptr;
    this->row = row; this->col = col;
}

void ChessPiece::undoPotentialMove() {
    (*chessBoard)[row][col] = potentialCapturedChessPiece;
    (*chessBoard)[previousRow][previousCol] = this;
    this->row = previousRow; this->col = previousCol;
}
