#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_

#include "Player.h"

class ChessGame;

class ChessPiece {
public:
	const Player player;
    ChessPiece(Player player, int row, int col, ChessPiece* (*chessBoard)[8][8]);
	virtual ~ChessPiece() = default; // Empty virtual destructor. Derived classes don't need to declare/define their own destructors if unneeded.

    virtual char getImage() const = 0;
    int getRow() const;
    int getCol() const;
    void setCol(int col) {this->col = col;}

    bool isEnemyChessPiece(const ChessPiece* const chessPiece) const;
	virtual void calculatePotentialMoves(bool potentialMoves[8][8]) const = 0; // Includes Captures. Ignores Checks. Override based on Movement rules for each type of ChessPiece.
    virtual void calculatePotentialCaptures(bool potentialCaptures[8][8]) const {calculatePotentialMoves(potentialCaptures);} // Same as calculatePotentialCaptures, except for Pawn.
    virtual void potentialMove(int row, int col); // Some ChessPiece types care if they haven't been moved during the whole game.
    virtual void undoPotentialMove();
    virtual bool isPawn(){return false;}
    virtual bool isRook(){return false;}
    virtual ChessPiece* move(int row, int col); // Also updates chessBoard. If capture another ChessPiece, return the pointer so ChessBoard can remove it.

protected:
	int row, col; // Current Position.
    int previousRow, previousCol; // For undoing potentialMove().
    ChessPiece* potentialCapturedChessPiece; // For undoing potentialMove().
    ChessPiece* (*chessBoard)[8][8]; // Pointer to ChessBoard. Passed in by ChessGame.
    bool checkPotential(int row, int col) const; // Check whether a block is potential for move
};

#endif /* CHESSPIECE_H_ */
