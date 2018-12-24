#ifndef ROOK_H_
#define ROOK_H_

#include "ChessPiece.h"

class Rook : public ChessPiece {
public:
    const static char IMAGE_WHITE = 'R';
	const static char IMAGE_BLACK = 'r';

    Rook(Player player, int row, int col, ChessPiece* (*chessBoard)[8][8]): ChessPiece(player, row, col, chessBoard), hasMoved(false){}
	virtual char getImage() const override;

    virtual void calculatePotentialMoves(bool potentialMoves[8][8]) const override;
    virtual ChessPiece* move(int row, int col) override;
    virtual bool isRook() override {return true;}
    bool canCastle() const {return !hasMoved;}

private:
    bool hasMoved = false;
};

#endif /* ROOK_H_ */
