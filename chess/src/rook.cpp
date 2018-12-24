# include "Rook.h"

char Rook::getImage() const {return (player == BLACK)? IMAGE_BLACK:IMAGE_WHITE;}

void Rook::calculatePotentialMoves(bool potentialMoves[8][8]) const {
    for (int i = -1 ; i <= 1; i+=2) {
        for (int n = 1 ; n < 8; n++) {
            if (checkPotential(row+n*i, col)) {
                potentialMoves[row+n*i][col] = true;
                if ((*chessBoard)[row+i*n][col] != nullptr) break;
            }
            else break;
        }
        for (int n = 1 ; n < 8; n++) {
            if (checkPotential(row, col+n*i)) {
                potentialMoves[row][col+n*i] = true;
                if ((*chessBoard)[row][col+n*i] != nullptr) break;
            }
            else break;
        }
    }
}

ChessPiece* Rook::move(int row, int col) {
    // Change the firstMoved status of Rock
    if(!hasMoved) hasMoved = true;
    // the enemy chess is eaten
    (*chessBoard)[row][col] = this;
    // remove current one
    (*chessBoard)[this->row][this->col] = nullptr;
    // change the current chesspiece
    this->row = row; this->col = col;
}
