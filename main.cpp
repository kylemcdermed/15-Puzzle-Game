// 15 Puzzle Game

class Board;
class Direction;
const int g_consoleLines {25};

class Direction {

private:

    char m_directionInput {};

public:

    friend class Point;
    friend class Board;

    enum Type { 

        up, // 1
        down, // 2
        left, // 3
        right, // 4
        max_directions, // 5

    };

    Direction() = default;

    Direction(char direction)
        : m_directionInput {direction} {}

    friend std::ostream& operator<<(std::ostream& out, const Direction& d) {

        out << d.m_directionInput;

        return out;

    }

    Direction operator-() const; 

    operator Direction() const { 

        return m_directionInput;

    }

    Type getType() const { // get direction

        switch (m_directionInput) {

            case 'w':
                return up;
            case 's':
                return down;
            case 'a':
                return left;
            case 'd':
                return right;
            default:
                return max_directions;

        }

    }

    operator std::string() const {

        switch (m_directionInput) {

            case 'w':
                return "up";
            case 's':
                return "down";
            case 'a':
                return "left";
            case 'd':
                return "right";
            default:
                return "invalid";

        }

    }

    static Type randomDirection() {

        switch(Random::get(0, max_directions - 1)) {

        case up:
            return down;
        case down:
            return up;
        case left:
            return right;
        case right:
            return left;
        default:
            return max_directions;

        }
        
    }

    void printRandomDirection() {

        for (int i {}; i < Direction::Type::max_directions; ++i) {
            Direction::Type dir = Direction::randomDirection();
            cout << "Generating random direction... ";
            switch (dir) {

                case Direction::up:
                    cout << "up\n";
                    break;
                case Direction::down:
                    cout << "down\n";
                    break;
                case Direction::left:
                    cout << "left\n";
                    break;
                case Direction::right:
                    cout << "right\n";
                    break;
                default:
                    cout << "invalid direction.\n";
                    break;

            }
        }
    }

};

Direction Direction::operator-() const {

    switch (getType()) {

        case up:
            return down;
        case down:
            return up;
        case left:
            return right;
        case right:
            return left;
        default:
            return max_directions;

    }

}

class Point {

private:

    int m_x {};
    int m_y {};

public :

    friend class Board;
    friend class Point;

    Point(int x=0, int y=0)
        : m_x {x}
        , m_y {y} {}

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {

        out << "(" << p.m_x << ", " << p.m_y << ")\n";

        return out;

    }

    bool operator==(const Point& p) {

        return (m_x == p.m_x && m_y == p.m_y);

    }

    bool operator!=(const Point& p) {

        return (!(m_x == p.m_x && m_y == p.m_y));

    }

    int getX() const {return m_x;}

    int getY() const {return m_y;}

    Point getAdjacentPoint(Direction::Type d) const {

        switch(d) {

            case Direction::up:
                return Point {m_x - 1, m_y};
            case Direction::down:
                return Point {m_x + 1, m_y};
            case Direction::right:
                return Point {m_x, m_y + 1};
            case Direction::left:
                return Point {m_x, m_y - 1};
            default:
                return *this;

        }
    }

};

namespace UserInput {

    char getCommandFromUser() {

        char userInput {};

        cout << "Enter a valid command. ('w'=up, 'a'=left, 's'=down, 'd'=right, or 'q'=quit.)\n";

        cin >> userInput;

        cout << '\n';

        return userInput;
    }

     // Function to convert char command to Direction
    Direction::Type charToDirection(char ch) {
        switch(ch) {
            case 'w':
                return Direction::up;
            case 'a':
                return Direction::left;
            case 's':
                return Direction::down;
            case 'd':
                return Direction::right;
            default:
                return Direction::max_directions;
        }
    }

}

class Tile {

private:

    int m_tile {};
    int m_missingTile {0};
    bool m_isItTheMissingTile {false};

public:

    friend class Board;
    friend class Point;

    Tile(int tile)
        : m_tile {tile}
        , m_missingTile {0}
        , m_isItTheMissingTile {false} {}

    friend std::ostream& operator<<(std::ostream& out, const Tile& t) {

        if (t.m_tile == t.m_missingTile) {
            out << std::setw(4) << " ";
        } else {
            out << std::setw(3) << t.m_tile << " ";
        }

        return out;

    }

    friend bool operator!=(const Tile& t1, const Tile& t2);

    bool operator==(int tileValue) const {

        return (m_tile == tileValue);

    }

    bool isEmpty() const {

        return (m_tile == m_missingTile);

    }

    int getNum() const {

        return m_tile;

    }

};

bool operator!=(const Tile& t1, const Tile& t2) {

    return (t1.m_tile != t2.m_tile);

}

class Board {

private:

    std::array<std::array<Tile,4>, 4> m_boardArray {
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };

public:

    Board () {

        randomize();

    }

    friend std::ostream& operator<<(std::ostream& out, const Board& b) {

        for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (b.m_boardArray[row][col].isEmpty()) {
                out << std::setw(4) << " ";
            } else {
                out << std::setw(4) << b.m_boardArray[row][col].getNum();
            }
        }
        out << '\n';
    }
    return out;


    }

    friend bool operator==(const Board& b1, const Board& b2) {

        for (int i{}; i < 4; ++i) {
            for (int j{}; j < 4; ++j) {
                if (b1.m_boardArray[i][j] != b2.m_boardArray[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void printLines();

    bool validPoint(const Point& p) const { // is point inside or outside board

        return (p.m_x >= 0 && p.m_x < 4 && p.m_y >= 0 && p.m_y < 4);

    }

    Point locateEmptyTile() const {

        for (int row {}; row < 4; ++row) {
            for (int col {}; col < 4; ++col) {
                if (m_boardArray[row][col].isEmpty()) {
                    return Point{row, col};
                }
            }
        }
        return Point(-1,-1);
    }

    void swapTiles(const Point& p1, const Point& p2);

    bool moveTile(Direction::Type dir);

    void randomize() {

        srand(static_cast<unsigned>(time(nullptr)));

        for (int i{}; i < 1000; ++i) {
            Direction::Type randomDir = Direction::randomDirection();
            Point emptyTile = locateEmptyTile();

            Point adjacentPoint = emptyTile.getAdjacentPoint(randomDir);

            if (validPoint(adjacentPoint)) {
                swapTiles(emptyTile, adjacentPoint);
            }
        }

    }

    bool playerWon() const {

        Board solvedBoard;

        for (int i{}; i < 4; ++i) {
            for (int j{}; j < 4; ++j) {
                if (m_boardArray[i][j] != solvedBoard.m_boardArray[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void updateBoard();

};

void Board::updateBoard() {

    cout << *this;

}

void Board::swapTiles(const Point& p1, const Point& p2) {

    Tile temp = m_boardArray[p1.m_x][p1.m_y];
    m_boardArray[p1.m_x][p1.m_y] = m_boardArray[p2.m_x][p2.m_y];
    m_boardArray[p2.m_x][p2.m_y] = temp;

}

bool Board::moveTile(Direction::Type dir) {

    Point emptyTile = locateEmptyTile();
    Point adjacentTile = emptyTile.getAdjacentPoint(dir);

    if (validPoint(adjacentTile)) {
        // swap tiles
        swapTiles(emptyTile, adjacentTile);
        return true;
    }
    return false;

}

void Board::printLines() {

    for (int i {}; i < g_consoleLines; ++i) {
        cout << '\n';
    }

}

int main() {

    Board board{};
    // Call updateBoard to print the initial board
    board.printLines();
    board.updateBoard();

    // Main game loop
     while (true) {
        // Print the current board after each input

        char ch{ UserInput::getCommandFromUser() };

        // Handle non-direction commands
        if (ch == 'q') {
            break; // Exit the loop if the user quits
        }

        // Handle direction commands
        Direction::Type dirType = UserInput::charToDirection(ch);

        bool userMoved { board.moveTile(dirType) };
        if (userMoved) {
            board.updateBoard();
        }

        if (board.playerWon()) {
            cout << "You won!\n";
            break; // Exit the loop if the player wins
        }
    }


}
