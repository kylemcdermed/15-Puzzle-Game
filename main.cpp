// 15 Puzzle Game

constexpr int g_consoleLines {5};

class Direction {

public:

    enum Type {

        up,
        left,
        down,
        right,
        maxDirections,

    };

    Direction() = default;

    Direction(Type type)
        : m_direction {type} {}

    static std::string directionToString(Type d) {

        switch (d) {
            case up: return "up";
            case left: return "left";
            case down: return "down";
            case right: return "right";
            default: return "unknown";
        }

    }

    std::string toString() const {return directionToString(m_direction);}

    void setDirection(Type d) {m_direction = d;}

    Type getDirection() {return m_direction;}

    int operator-() const {return -m_direction;}

    friend std::ostream& operator<<(std::ostream& out, const Direction& d) {

        out << d.m_direction;
        return out;

    }

    static Type randomDirection() {

        int random = Random::get(0,3);

        return static_cast<Type>(random);

    }

    static Type charToDirection(char c) {

        switch (c) {
            case 'w': return up;
            case 'a': return left;
            case 's': return down;
            case 'd': return right;
            default: throw std::invalid_argument("Invalid direction character");
        }

    }

private:

    Type m_direction;

};

struct Point {

public:

    int m_x, m_y;

    Point(int x=0, int y=0)
        : m_x {x}, m_y {y} {}

    Point getAdjacentPoint(Direction d) {

        if (d.getDirection() == Direction::up) {
            return Point{m_x, m_y - 1};
        } else if (d.getDirection() == Direction::down) {
            return Point{m_x, m_y + 1};
        } else if (d.getDirection() == Direction::left) {
            return Point{m_x - 1, m_y};
        } else if (d.getDirection() == Direction::right) {
            return Point{m_x + 1, m_y};
        }

    }

    friend bool operator==(const Point& p1, const Point& p2) {

        return p1.m_x == p2.m_x && p1.m_y == p2.m_y;

    }

    friend bool operator!=(const Point& p1, const Point& p2) {

        return p1.m_x != p2.m_x || p1.m_y != p2.m_y;

    }

};

class Tile {

private:

    int m_tile;

public:

    Tile() : m_tile{0} {}

    Tile(int tile)
        : m_tile {tile} {}

    friend std::ostream& operator<<(std::ostream& out, const Tile& t) {

        if (t.m_tile == 0) {
            out << std::setw(4) << ' ';  
        } else {
            out << std::setw(4) << t.m_tile; 
        }
        return out;

    }

    bool operator==(const Tile& t) const {

        return m_tile == t.m_tile;

    }

    bool isEmpty() {

        return m_tile == 0;

    }

    int& getNum() {

        return m_tile;

    }

    bool operator!=(int value) const {

        return m_tile != value;

    }

    Tile getTile() const {

        return m_tile;

    }

};

class Board {

private:

    std::array<std::array<Tile, 4>, 4> m_board;

public:

    Board() {

        for (int i=0; i < g_consoleLines; ++i) {
            cout << '\n';
        }

        int value = 1;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == 3 && j == 3) {
                    m_board[i][j] = Tile {0};  // 0 is empty space
                } else {
                    m_board[i][j] = value++;
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Board& b) {

        for (int i{0}; i < 4; ++i) {
            for (int j{0}; j < 4; ++j) {
                if (b.m_board[i][j] != 0) {
                    out << b.m_board[i][j] << '\t';
                } else {
                    out << ' ' << '\t';
                }
            }
            out << '\n';
        }
        return out;
    }

    bool operator==(const Board& b) const {

        return m_board == b.m_board;

    }

    bool validPoint(Point p) {

        return p.m_x >= 0 && p.m_x < 4 && p.m_y >= 0 && p.m_y < 4;

    }

    Point emptyTile() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (m_board[i][j].isEmpty()) { // Check if the tile is empty
                    return Point{i, j}; // Return the position of the empty tile
                }
            }
        }
        return Point{-1, -1}; // Return an invalid Point if no empty tile is found
    }

    void swapTiles(Point& p1, Point& p2) {

        std::swap(m_board[p1.m_x][p1.m_y], m_board[p2.m_x][p2.m_y]);

    }

    bool moveDirection(Direction& dir) {
        Point empty = emptyTile();
        Point adjacent = empty.getAdjacentPoint(dir);

        if (validPoint(adjacent)) {
            swapTiles(empty, adjacent);
            return true;
        }
        return false;
    }

    void randomizeBoard() {
        Direction d;
        for (int i{0}; i < 1000; ++i) {
            Direction::Type randomDir = Direction::randomDirection();
            d.setDirection(randomDir);
            Point empty = emptyTile();
            Point adjacent = empty.getAdjacentPoint(d);

            if (validPoint(adjacent)) {
                swapTiles(empty, adjacent); // Access member function directly
            }
        }
    }

    bool playerWon(const Board& b) {

        if (b.m_board == m_board) {
            return true;
        }
        return false;
    }

};

namespace UserInput {

    int getCommandFromUser(char c) {
        switch (c) {
        case 'w':
            return 0;
        case 'a':
            return 1;
        case 's':
            return 2;
        case 'd':
            return 3;
        case 'q':
            return 4;
        default:
            cout << c << '\n';
            cin.ignore();
            cin.clear();
    }
        return c;
    }

}

int main() {

    Board board;
    board.randomizeBoard();
    cout << board;

    bool end {false};
    Direction direction;

    // Generate and print random directions
    for (int i {0}; i < 4; ++i) {
        Direction::Type randomDir = Direction::randomDirection();
        direction.setDirection(randomDir);
        cout << "Generating random direction... " << direction.toString() << '\n';
    }

    cout << "\nEnter a valid command (w=up/a=left/s=down/d=right/q=quit): ";

    while (!end) {
        char c;
        cin >> c;

        try {
            Direction::Type dir = Direction::charToDirection(c);
            direction.setDirection(dir);
            cout << "You entered direction: " << direction.toString() << '\n';
            board.moveDirection(direction);
            cout << board;
            if (board.playerWon(board)) {
                end = true;
            }
        } catch (const std::invalid_argument&) {
            if (c == 'q') {
                end = true;
                cout << "\n\nBye!\n\n";
                break;
            } else {
                cout << "Invalid input, please enter w, a, s, d, or q.\n";
            }
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!end) {
            cout << "\nEnter a valid command (w=up/a=left/s=down/d=right/q=quit): ";
        } else if (end){
            cout << "\n\nYou won!\n\n";
        }
    }

    cout << "Game over.\n";

    return 0;

}
