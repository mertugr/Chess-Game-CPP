#include "board.h"
#include "piece.h"

int main() {
    board chessBoard;
    chessBoard.display_board();

    std::string move;
    while (1) {
        std::string currentPlayer = (chessBoard.isWhiteTurn) ? "White" : "Black";
        std::cout << "[" << currentPlayer << "'s Turn]" << std::endl;
        std::cout << "Enter your move : ";
        std::cin >> move;

        if (move == "suggest") {
            std::vector<std::string> legalMoves = chessBoard.generateLegalMoves();
            if (!legalMoves.empty()) {
                std::cout << "Suggestion is " << legalMoves[0] << std::endl;
            } else {
                std::cout << "No legal moves available." << std::endl;
            }
            continue;
        }

        if (move == "quit") {
            break;
        }

        chessBoard.make_move(move).display_board();
	std::cout<< "whiteScore:" << chessBoard.whiteScore << " blackScore:" << chessBoard.blackScore <<  "\n";
	chessBoard.saveToFile("savedfile.txt");

        if (chessBoard.isCheckmate()) {
            std::cout << "Checkmate! " << currentPlayer << " wins!" << std::endl;
            break;
        }
    }

    return 0;
}

