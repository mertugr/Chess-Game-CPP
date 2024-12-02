#ifndef PIECE_H
#define PIECE_H
//DEFINING PIECE CLASS
class piece {
private:
    char type, row, col;

public:
    friend class board;
    piece() : type('.') {}
    void setPiece(char type, char r, char j);
    char display() const;
};

#endif // PIECE_H

