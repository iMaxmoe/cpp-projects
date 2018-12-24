#ifndef KING_H_
#define KING_H_

#include "ChessPiece.h"
#include "Rook.h"

class King : public ChessPiece {
public:
    const static char IMAGE_WHITE = 'K';
    const static char IMAGE_BLACK = 'k';
    enum CastlingSide {KING_SIDE, QUEEN_SIDE};

    King(Player player, int row, int col, ChessPiece* (*chessBoard)[8][8]): ChessPiece(player, row, col, chessBoard),
    check(false), hasMoved(false){}
    virtual char getImage() const override;
    virtual void calculatePotentialMoves(bool potentialMoves[8][8]) const override;
    virtual void calculatePotentialCaptures(bool potentialCaptures[8][8]) const override;
    virtual ChessPiece* move(int row, int col) override;

    bool calculatePotentialCheck() const;
    void updateCheck();
    bool isCheck() const;

    bool hasCastled() const {return (castledKingSide || castledQueenSide);}
    bool hasCastledKingSide() const {return castledKingSide;}
    bool hasCastledQueenSide() const {return castledQueenSide;}
    bool castledKingSide = false, castledQueenSide = false;
    bool canCastleGivenSide(CastlingSide castlingSide) const;

private:
    bool check;
    bool hasMoved = false;

};

#endif /* KING_H_ */
