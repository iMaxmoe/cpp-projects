#include "ChessGame.h"
#include "QDebug"
#include "cstring"

/******************************
 * Constructor and Destructor *
 ******************************/

ChessGame::ChessGame(): game_window(new GameWindow(nullptr, this)),
    whiteKing(new King(WHITE, 0, 4, &chessBoard)), blackKing(new King(Player::BLACK, 7, 4, &chessBoard)),
    pawnFirstMove(nullptr), selectedChessPiece(nullptr), currentPlayer(WHITE)
{
    //first fill the chessBoard with nullptrs
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            chessBoard[i][j] = nullptr;
        }
    }

    // initialize chessBoard(all the chesses) and set the icons
    // Pawn
    for (int i = 0; i < 8; i++) {
        chessBoard[1][i] = new Pawn(Player::WHITE, 1, i, &chessBoard);
        chessBoard[6][i] = new Pawn(Player::BLACK, 6, i, &chessBoard);
        game_window->set_piece(1,i,chessBoard[1][i]->getImage());
        game_window->set_piece(6,i,chessBoard[6][i]->getImage());
    }
    // Rook
    chessBoard[0][0] = new Rook(Player::WHITE, 0, 0, &chessBoard);
    chessBoard[0][7] = new Rook(Player::WHITE, 0, 7, &chessBoard);
    chessBoard[7][0] = new Rook(Player::BLACK, 7, 0, &chessBoard);
    chessBoard[7][7] = new Rook(Player::BLACK, 7, 7, &chessBoard);
    game_window->set_piece(0,0,chessBoard[0][0]->getImage());
    game_window->set_piece(0,7,chessBoard[0][7]->getImage());
    game_window->set_piece(7,0,chessBoard[7][0]->getImage());
    game_window->set_piece(7,7,chessBoard[7][7]->getImage());

    // Knight
    chessBoard[0][1] = new Knight(Player::WHITE, 0, 1, &chessBoard);
    chessBoard[0][6] = new Knight(Player::WHITE, 0, 6, &chessBoard);
    chessBoard[7][1] = new Knight(Player::BLACK, 7, 1, &chessBoard);
    chessBoard[7][6] = new Knight(Player::BLACK, 7, 6, &chessBoard);
    game_window->set_piece(0,1,chessBoard[0][1]->getImage());
    game_window->set_piece(0,6,chessBoard[0][6]->getImage());
    game_window->set_piece(7,1,chessBoard[7][1]->getImage());
    game_window->set_piece(7,6,chessBoard[7][6]->getImage());

    // Bishop
    chessBoard[0][2] = new Bishop(Player::WHITE, 0, 2, &chessBoard);
    chessBoard[0][5] = new Bishop(Player::WHITE, 0, 5, &chessBoard);
    chessBoard[7][2] = new Bishop(Player::BLACK, 7, 2, &chessBoard);
    chessBoard[7][5] = new Bishop(Player::BLACK, 7, 5, &chessBoard);
    game_window->set_piece(0,2,chessBoard[0][2]->getImage());
    game_window->set_piece(0,5,chessBoard[0][5]->getImage());
    game_window->set_piece(7,2,chessBoard[7][2]->getImage());
    game_window->set_piece(7,5,chessBoard[7][5]->getImage());

    // King
    chessBoard[0][4] = whiteKing;
    chessBoard[7][4] = blackKing;
    game_window->set_piece(0,4,chessBoard[0][4]->getImage());
    game_window->set_piece(7,4,chessBoard[7][4]->getImage());

    // Queen
    chessBoard[0][3] = new Queen(Player::WHITE, 0, 3, &chessBoard);
    chessBoard[7][3] = new Queen(Player::BLACK, 7, 3, &chessBoard);
    game_window->set_piece(0,3,chessBoard[0][3]->getImage());
    game_window->set_piece(7,3,chessBoard[7][3]->getImage());

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            connect(game_window->get_square(i, j), &Square::clicked_with_pos, this, &ChessGame::processUserInput);
        }
    }
}

ChessGame::~ChessGame() {
    // delete game_window and all the chess pieces
    delete game_window;
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            delete chessBoard[i][j];
    }
}



/********************
 * ChessBoard State *
 ********************/

King* ChessGame::getPlayerKing(Player player) const { return (player == BLACK)?  blackKing : whiteKing; }

bool checkValidMoves(bool validMoves[8][8]) { // check whether there is valid move for a chess. helper function
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++ ) {
            if (validMoves[i][j] == true)
                return true;
        }
    }
    return false;
}

bool ChessGame::hasValidMoves(Player player) const {
    // traverse all the chess pieces of the given player to see whether he has a movable chess
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard[i][j] != nullptr && chessBoard[i][j]->player == player) {
                bool validMoves[8][8];
                // create a validMoves[8][8] for the chess. Initially all false
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        validMoves[i][j] = false;
                    }
                }
                // process validMoves
                calculateValidMoves(chessBoard[i][j], validMoves);
                // check whether there exists a chess that has valid move
                if (checkValidMoves(validMoves)) return true;
            }
        }
    }
    return false;
}

void ChessGame::calculateValidMoves(ChessPiece* chessPiece, bool validMoves[8][8]) const {
    if (chessPiece == nullptr) return;
    for (int m = 0; m < 8; m++) {
        for (int n = 0; n < 8; n++) {
           validMoves[m][n] = false;
        }
    }
    // first calculate potential moves
    chessPiece->calculatePotentialMoves(validMoves);
    // check whether there will be check: upgrade potential moves to valid moves
    King* myKing = (chessPiece->player == BLACK)? blackKing: whiteKing;
    for (int m = 0; m < 8; m++) {
        for (int n = 0; n < 8; n++) {
            if (validMoves[m][n]  == true) {
                chessPiece->potentialMove(m,n);
                if (myKing->calculatePotentialCheck()) validMoves[m][n] = false;
                chessPiece->undoPotentialMove();
            }
        }
    }
    // for castling
    if (selectedChessPiece == myKing) {
        if (myKing->canCastleGivenSide(King::KING_SIDE) && validMoves[myKing->getRow()][5] == false) validMoves[myKing->getRow()][6] = false;
        if (myKing->canCastleGivenSide(King::QUEEN_SIDE) && validMoves[myKing->getRow()][3] == false) validMoves[myKing->getRow()][2] = false;
    }
}

void ChessGame::promotePawn(Pawn* pawn) {
    if ((pawn->player == WHITE && pawn->getRow() == 7) || (pawn->player == BLACK && pawn->getRow() == 0)){
        // delete highlight
        game_window->reset_highlighted();
        // First pop out the promotion window to get user's selection
        char choice = game_window->get_promotion_choice(this->currentPlayer);
        int row = pawn->getRow(), col = pawn->getCol();
        // Say goodbye to the previous piece
        // delete pawn;
        // Create a new piece of the corresponding type'
        switch (choice)
        {
            case 'Q':
                chessBoard[row][col] = new Queen(currentPlayer, row, col, &chessBoard);
                game_window->set_piece(row,col,chessBoard[row][col]->getImage());
            break;
            case 'R':
                chessBoard[row][col] = new Rook(currentPlayer, row, col, &chessBoard);
                game_window->set_piece(row,col,chessBoard[row][col]->getImage());
            break;
            case 'N':
                chessBoard[row][col] = new Knight(currentPlayer, row, col, &chessBoard);
                game_window->set_piece(row,col,chessBoard[row][col]->getImage());
            break;
            case 'B':
                chessBoard[row][col] = new Bishop(currentPlayer, row, col, &chessBoard);
                game_window->set_piece(row,col,chessBoard[row][col]->getImage());
            break;
        }
    }
}



/******************
 * ChessGame Flow *
 ******************/

void ChessGame::processUserInput(int row, int col) {
    if (selectedChessPiece != nullptr && selectedChessPiece->player == currentPlayer && selectedChessPieceValidMoves[row][col] == true) {
        moveSelectedChessPiece(row, col);
        game_window->reset_highlighted();
        selectedChessPiece = nullptr;
        displayCurrentPlayerCheck();
        return;
    }
    selectChessPiece(row, col);
    if (selectedChessPiece == nullptr) {
        game_window->reset_highlighted();
        game_window->get_square(row, col)->set_highlighted(true);
        displayCurrentPlayerCheck();
        return;
    }
    displaySelectedChessPieceValidMoves();
}

void ChessGame::selectChessPiece(int row, int col) {
    selectedChessPiece = chessBoard[row][col];
    if (selectedChessPiece != nullptr) {
        calculateValidMoves(selectedChessPiece, selectedChessPieceValidMoves);
    }
}

void ChessGame::moveSelectedChessPiece(int row, int col) {
    int prevRow = selectedChessPiece->getRow(), prevCol = selectedChessPiece->getCol();
    // move the selected chess piece. if implement undo, store it in stack.
    selectedChessPiece->move(row, col);
    game_window->set_piece(prevRow,prevCol,' ');
    game_window->set_piece(row, col, chessBoard[row][col]->getImage());

    if (selectedChessPiece->isPawn()) {
        // promote pawn
        promotePawn(dynamic_cast<Pawn*>(selectedChessPiece));
        // enpassant
        if (pawnFirstMove != nullptr && row == dynamic_cast<Pawn*>(selectedChessPiece)->rowEnPassant && col == dynamic_cast<Pawn*>(selectedChessPiece)->colEnPassant) {
            game_window->set_piece(pawnFirstMove->getRow(), pawnFirstMove->getCol(), ' ');
            if (pawnFirstMove->enpassantedBy1 != nullptr) pawnFirstMove->enpassantedBy1->passTurnEnPassant();
            if (pawnFirstMove->enpassantedBy2 != nullptr) pawnFirstMove->enpassantedBy2->passTurnEnPassant();
            pawnFirstMove = nullptr;
        }
        if (dynamic_cast<Pawn*>(selectedChessPiece)->potentiallyCaptured == true) {
            pawnFirstMove = dynamic_cast<Pawn*>(selectedChessPiece);
            dynamic_cast<Pawn*>(selectedChessPiece)->potentiallyCaptured = false;
            // update check
            blackKing->updateCheck();
            whiteKing->updateCheck();
            nextPlayerTurn();
            return;
        }
    }
    // update pawnFirstMove
    if (pawnFirstMove != nullptr) {
        if (pawnFirstMove->enpassantedBy1 != nullptr) pawnFirstMove->enpassantedBy1->passTurnEnPassant();
        if (pawnFirstMove->enpassantedBy2 != nullptr) pawnFirstMove->enpassantedBy2->passTurnEnPassant();
    }
    pawnFirstMove = nullptr;
    // castling
    if ((currentPlayer == WHITE && selectedChessPiece == whiteKing && whiteKing->hasCastled()) || (currentPlayer == BLACK && selectedChessPiece == blackKing && blackKing->hasCastled()))
        updateCastlingGUI();

    // update check
    blackKing->updateCheck();
    whiteKing->updateCheck();
    // After the move, switch to another player
    nextPlayerTurn();
}

void ChessGame::nextPlayerTurn() {
    // change the currentPlayer
    currentPlayer = (currentPlayer == WHITE)? BLACK: WHITE;
    // change label
    game_window->set_current_player(currentPlayer);
    // checkmate?
    if (getPlayerKing(currentPlayer)->isCheck() && !hasValidMoves(currentPlayer)) {
        game_window->show_checkmate_label();
    }
    // stalemate?
    if (!getPlayerKing(currentPlayer)->isCheck() && !hasValidMoves(currentPlayer)) {
        game_window->show_stalemate_label();
    }
}



/**************
 * Graphic UI *
 **************/

GameWindow* ChessGame::get_game_window() const { return game_window; }

void ChessGame::startGraphicUI() { game_window->show(); }

void ChessGame::displaySelectedChessPieceValidMoves() const {
    // first delete the previously-highlighted ones
    game_window->reset_highlighted();
    displayCurrentPlayerCheck(); // the checked king should always been highlighted
    // highlight the new ones
    std::string color_light = (selectedChessPiece->player == currentPlayer)? "green":"purple";
    // highlight selected piece itself
    game_window->get_square(selectedChessPiece->getRow(), selectedChessPiece->getCol())->set_highlighted(true, color_light);
    // highlight the valid moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (selectedChessPieceValidMoves[i][j] == true)
                game_window->get_square(i, j)->set_highlighted(true, color_light);
        }
    }
}

void ChessGame::displayCurrentPlayerCheck() const {
    if (blackKing->isCheck())
         game_window->get_square(blackKing->getRow(), blackKing->getCol())->set_highlighted(true, "red");
    if (whiteKing->isCheck())
         game_window->get_square(whiteKing->getRow(), whiteKing->getCol())->set_highlighted(true, "red");
}

void ChessGame::updateCastlingGUI() const {
    // King's image has been updated in moveSelectedChess
    King* current = (currentPlayer == WHITE)? whiteKing: blackKing;
    if (current->hasCastledKingSide()) {
        game_window->set_piece(current->getRow(), 7, ' ');
        game_window->set_piece(current->getRow(), 5, chessBoard[current->getRow()][5]->getImage());
        current->castledKingSide = false;
        return;
    }
    if (current->hasCastledQueenSide()) {
        game_window->set_piece(current->getRow(), 0, ' ');
        game_window->set_piece(current->getRow(), 3, chessBoard[current->getRow()][3]->getImage());
         current->castledQueenSide = false;
        return;
    }
}



/**************
 * Console UI *
 **************/

void ChessGame::startConsoleUI() {
    do {
        displayChessBoardConsole();
        cout << ((currentPlayer == WHITE)? "White" : "Black") << "'s Turn." << endl;

        int row, col;
        char confirm;
        do {
            do {
                do {
                    cout << "Select your Chess Piece (col, row): ";
                    cin >> col >> row; col -= 1; row -=1;
                    if ((row < 0) || (row >= 8) || (col < 0) || (col >= 8)) continue;

                    if ((chessBoard[row][col] != nullptr) && (chessBoard[row][col]->player != currentPlayer)) {
                        selectedChessPiece = nullptr;
                    }
                    else {
                        selectedChessPiece = chessBoard[row][col];
                    }
                    calculateValidMoves(selectedChessPiece, selectedChessPieceValidMoves);
                } while (selectedChessPiece == nullptr);
                cout << endl;
                displaySelectedChessPieceValidMovesConsole();

                cout << "Confirm selection? (Y/N) ";
                cin >> confirm;
            } while ((confirm != 'Y') && (confirm != 'y'));

            cout << "Make your Move (col, row): ";
            cin >> col >> row; col -= 1; row -=1;
            cout << endl;
        } while ((row < 0) || (row >= 8) || (col < 0) || (col >= 8) || !selectedChessPieceValidMoves[row][col]);
        ChessPiece* occupyingChessPiece = selectedChessPiece->move(row, col);
        delete occupyingChessPiece;

        selectedChessPiece = nullptr;
        fill_n(&selectedChessPieceValidMoves[0][0], 64, false); // Reset all to false.
        currentPlayer = ((currentPlayer == WHITE)? BLACK : WHITE);
        getPlayerKing(currentPlayer)->updateCheck();
    } while (hasValidMoves(currentPlayer));

    displayChessBoardConsole();
    if (getPlayerKing(currentPlayer)->isCheck()) {
        cout << ((currentPlayer == WHITE)? "White" : "Black") << " Checkmate! " << ((currentPlayer == WHITE)? "Black" : "White") << " wins!" << endl;
    }
    else {
        cout << "Stalemate!" << endl;
    }
}

void ChessGame::displayChessBoardConsole() const {
    cout << " |---|---|---|---|---|---|---|---|\n";
    for (int row = 7; row >= 0; row--) {
        cout << row + 1;
        for (int col = 0; col < 8; col++) {
            cout << "|";

            if (chessBoard[row][col] == nullptr) {
                cout << "   ";
            }
            else {
                if ((chessBoard[row][col] == getPlayerKing(currentPlayer)) && getPlayerKing(currentPlayer)->isCheck()) {
                    cout << "!" << chessBoard[row][col]->getImage() << "!";
                }
                else {
                    cout << " " << chessBoard[row][col]->getImage() << " ";
                }
            }
        }
        cout << "|\n";
        cout << " |---|---|---|---|---|---|---|---|\n";
    }
    cout << " | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n";
    cout << endl;
}

void ChessGame::displaySelectedChessPieceValidMovesConsole() const {
    cout << " |---|---|---|---|---|---|---|---|\n";
    for (int row = 7; row >= 0; row--) {
        cout << row + 1;
        for (int col = 0; col < 8; col++) {
            cout << "|";
            if (chessBoard[row][col] == nullptr) {
                if (selectedChessPieceValidMoves[row][col]) {
                    cout << "< >";
                }
                else {
                    cout << "   ";
                }
            }
            else {
                if (selectedChessPieceValidMoves[row][col] || ((row == selectedChessPiece->getRow()) && (col == selectedChessPiece->getCol()))) {
                    cout << "<" << chessBoard[row][col]->getImage() << ">";
                }
                else if ((chessBoard[row][col] == getPlayerKing(currentPlayer)) && getPlayerKing(currentPlayer)->isCheck()) {
                    cout << "!" << chessBoard[row][col]->getImage() << "!";
                }
                else {
                    cout << " " << chessBoard[row][col]->getImage() << " ";
                }
            }
        }
        cout << "|\n";
        cout << " |---|---|---|---|---|---|---|---|\n";
    }
    cout << " | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n";
    cout << endl;
}
