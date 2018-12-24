#include "King.h"
#include "QDebug"
char King::getImage() const {return (player == BLACK)? IMAGE_BLACK:IMAGE_WHITE;}

void King::calculatePotentialMoves(bool potentialMoves[8][8]) const {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i== 0 && j == 0) continue;
            if (checkPotential(row+i, col+j)) {
                potentialMoves[row+i][col+j] = true;
            }
        }
    }
    if (canCastleGivenSide(KING_SIDE)) {
        potentialMoves[row][col+2] = true;
    }
    if (canCastleGivenSide(QUEEN_SIDE)) potentialMoves[row][col-2] = true;
}

void King::calculatePotentialCaptures(bool potentialCaptures[8][8]) const {
    calculatePotentialMoves(potentialCaptures);
}

ChessPiece* King::move(int row, int col) {
    // Change the firstMoved status of King
    if(!hasMoved) hasMoved = true;
    // whether it is castling
    if (col == this->col + 2) {
        castledKingSide = true;
        (*chessBoard)[row][5] = (*chessBoard)[row][7];
        (*chessBoard)[row][5]->setCol(5);
        (*chessBoard)[row][7] = nullptr;
    }
    if (col == this->col - 2) {
        castledQueenSide = true;
        (*chessBoard)[row][3] = (*chessBoard)[row][0];
        (*chessBoard)[row][3]->setCol(3);
        (*chessBoard)[row][0] = nullptr;
    }
    // the enemy chess is eaten
    (*chessBoard)[row][col] = this;
    // remove current one
    (*chessBoard)[this->row][this->col] = nullptr;
    // change the current chesspiece
    this->row = row; this->col = col;
}

bool King::calculatePotentialCheck() const {
    // create a potentialCapture[8][8] for each enemy chess.
    bool potentialCapture[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*chessBoard)[i][j] != nullptr && isEnemyChessPiece((*chessBoard)[i][j])) {
                // refresh potentialCapture
                for (int m = 0; m < 8; m++) {
                    for (int n = 0; n < 8; n++) {
                       potentialCapture[m][n] = false;
                    }
                }
                // process potentialCature
                (*chessBoard)[i][j]->calculatePotentialCaptures(potentialCapture);
                // check whether there exists a potential capture of the king
                if (potentialCapture[row][col] == true) return true;
            }
        }
    }
    return false;
}

void King::updateCheck() {
    check = calculatePotentialCheck();
}

bool King::isCheck() const {return check;}


bool King::canCastleGivenSide(CastlingSide castlingSide) const{
    if (check) return false;
    if (hasMoved) return false;
    if (castlingSide == KING_SIDE) {
        if ((*chessBoard)[row][7]!= nullptr && (*chessBoard)[row][7]->isRook() && dynamic_cast<Rook*>((*chessBoard)[row][7])->canCastle()){
            if ((*chessBoard)[row][5] != nullptr) return false;
            if ((*chessBoard)[row][6] != nullptr) return false;
            return true;
        }
    }
    if (castlingSide == QUEEN_SIDE) {
        if ((*chessBoard)[row][0]!= nullptr&& (*chessBoard)[row][0]->isRook() && dynamic_cast<Rook*>((*chessBoard)[row][0])->canCastle()){
            if ((*chessBoard)[row][3] != nullptr) return false;
            if ((*chessBoard)[row][2] != nullptr) return false;
            if ((*chessBoard)[row][1] != nullptr) return false;
            return true;
        }
    }
    return false;
}

