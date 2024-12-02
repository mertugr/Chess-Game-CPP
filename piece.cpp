#include "piece.h"

char piece::display() const {
    return type;
}
//DEFINING PIECE TYPES ROWS AND COLUMNS
void piece::setPiece(char t, char r, char c) {
    type = t;
    row = r;
    col = c;
}

