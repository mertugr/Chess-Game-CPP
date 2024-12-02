#include "board.h"
#include "piece.h"
#include <string>
#include <fstream>

//CREATING BOARD
board::board() : _board(8, std::vector<piece>(8)), whiteScore(0), blackScore(0), isWhiteTurn(true) {
      whiteScore=0;
    blackScore=0;
 for (int i = 0; i < 8; ++i) {
        _board[1][i].setPiece('p', '7', 'a' + i); // Black pawn
        _board[6][i].setPiece('P', '2', 'a' + i); // White pawn
    }
    // Set up rooks
    _board[0][0].setPiece('r', '8', 'a'); // Black rook
    _board[0][7].setPiece('r', '8', 'h'); // Black rook
    _board[7][0].setPiece('R', '1', 'a'); // White rook
    _board[7][7].setPiece('R', '1', 'h'); // White rook
    // Set up knights
    _board[0][1].setPiece('n', '8', 'b'); // Black knight
    _board[0][6].setPiece('n', '8', 'g'); // Black knight
    _board[7][1].setPiece('N', '1', 'b'); // White knight
    _board[7][6].setPiece('N', '1', 'g'); // White knight
    // Set up bishops
    _board[0][2].setPiece('b', '8', 'c'); // Black bishop
    _board[0][5].setPiece('b', '8', 'f'); // Black bishop
    _board[7][2].setPiece('B', '1', 'c'); // White bishop
    _board[7][5].setPiece('B', '1', 'f'); // White bishop
    // Set up queens
    _board[0][3].setPiece('q', '8', 'd'); // Black queen
    _board[7][3].setPiece('Q', '1', 'd'); // White queen
    // Set up kings
    _board[0][4].setPiece('k', '8', 'e'); // Black king
    _board[7][4].setPiece('K', '1', 'e'); // White king
}
//PRINTING BOARD
void board::display_board() const {
    for (int i = 0; i < 8; ++i) {
        std::cout << " " << 8 - i << "| ";
        for (int j = 0; j < 8; ++j) {
           std:: cout<<_board[i][j].display();
            std::cout << " ";
        }
       std:: cout << std::endl;
    }
    std::cout << "   _________________" << std::endl;
   std:: cout << "    a b c d e f g h" << std::endl;
}
//INITIALIZE IF THE PIECE IS ATTACK
bool board::isPieceAttackingSquare(int fromRow, int fromCol, int toRow, int toCol) const {
   char pieceType = _board[fromRow][fromCol].display();

    if (isupper(pieceType) == isupper(_board[toRow][toCol].display())) {
        return false;
    }
    switch (pieceType) {
        case 'p':
            return ((toRow == fromRow + 1 && std::abs(toCol - fromCol) == 1) || (toRow == fromRow + 1 && toCol == fromCol));
        case 'P':
            return ((toRow == fromRow - 1 && std::abs(toCol - fromCol) == 1) || (toRow == fromRow - 1 && toCol == fromCol));
        case 'n':
        case 'N':
            return ((std::abs(toRow - fromRow) == 2 && std::abs(toCol - fromCol) == 1) || (std::abs(toRow - fromRow) == 1 && std::abs(toCol - fromCol) == 2));
        case 'b':
        case 'B':
            return (std::abs(toRow - fromRow) == std::abs(toCol - fromCol));
        case 'r':
        case 'R':
            return (toRow == fromRow || toCol == fromCol);
        case 'q':
        case 'Q':
            return (toRow == fromRow || toCol == fromCol || std::abs(toRow - fromRow) == std::abs(toCol - fromCol));
        case 'k':
        case 'K':
            return (std::abs(toRow - fromRow) <= 1 && std::abs(toCol - fromCol) <= 1);
        default:
            return false;
    }
}


bool board::legal_move(std::string move) const {
      if (move.length() != 4) {
        std:: cout << "Invalid move format. Please enter a move in the format 'e2e4'." << std::endl;
        return false;
    }
    char fromCol =move[0];
    char fromRow =move[1];
    char toCol =move[2];
    char toRow =move[3];

     if (fromCol < 'a' || fromCol > 'h' || toCol < 'a' || toCol > 'h' ||
        fromRow < '1' || fromRow > '8' || toRow < '1' || toRow > '8') {
        std::cout << "Invalid coordinates. Please enter valid coordinates." << std::endl;
        return false;
    }
    int fromRowIndex = '8' - fromRow;
    int fromColIndex = fromCol - 'a';
    int toRowIndex = '8' - toRow;
    int toColIndex = toCol - 'a';

    if (_board[fromRowIndex][fromColIndex].display() == '.') {
        std::cout << "There is no piece at the starting position." << std::endl;
        return false;
    }
     if ((isupper(_board[fromRowIndex][fromColIndex].display()) == isupper(_board[toRowIndex][toColIndex].display())) &&
    (islower(_board[fromRowIndex][fromColIndex].display()) == islower(_board[toRowIndex][toColIndex].display()))) {
    return false;  // PATH IS NOT CLEAR OR THE PIECES ARE IN SAME COLOR
    }

    char pieceType = _board[fromRowIndex][fromColIndex].display();
    char targetPiece = _board[toRowIndex][toColIndex].display();

    // Check rules for each piece type
    if(islower(pieceType) && isWhiteTurn)
        return false;
    if(isupper(pieceType) && !isWhiteTurn)
        return false;
    switch (pieceType) {
      case 'p':
    // Black pawn rules
    if (fromRowIndex == 1 && fromColIndex == toColIndex && targetPiece == '.' && toRowIndex - fromRowIndex == 2)
        return true;
    if (fromColIndex == toColIndex && targetPiece == '.' && toRowIndex - fromRowIndex == 1) {
        // Pawn moves forward (including initial two-square move)
        return true;
    } else if (std::abs(fromColIndex - toColIndex) == 1 && toRowIndex - fromRowIndex == 1 && targetPiece != '.') {
        // Valid pawn move
        return true;
    }
    break;

case 'P':
    // White pawn rules
    if (fromRowIndex == 6 && fromColIndex == toColIndex && targetPiece == '.' && fromRowIndex - toRowIndex == 2)
        return true;
    if (fromColIndex == toColIndex && targetPiece == '.' && fromRowIndex - toRowIndex == 1) {
        // Pawn moves forward (including initial two-square move)
        return true;
    } else if (std::abs(fromColIndex - toColIndex) == 1 && fromRowIndex - toRowIndex == 1 && targetPiece != '.') {
        // Valid pawn move
        return true;
    }
    break;

        case 'r':
        case 'R':
            // Rook rules
            if ((fromRowIndex == toRowIndex || fromColIndex == toColIndex) && isClearPath(fromRowIndex, fromColIndex, toRowIndex, toColIndex)) {
                return true;
            }
            break;
        case 'n':
        case 'N':
            // Knight rules
            if ((std::abs(fromRowIndex - toRowIndex) == 2 && std::abs(fromColIndex - toColIndex) == 1)
                || (std::abs(fromRowIndex - toRowIndex) == 1 && std::abs(fromColIndex - toColIndex) == 2)) {
                return true;
            }
            break;
        case 'b':
        case 'B':
            // Bishop rules
            if (std::abs(fromRowIndex - toRowIndex) == std::abs(fromColIndex - toColIndex) && isClearPath(fromRowIndex, fromColIndex, toRowIndex, toColIndex)) {
                return true;
            }
            break;
        case 'q':
        case 'Q':
            // Queen rules (combination of rook and bishop)
            if ((fromRowIndex == toRowIndex || fromColIndex == toColIndex || std::abs(fromRowIndex - toRowIndex) == std::abs(fromColIndex - toColIndex))
                && isClearPath(fromRowIndex, fromColIndex, toRowIndex, toColIndex)) {
                return true;
            }
            break;
        case 'k':
        case 'K':
            // King rules
            if (std::abs(fromRowIndex - toRowIndex) <= 1 && std::abs(fromColIndex - toColIndex) <= 1) {
                return true;
            }
            break;
        default:
           std:: cout << "Invalid piece type." << std::endl;
            return false;
    }

   // cout << "Invalid move for piece type: " << pieceType << endl;
    return false;
}

board& board::make_move(std::string move) {
    if (legal_move(move)) {
        char fromCol = move[0];
        char fromRow = move[1];
        char toCol = move[2];
        char toRow = move[3];

        int fromRowIndex = '8' - fromRow;
        int fromColIndex = fromCol - 'a';
        int toRowIndex = '8' - toRow;
        int toColIndex = toCol - 'a';

         if (_board[toRowIndex][toColIndex].display() != '.') {
            char capturedPiece = _board[toRowIndex][toColIndex].display();
            int capturedPieceValue = 0;

            // Assign point values to captured piece types
            switch (capturedPiece) {
                case 'p':
                case 'P':
                    capturedPieceValue = 1;
                    break;
                case 'n':
                case 'N':
                    capturedPieceValue = 3;
                    break;
                case 'b':
                case 'B':
                    capturedPieceValue = 3;
                    break;
                case 'r':
                case 'R':
                    capturedPieceValue = 5;
                    break;
                case 'q':
                case 'Q':
                    capturedPieceValue = 9;
                    break;
                
                case 'k':
                case 'K':
                    capturedPieceValue = 100;  // think as its infinity
                    break;
            }

            // Increment the score based on the captured piece value and its color
            if (isupper(capturedPiece)) {
                // Black piece captured
                blackScore += capturedPieceValue;
            } else {
                // White piece captured
                whiteScore += capturedPieceValue;
            }
        }

       
       

      
        _board[toRowIndex][toColIndex] = _board[fromRowIndex][fromColIndex];
        _board[fromRowIndex][fromColIndex] = piece();
        isWhiteTurn = !isWhiteTurn;
        return *this;  // Return a reference to the current board
    } else {
        std::cout << "Invalid move. Please try again." << std::endl;
        return *this;  // Return a reference to the current board
    }
}

bool board::isClearPath(int fromRow, int fromCol, int toRow, int toCol) const {
     int deltaRow = (toRow > fromRow) ? 1 : ((toRow < fromRow) ? -1 : 0);
    int deltaCol = (toCol > fromCol) ? 1 : ((toCol < fromCol) ? -1 : 0);

    for (int row = fromRow + deltaRow, col = fromCol + deltaCol; row != toRow || col != toCol; row += deltaRow, col += deltaCol) {
        if (_board[row][col].display() != '.') {
            return false;  // Path is not clear
        }
    }
    return true;  // Path is clear
}



bool board::isPieceUnderAttack(int row, int col) const {
    char kingColor = _board[row][col].display();

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char pieceType = _board[i][j].display();

            if ((kingColor == 'K' && std::islower(pieceType)) || (kingColor == 'k' && std::isupper(pieceType))) {
                if (isPieceAttackingSquare(i, j, row, col)) {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<int> board::calculateOverallScore() const {
    int totalWhiteScore = 0;
    int totalBlackScore = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char pieceType = _board[i][j].display();
            if (pieceType != '.') {
                int pieceValue = 0;

                switch (pieceType) {
                    case 'p':
                    case 'P':
                        pieceValue = 1;
                        break;
                    case 'n':
                    case 'N':
                        pieceValue = 3;
                        break;
                    case 'b':
                    case 'B':
                        pieceValue = 3;
                        break;
                    case 'r':
                    case 'R':
                        pieceValue = 5;
                        break;
                    case 'q':
                    case 'Q':
                        pieceValue = 9;
                        break;
                    case 'k':
                    case 'K':
                        pieceValue = 100;
                        break;
                }

                if (isPieceUnderAttack(i, j)) {
                    pieceValue -= pieceValue / 2;
                }

                if (std::isupper(pieceType)) {
                    totalWhiteScore += pieceValue;
                } else {
                    totalBlackScore += pieceValue;
                }
            }
        }
    }

    std::vector<int> scores;
    scores.push_back(totalBlackScore);
    scores.push_back(totalWhiteScore);

    return scores;
}

std::vector<std::string> board::generateLegalMoves() const {
    std::vector<std::string> legalMoves;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char pieceType = _board[i][j].display();

            if ((isWhiteTurn && std::isupper(pieceType)) || (!isWhiteTurn && std::islower(pieceType))) {
                for (int toRow = 0; toRow < 8; ++toRow) {
                    for (int toCol = 0; toCol < 8; ++toCol) {
                        std::string move = std::string(1, 'a' + j) + std::to_string(8 - i) + std::string(1, 'a' + toCol) + std::to_string(8 - toRow);

                        if (legal_move(move)) {
                            if (_board[toRow][toCol].display() != '.' &&
                                std::isupper(pieceType) != std::isupper(_board[toRow][toCol].display())) {
                                legalMoves.insert(legalMoves.begin(), move);
                            } else {
                                legalMoves.push_back(move);
                            }
                        }
                    }
                }
            }
        }
    }

    return legalMoves;
}

void board::findKingPosition(int &kingRow, int &kingCol) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char pieceType = _board[i][j].display();
            if ((isWhiteTurn && pieceType == 'K') || (!isWhiteTurn && pieceType == 'k')) {
                kingRow = i;
                kingCol = j;
                return;
            }
        }
    }

    kingRow = -1;
    kingCol = -1;
}

bool board::isCheckmate() const {
    int kingRow, kingCol;
    findKingPosition(kingRow, kingCol);

    if (isPieceUnderAttack(kingRow, kingCol)) {
        std::vector<std::string> legalMoves = generateLegalMoves();

        if (legalMoves.empty()) {
            return true;
        }
    }

    return false;
}

void board::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::out);

    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Save the board state to the file
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            outFile << _board[i][j].display() << " ";
        }
        outFile << "\n";
    }

    // Save other relevant game state information (e.g., scores, player turn)
    outFile << "whiteScore:" << whiteScore << " blackScore:" << blackScore <<  "\n";

    outFile.close();
}


void board::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::in);

    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    // Load the board state from the file
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char pieceType;
            inFile >> pieceType;
            _board[i][j].setPiece(pieceType, '0' + (8 - i), 'a' + j);
        }
    }

    // Load other relevant game state information
    inFile >> whiteScore >> blackScore >> isWhiteTurn;

    inFile.close();
}


