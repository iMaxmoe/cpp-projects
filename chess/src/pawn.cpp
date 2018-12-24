#include "Pawn.h"

char Pawn::getImage() const {return (player == BLACK)? IMAGE_BLACK:IMAGE_WHITE;}

void Pawn::calculatePotentialMoves(bool potentialMoves[8][8]) const {
    int dir = (player == BLACK)? -1: 1;
    if (!(row+dir < 0 || row+dir > 7 || col < 0 || col > 7) && (*chessBoard)[row+dir][col] == nullptr) {
        potentialMoves[row+dir][col] = true;
        // First Move
        if (!hasMoved && !(row+2*dir < 0 || row+2*dir > 7) && (*chessBoard)[row+2*dir][col]==nullptr) {
            potentialMoves[row+2*dir][col] = true;
        }
    }
    calculatePotentialCaptures(potentialMoves);
}

void Pawn::calculatePotentialCaptures(bool potentialCaptures[8][8]) const {
    int dir = (player == BLACK)? -1: 1;
    if (!(row+dir < 0 || row+dir > 7 || col-1 < 0 || col-1 > 7) && (*chessBoard)[row+dir][col-1] != nullptr && isEnemyChessPiece((*chessBoard)[row+dir][col-1]))
        potentialCaptures[row+dir][col-1] = true;
    if (!(row+dir < 0 || row+dir > 7 || col+1 < 0 || col+1 > 7) && (*chessBoard)[row+dir][col+1] != nullptr && isEnemyChessPiece((*chessBoard)[row+dir][col+1]))
        potentialCaptures[row+dir][col+1] = true;
    if (firstMoved) {
        potentialCaptures[rowEnPassant][colEnPassant] = true;
    }
}

bool Pawn::hasCapturedEnPassant() const {
    return firstMoved;
}

void Pawn::passTurnEnPassant() {
    firstMoved = false;
    enpassanted = nullptr;
}

ChessPiece* Pawn::move(int row, int col) {
    int i = (player == WHITE)? 1:-1;

    // mark as potential enpassanted
    if (!hasMoved) {
        hasMoved = true;
        if (this->row+2*i == row) {
            // check whether there are enemy pawn at enpassant position
            // rowEnPassant records where to go if choose to perform enpassant
            if ((*chessBoard)[row][col-1]!=nullptr && isEnemyChessPiece((*chessBoard)[row][col-1]) && (*chessBoard)[row][col-1]->isPawn()) {
                dynamic_cast<Pawn*>((*chessBoard)[row][col-1])->rowEnPassant = row-i;
                dynamic_cast<Pawn*>((*chessBoard)[row][col-1])->colEnPassant = col;
                dynamic_cast<Pawn*>((*chessBoard)[row][col-1])->firstMoved = true;
                dynamic_cast<Pawn*>((*chessBoard)[row][col-1])->enpassanted = this;
                this->potentiallyCaptured = true;
                this->enpassantedBy1 = dynamic_cast<Pawn*>((*chessBoard)[row][col-1]);
            }
            if ((*chessBoard)[row][col+1]!=nullptr && isEnemyChessPiece((*chessBoard)[row][col+1])&& (*chessBoard)[row][col+1]->isPawn()) {
                dynamic_cast<Pawn*>((*chessBoard)[row][col+1])->rowEnPassant = row-i;
                dynamic_cast<Pawn*>((*chessBoard)[row][col+1])->colEnPassant = col;
                dynamic_cast<Pawn*>((*chessBoard)[row][col+1])->firstMoved = true;
                dynamic_cast<Pawn*>((*chessBoard)[row][col+1])->enpassanted = this;
                this->potentiallyCaptured = true;
                this->enpassantedBy2 = dynamic_cast<Pawn*>((*chessBoard)[row][col+1]);
            }
        }
    }

    // the enemy chess is eaten (regular)
    (*chessBoard)[row][col] = this;

    // choose to use EnPassant
    if (firstMoved && row == rowEnPassant && col == colEnPassant) {
        (*chessBoard)[enpassanted->getRow()][enpassanted->getCol()] = nullptr;
    }
    // remove current one
    (*chessBoard)[this->row][this->col] = nullptr;
    // change the current chesspiece
    this->row = row; this->col = col;
}
