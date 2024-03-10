#include <iostream>
#include <vector>

using std::string;

class Chess {
public:
    class Piece;
    class Board {
    private:
        std::vector<std::vector<string>> chessboard{8, std::vector<string>(8, "#")};
    public:
        Board()
        = default;

        void show_board() const {
            for (auto &i: this->chessboard) {
                for (const auto &j: i) {
                    std::cout << j;
                }
                std::cout << std::endl;
            }
        }

        [[nodiscard]] string show_piece_in_loc(int x, int y) const {
            return this->chessboard[x][y];
        }
    };

    class Player {
    private:
        std::string side;
        static bool pick_sides;
    public:
        Player() {
            if (not Chess::Player::pick_sides) {
                this->side = "White";
                Chess::Player::pick_sides += 1;
            } else {
                this->side = "Black";
                Chess::Player::pick_sides -= 1;
            }
        }

        [[nodiscard]] Piece *select_piece(Board *board, int x_loc, int y_loc) const {
            if (board->show_piece_in_loc(x_loc, y_loc) != "#") {
                return
            }
        }
    };

    class Piece {
    protected:
        int x_loc;
        int y_loc;
        static int piece_color_counter;
    public:
        Piece(int x, int y) : x_loc(x), y_loc(y)
        {
            Chess::Piece::piece_color_counter++;
        }
        virtual void move()
        {

        }
    };
    class King : protected Piece {
    public:
        King(int x, int y) : Piece(x, y)
        {

        }
        void move() override
        {

        }
    };
    class Queen : protected Piece {
    public:
        Queen(int x, int y) : Piece(x, y)
        {

        }
        void move() override
        {

        }
    };
    class Rook : protected Piece {
    public:
        Rook(int x, int y) : Piece(x, y)
        {

        }
        void move() override
        {

        }
    };
    class Bishop : protected Piece {
    public:
        Bishop(int x, int y) : Piece(x, y)
        {

        }
        void move() override
        {

        }
    };
    class Knight : protected Piece {
    public:
        Knight(int x, int y) : Piece(x, y)
        {

        }
        void move() override
        {

        }
    };
    class Paw : protected Piece {
    public:
        Paw(int x, int y) : Piece(x, y)
        {

        }
        void move() override
        {

        }
    };
};
int Chess::Piece::piece_color_counter = 0;

int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
