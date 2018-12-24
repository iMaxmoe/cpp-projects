#ifndef PAWN_H_
#define PAWN_H_

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    const static char IMAGE_WHITE = 'P';
	const static char IMAGE_BLACK = 'p';

    Pawn(Player player, int row, int col, ChessPiece* (*chessBoard)[8][8]): ChessPiece(player, row, col, chessBoard),
        hasMoved(false), firstMoved(false), capturedEnPassant(false),
        rowEnPassant(-1), colEnPassant(-1){}
	virtual char getImage() const override;

	virtual void calculatePotentialMoves(bool potentialMoves[8][8]) const override;
	virtual void calculatePotentialCaptures(bool potentialCaptures[8][8]) const override;
    virtual ChessPiece* move(int row, int col) override; // First Move and En Passant.
    virtual bool isPawn() override {return true;}
    bool hasFirstMoved() const {return (hasMoved == true)? true: false;}
    bool hasCapturedEnPassant() const;
    void passTurnEnPassant();
    Pawn* enpassanted = nullptr;
    Pawn* enpassantedBy1 = nullptr;
    Pawn* enpassantedBy2 = nullptr;
    int rowEnPassant; // Row of enemy Pawn captured En Passant.
    int colEnPassant; // Col of enemy Pawn captured En Passant.
    bool potentiallyCaptured = false;

private:
    bool hasMoved; // Pawn has First Move if still have not moved the whole game.
    bool firstMoved; // En Passant only valid for the immediate next turn.
    bool capturedEnPassant;
};

#endif /* PAWN_H_ */
