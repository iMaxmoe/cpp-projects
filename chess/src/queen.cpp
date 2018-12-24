#include "Queen.h"

void Queen::calculatePotentialMoves(bool potentialMoves[8][8]) const
{
    for (int i = -1 ; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            for (int n = 1; n < 8; n++) {
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
