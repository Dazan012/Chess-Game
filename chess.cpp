#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int BOARD_SIZE = 8;

enum Piece {
    EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

struct Square {
    Piece piece;
    bool isWhite;
};

class ChessBoard {
public:
    ChessBoard() {
        board.resize(BOARD_SIZE, vector<Square>(BOARD_SIZE, {EMPTY, false}));
        setupBoard();
    }

    void display() {
        cout << "  a b c d e f g h\n";
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << 8 - i << " ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << pieceToChar(board[i][j]) << " ";
            }
            cout << 8 - i << endl;
        }
        cout << "  a b c d e f g h\n";
    }

    bool movePiece(string from, string to) {
        int fromRow = 8 - (from[1] - '0');
        int fromCol = from[0] - 'a';
        int toRow = 8 - (to[1] - '0');
        int toCol = to[0] - 'a';

        if (isValidMove(fromRow, fromCol, toRow, toCol)) {
            board[toRow][toCol] = board[fromRow][fromCol];
            board[fromRow][fromCol] = {EMPTY, false};
            return true;
        }
        return false;
    }

private:
    vector<vector<Square>> board;

    void setupBoard() {
        // Set up pawns
        for (int i = 0; i < BOARD_SIZE; ++i) {
            board[1][i] = {PAWN, true};   // White pawns
            board[6][i] = {PAWN, false};  // Black pawns
        }

        // Set up rooks
        board[0][0] = board[0][7] = {ROOK, true};   // White rooks
        board[7][0] = board[7][7] = {ROOK, false};  // Black rooks

        // Set up knights
        board[0][1] = board[0][6] = {KNIGHT, true};
        board[7][1] = board[7][6] = {KNIGHT, false};

        // Set up bishops
        board[0][2] = board[0][5] = {BISHOP, true};
        board[7][2] = board[7][5] = {BISHOP, false};

        // Set up queens and kings
        board[0][3] = {QUEEN, true};
        board[0][4] = {KING, true};
        board[7][3] = {QUEEN, false};
        board[7][4] = {KING, false};
    }

    char pieceToChar(Square square) {
        if (square.piece == EMPTY) return '.';
        
        switch (square.piece) {
            case PAWN:   return square.isWhite ? 'P' : 'p';
            case ROOK:   return square.isWhite ? 'R' : 'r';
            case KNIGHT: return square.isWhite ? 'N' : 'n';
            case BISHOP: return square.isWhite ? 'B' : 'b';
            case QUEEN:  return square.isWhite ? 'Q' : 'q';
            case KING:   return square.isWhite ? 'K' : 'k';
            default:     return '.';
        }
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
        // Basic validation: check if the move is within bounds and not moving to own piece
        if (toRow < 0 || toRow >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE) return false;
        
        Square fromSquare = board[fromRow][fromCol];
        Square toSquare = board[toRow][toCol];

        if (fromSquare.piece == EMPTY) return false; // No piece to move
        if (toSquare.isWhite == fromSquare.isWhite) return false; // Can't capture own piece

        // For simplicity: Allow only basic moves for pawns (forward one square)
        if (fromSquare.piece == PAWN) {
            int direction = fromSquare.isWhite ? -1 : 1;
            if (toRow == fromRow + direction && toCol == fromCol && toSquare.piece == EMPTY) {
                return true; // Move forward
            }
            if (toRow == fromRow + direction && abs(toCol - fromCol) == 1 && toSquare.piece != EMPTY) {
                return true; // Capture diagonally
            }
            return false;
        }

        // Other pieces' movement validation can be added here
        
        return false; // Default case for invalid moves
    }
};

int main() {
    ChessBoard chessBoard;
    chessBoard.display();

    string from, to;

    while (true) {
        cout << "Enter move (e.g., e2 e4): ";
        cin >> from >> to;

        if (!chessBoard.movePiece(from, to)) {
            cout << "Invalid move. Try again." << endl;
        } else {
            chessBoard.display();
        }
    }

    return 0;
}
