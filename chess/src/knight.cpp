#include "Knight.h"

void Knight::calculatePotentialMoves(bool potentialMoves[8][8]) const {
    if (checkPotential(row+2, col+1)) potentialMoves[row+2][col+1] = true;
    if (checkPotential(row-2, col+1)) potentialMoves[row-2][col+1] = true;
    if (checkPotential(row+2, col-1)) potentialMoves[row+2][col-1] = true;
    if (checkPotential(row-2, col-1)) potentialMoves[row-2][col-1] = true;
    if (checkPotential(row+1, col+2)) potentialMoves[row+1][col+2] = true;
    if (checkPotential(row+1, col-2)) potentialMoves[row+1][col-2] = true;
    if (checkPotential(row-1, col+2)) potentialMoves[row-1][col+2] = true;
    if (checkPotential(row-1, col-2)) potentialMoves[row-1][col-2] = true;
}
