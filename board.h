#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cctype>
#include <vector>
#include <cmath>
#include <fstream>
#include "piece.h"

class piece;
//DEFINING BOARD CLASS
class board {
private:
    std::vector<std::vector<piece> > _board;
    bool isPieceAttackingSquare(int fromRow, int fromCol, int toRow, int toCol) const;
    

public:
    board();
    int whiteScore;
    int blackScore;
    void display_board() const;
    bool legal_move(std::string move) const;
    board &make_move(std::string move);
    bool isClearPath(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isWhiteTurn=1;
    std::vector<int> calculateOverallScore() const;
    bool isPieceUnderAttack(int row, int col) const;
    std::vector<std::string> generateLegalMoves() const;
    bool isCheckmate() const;
    void findKingPosition(int &kingRow, int &kingCol) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // BOARD_H

