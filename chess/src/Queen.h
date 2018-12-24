#ifndef QUEEN_H_
#define QUEEN_H_

#include "ChessPiece.h"

class Queen : public ChessPiece {
public:
    const static char IMAGE_WHITE = 'Q';
	const static char IMAGE_BLACK = 'q';

    Queen(Player player, int row, int col, ChessPiece* (*chessBoard)[8][8]): ChessPiece(player, row, col, chessBoard){}
    virtual char getImage() const override {return (player == BLACK)? IMAGE_BLACK:IMAGE_WHITE;}
    virtual void calculatePotentialMoves(bool potentialMoves[8][8]) const override;
};

#endif /* QUEEN_H_ */
