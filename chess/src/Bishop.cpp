#include "Bishop.h"

void Bishop::calculatePotentialMoves(bool potentialMoves[8][8]) const {
    // each (i, j) pair indicates a direction
    for (int i = -1; i <= 1; i+=2) {
        for (int j = -1; j <= 1; j+=2) {
            for (int n = 1; n < 8; n ++) {
                if (checkPotential(row+i*n, col+j*n)){
                    potentialMoves[row+i*n][col+j*n] = true;
                    // If it's enemy piece, mark as potential move but stop further search
                    if ((*chessBoard)[row+i*n][col+j*n] != nullptr) break;
                }
                else break;
            }
        }
    }
}
