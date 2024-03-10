#include <iostream>
#include <vector>
#include <cmath>

// Define chess piece types
enum class PieceType {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

// Define colors of pieces
enum class PieceColor {
    White,
    Black
};

bool Running {true};

// Define a class for a chess piece
class ChessPiece {
public:
    ChessPiece(PieceType type, PieceColor color) : type(type), color(color) {}
    virtual ~ChessPiece() = default;

    [[nodiscard]] PieceType getType() const { return type; }
    [[nodiscard]] PieceColor getColor() const { return color; }

    [[nodiscard]] virtual bool move(int fromX, int fromY, int toX, int toY,
                      const std::vector<std::vector<ChessPiece*>> &board) const = 0;
    virtual std::ostream& operator<<(std::ostream& stream) const = 0;

private:
    PieceType type;
    PieceColor color;
};

//Define Pawn class
class Pawn : public ChessPiece{
public:
    explicit Pawn(PieceColor color) : ChessPiece(PieceType::Pawn, color) {

    }
    std::ostream& operator<<(std::ostream& stream) const override {
        stream << "P";
        return stream;
    }
    [[nodiscard]] bool move (int fromX, int fromY, int toX, int toY,
                             const std::vector<std::vector<ChessPiece*>> &board)  const override {
        //Implement Pawn movement
        if (this->getColor() == PieceColor::White) {
            if (fromY == toY) {
                if (fromX == 6 && fromX == toX+2 && board[toX][toY] == nullptr) { return true; }
                if (fromX == toX+1 && board[toX][toY] == nullptr) { return true; }
                return false;
            }
            if (fromX == toX+1 && (fromY == toY+1 || fromY == toY-1) && board[toX][toY] != nullptr) {
                return true;
            }
            return false;
        }
        else {
            if (fromY == toY) {
                if (fromX == 1 && fromX == toX-2 && board[toX][toY] == nullptr) { return true; }
                if (fromX == toX-1 && board[toX][toY] == nullptr) { return true; }
                return false;
            }
            if (fromX == toX-1 && (fromY == toY+1 || fromY == toY-1) && board[toX][toY] != nullptr) {
                return true;
            }
            return false;
        }
        /* NOT: PİYON KARŞI TARAFA VARINCA İSTEDİĞİ TAŞ OLMA ÖZELLİĞİ EKLENEBİLİR... */
    }
};

//Define King class
class King : public ChessPiece{
public:
    explicit King(PieceColor color) : ChessPiece(PieceType::King, color) {

    }
    std::ostream& operator<<(std::ostream& stream) const override {
        stream << "S";
        return stream;
    }
private:
    [[nodiscard]] bool move (int fromX, int fromY, int toX, int toY,
                             const std::vector<std::vector<ChessPiece*>> &board) const override {
        if (std::sqrt(2.0) >= std::sqrt(std::pow(toX - fromX, 2) + std::pow(toY - fromY, 2))) {
            return true;
        }
        return false;
    }
    ~King() override {
        std::string winner {this->getColor() == PieceColor::Black ? "WHITE" : "BLACK"};
        std::cout << "\n" << winner << " SIDE WON!!!" << std::endl;
        Running = false;
    }
    /* NOT: ŞAH KALE YER DEGİSTİRMESİ (ROK) VE ŞAH CEKME ÖZELLİĞİ EKLENEBİLİR... */
};

//Define Rook class
class Rook : public ChessPiece{
public:
    explicit Rook(PieceColor color) : ChessPiece(PieceType::Rook, color) {

    }
    std::ostream& operator<<(std::ostream& stream) const override {
        stream << "K";
        return stream;
    }
    static bool rookMovement(int fromX, int fromY, int toX, int toY,
                             const std::vector<std::vector<ChessPiece*>> &board) {
        //Implement Rook movement
        if (toX == fromX) {
            if (toY > fromY) {
                int block {-1};
                for (int i = fromY+1; i < toY; ++i) {
                    if (board[fromX][i] != nullptr) {
                        block = i;
                        break;
                    }
                }
                return (block == -1 || toY <= block);
            }
            else {
                int block {-1};
                for (int i = fromY-1; i > toY; --i) {
                    if (board[fromX][i] != nullptr) {
                        block = i;
                        break;
                    }
                }
                return (block == -1 || toY >= block);
            }
        }
        else if (toY == fromY) {
            if (toX > fromX) {
                int block {-1};
                for (int i = fromX+1; i < toX; ++i) {
                    if (board[i][fromY] != nullptr) {
                        block = i;
                        break;
                    }
                }
                return (block == -1 || toX <= block);
            }
            else {
                int block {-1};
                for (int i = fromX-1; i > toX; --i) {
                    if (board[i][fromY] != nullptr) {
                        block = i;
                        break;
                    }
                }
                return (block == -1 || toX >= block);
            }
        }
        else { return false; }
    }

    [[nodiscard]] bool move (int fromX, int fromY, int toX, int toY,
                             const std::vector<std::vector<ChessPiece*>> &board) const override {
        return rookMovement(fromX, fromY, toX, toY, board);
    }
};

//Define Bishop class
class Bishop : public ChessPiece{
public:
    explicit Bishop(PieceColor color) : ChessPiece(PieceType::Bishop, color) {

    }
    std::ostream& operator<<(std::ostream& stream) const override {
        stream << "F";
        return stream;
    }

    static bool bishopMovement(int fromX, int fromY, int toX, int toY,
                               const std::vector<std::vector<ChessPiece*>> &board) {
        //Implement Bishop movement
        if (std::abs(fromY - toY) != std::abs(fromX - toX)) return false;
        if (toY > fromY && toX > fromX) {
            for (int i = fromX+1, j = fromY+1; i <= toX && j <= toY; ++i, ++j) {
                if (board[i][j] != nullptr) {
                    return (toX == i && toY == j);
                }
            }
            return true;
        }
        else if (toY < fromY && toX > fromX) {
            for (int i = fromX+1, j = fromY-1; i <= toX && j >= toY; ++i, --j) {
                if (board[i][j] != nullptr) {
                    return (toX == i && toY == j);
                }
            }
            return true;
        }
        else if (toY > fromY && toX < fromX) { //
            for (int i = fromX-1, j = fromY+1; i >= toX && j <= toY; --i, ++j) {
                if (board[i][j] != nullptr) {
                    return (toX == i && toY == j);
                }
            }
            return true;
        }
        else if (toY < fromY && toX < fromX) {
            for (int i = fromX-1, j = fromY-1; i >= toX && j >= toY; --i, --j) {
                if (board[i][j] != nullptr) {
                    return (toX == i && toY == j);
                }
            }
            return true;
        }
        else {
            return false;
        }
    }

    [[nodiscard]] bool move (int fromX, int fromY, int toX, int toY,
                             const std::vector<std::vector<ChessPiece*>> &board) const override {
        return bishopMovement(fromX,fromY,toX,toY,board);
    }
};

//Define Queen class
class Queen : public ChessPiece {

public:
    explicit Queen(PieceColor color) : ChessPiece(PieceType::Queen, color) {
        Rook rook(color);
        Bishop bishop(color);
    }
    std::ostream& operator<<(std::ostream& stream) const override {
        stream << "V";
        return stream;
    }
    [[nodiscard]] bool move (int fromX, int fromY, int toX, int toY,
                             const std::vector<std::vector<ChessPiece*>> &board) const override {
        //Implement Queen movement
        return (Rook::rookMovement(fromX, fromY, toX, toY, board) ||
                Bishop::bishopMovement(fromX, fromY, toX, toY, board));
    }
};

//Define Knight class
class Knight : public ChessPiece{
public:
    explicit Knight(PieceColor color) : ChessPiece(PieceType::Knight, color) {

    }
    std::ostream& operator<<(std::ostream& stream) const override {
        stream << "A";
        return stream;
    }
    [[nodiscard]] bool move (int fromX, int fromY, int toX, int toY,
                             const std::vector<std::vector<ChessPiece*>> &board) const override {
        if (sqrt(5) == std::sqrt(std::pow(toX - fromX, 2) + std::pow(toY - fromY, 2))) {
            return true;
        }
        return false;
    }
};

// Define the chess board class
class ChessBoard {
public:
    ChessBoard() {
        initializeBoard();
    }

    void displayBoard() const {
        // Display the current state of the board
        std::cout << "   0  1  2  3  4  5  6  7  \n";
        for (int i = 0; i < 8; ++i) {
            std::cout << i << " |";
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr) {
                    PieceColor color = board[i][j]->getColor();
                    char symbol = (color == PieceColor::White) ? 'w' : 'b';
                    std::cout << symbol;
                    board[i][j]->operator<<(std::cout);
                    std::cout << "|";
                } else {
                    std::cout << "__|";
                }
            }
            std::cout << " " << i <<  std::endl;
        }
        std::cout << "   0  1  2  3  4  5  6  7  \n";
        std::cout << std::endl;
    }

    void movePiece(int fromX, int fromY, int toX, int toY) {
        if (isValidMove(fromX, fromY, toX, toY)) {
            delete board[toX][toY]; // Remove any existing piece at destination
            board[toX][toY] = board[fromX][fromY];
            board[fromX][fromY] = nullptr;
            std::cout << "Piece moved successfully.\n" << std::endl;
            ChessBoard::totalMoveCount++;
        } else {
            std::cout << "Invalid move!\n" << std::endl;
        }
    }

    [[nodiscard]] static int* getInput() {
        // Input format: IntInt-IntInt / example: 45-71
        std::string temp;
        std::cout << ((ChessBoard::checkTurnColor() == PieceColor::White) ? "WHITE'S TURN: " : "BLACK'S TURN: ");
        std::getline(std::cin, temp);
        std::cout << std::endl;

        int* ptr = new int[4];
        int i = 0;
        for (char c : temp) {
            if (std::isdigit(c)) {
                ptr[i++] = (c - '0');
            }
        }
        return ptr;
    }

    [[nodiscard]] ChessPiece* getPiece(int x, int y) const {
        return this->board[x][y];
    }

private:
    void initializeBoard() {
        // Initialize the board with pieces
        board.resize(8, std::vector<ChessPiece*>(8, nullptr));
        // Place Pawns
        for (int i = 0; i < 8; ++i) {
            board[1][i] = new Pawn(PieceColor::Black);
            board[6][i] = new Pawn(PieceColor::White);
        }
        // Place Knights
        board[0][1] = new Knight(PieceColor::Black);
        board[0][6] = new Knight(PieceColor::Black);
        board[7][1] = new Knight(PieceColor::White);
        board[7][6] = new Knight(PieceColor::White);
        // Place Bishops
        board[0][2] = new Bishop(PieceColor::Black);
        board[0][5] = new Bishop(PieceColor::Black);
        board[7][2] = new Bishop(PieceColor::White);
        board[7][5] = new Bishop(PieceColor::White);
        // Place Rooks
        board[0][0] = new Rook(PieceColor::Black);
        board[0][7] = new Rook(PieceColor::Black);
        board[7][0] = new Rook(PieceColor::White);
        board[7][7] = new Rook(PieceColor::White);
        // Place Queens
        board[0][3] = new Queen(PieceColor::Black);
        board[7][3] = new Queen(PieceColor::White);
        // Place Kings
        board[0][4] = new King(PieceColor::Black);
        board[7][4] = new King(PieceColor::White);
    }
    std::vector<std::vector<ChessPiece*>> board; // 2D vector representing the board

    static int totalMoveCount;

    bool isValidMove(int fromX, int fromY, int toX, int toY) {
        // Boundary protection logic
        for (int i: {fromX, fromY, toX, toY}) {
            if (not(-1 < i && i < 8)) { return false; }
        }
        // Add validation logic here, e.g., checking piece movement rules
        if (board[fromX][fromY] == nullptr) {
            return false; // No piece at the starting position
        }
        if (board[fromX][fromY]->getColor() != checkTurnColor()) {
            return false; // Color turn check
        }
        if (board[toX][toY] != nullptr) {
            if (board[fromX][fromY]->getColor() == board[toX][toY]->getColor()) {
                return false; // Prohibit selected piece to replace same color target piece
            }
        }
        // For simplicity, we delegate to each specific move set function
        return board[fromX][fromY]->move(fromX, fromY, toX, toY, board);
    }

    static PieceColor checkTurnColor()
    {
        return (totalMoveCount % 2) ? PieceColor::Black : PieceColor::White;
    }
};

void RunChess() {
    ChessBoard board;
    while (Running) {
        board.displayBoard();
        int* arg = ChessBoard::getInput();
        board.movePiece(*arg, *(arg+1), *(arg+2), *(arg+3));
        delete [] arg;
    }
}

int ChessBoard::totalMoveCount = 0;

int main() {
    RunChess();
    return 0;
}