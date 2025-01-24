#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

class Node {
public:
    vector<vector<char>> board;
    Node* parent;
    int g, h, f;
    string move;
};

void createNode(Node* Node, const vector<vector<char>>& grid) {
    Node->board = grid;
    Node->parent = nullptr;
    Node->g = Node->h = Node->f = 0;
}

pair<int, int> emptySpot(const vector<vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '#') {
                return {i, j};
            }
        }
    }
    return {-1, -1};  // Should never happen
}

vector<vector<char>> formGrid(const string& puzzle) {
    vector<vector<char>> grid(3, vector<char>(3));
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = puzzle[count++];
        }
    }
    return grid;
}

struct CompareNodes {
    bool operator()(const Node* node1, const Node* node2) const {
        return node1->f > node2->f;
    }
};

vector<Node*> generateMoves(const vector<vector<char>>& grid, Node* currentNode) {
    pair<int, int> empty = emptySpot(currentNode->board);
    int emptyRow = empty.first;
    int emptyCol = empty.second;

    vector<Node*> nodes;
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<string> MOVES = {"UP", "DOWN", "LEFT", "RIGHT"};

    for (int i = 0; i < 4; i++) {
        int newRow = emptyRow + directions[i][0];
        int newCol = emptyCol + directions[i][1];

        if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size()) {
            vector<vector<char>> newGrid = grid;
            swap(newGrid[emptyRow][emptyCol], newGrid[newRow][newCol]);

            Node* newNode = new Node();
            createNode(newNode, newGrid);
            newNode->move = MOVES[i];
            newNode->parent = currentNode;
            nodes.push_back(newNode);
        }
    }

    return nodes;
}

bool isGoalState(const vector<vector<char>>& board, const vector<vector<char>>& goalBoard) {
    return board == goalBoard;
}

Node* AStarSearch(vector<vector<char>>& startBoard, vector<vector<char>>& goalBoard) {
    priority_queue<Node*, vector<Node*>, CompareNodes> openList;
    map<vector<vector<char>>, bool> visited;

    Node* startNode = new Node();
    createNode(startNode, startBoard);
    startNode->h = abs(emptySpot(startBoard).first - emptySpot(goalBoard).first) + abs(emptySpot(startBoard).second - emptySpot(goalBoard).second);
    startNode->f = startNode->g + startNode->h;

    openList.push(startNode);

    while (!openList.empty()) {
        Node* currentNode = openList.top();
        openList.pop();

        if (isGoalState(currentNode->board, goalBoard)) {
            return currentNode;
        }

        visited[currentNode->board] = true;

        for (Node* nextMove : generateMoves(currentNode->board, currentNode)) {
            nextMove->g = currentNode->g + 1;
            nextMove->h = abs(emptySpot(nextMove->board).first - emptySpot(goalBoard).first) + abs(emptySpot(nextMove->board).second - emptySpot(goalBoard).second);
            nextMove->f = nextMove->g + nextMove->h;

            if (visited.find(nextMove->board) == visited.end()) {
                openList.push(nextMove);
            } else {
                delete nextMove;
            }
        }
    }

    return nullptr;
}

void drawBoard(sf::RenderWindow &window, vector<vector<char>> &board) {
    const int tileSize = 100;
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            for (int i = 1; i < 3; ++i) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(i * tileSize, 0), sf::Color::White),
                    sf::Vertex(sf::Vector2f(i * tileSize, window.getSize().y), sf::Color::White)
                };
                window.draw(line, 2, sf::Lines);
                sf::Vertex line2[] = {
                    sf::Vertex(sf::Vector2f(0, i * tileSize), sf::Color::White),
                    sf::Vertex(sf::Vector2f(window.getSize().x, i * tileSize), sf::Color::White)
                };
                window.draw(line2, 2, sf::Lines);
            }
            tile.setPosition(j * tileSize, i * tileSize);

            if (board[i][j] == '#') {
                tile.setFillColor(sf::Color::Red);  // Empty space
            } else {
                tile.setFillColor(sf::Color::Black);  // Numbered tiles
            }

            window.draw(tile);

            if (board[i][j] != '#') {
                sf::Text text;
                text.setFont(font);
                text.setString(std::string(1, board[i][j]));
                text.setCharacterSize(60);
                text.setFillColor(sf::Color::White);
                text.setPosition(j * tileSize + tileSize / 4, i * tileSize + tileSize / 4);
                                  
                window.draw(text);
            }
        }
    }
}

void displaySolution(sf::RenderWindow &window, Node *solution) {
    vector<Node *> path;
    for (Node *curr = solution; curr != nullptr; curr = curr->parent) {
        path.push_back(curr);
    }
    std::reverse(path.begin(), path.end());

    const int delay = 600; // Milliseconds

    // Iterate through the solution path and display each board state with delay
    for (auto &step : path) {
        window.clear(sf::Color::White);  // Clear window
        drawBoard(window, step->board);  // Draw the current board state
        window.display();  // Refresh the window

        // Wait for a specified delay
        sf::sleep(sf::milliseconds(delay));

        // Check for any window events (e.g., closing)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close window if requested
            }
        }
    }
}

int main() {
    // Start and goal grid for 3x3 puzzle
    //1 2 3
    //4 5 6
    //7 8 #
    
    vector<vector<char>> startGrid = formGrid("#12345678");
    vector<vector<char>> goalGrid = formGrid("12345678#");

    sf::RenderWindow window(sf::VideoMode(300, 300), "Puzzle Solver");
    window.setFramerateLimit(60);

    Node* solution = AStarSearch(startGrid, goalGrid);

    if (solution != nullptr) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Display the solution step by step
            window.clear(sf::Color::White);
            displaySolution(window, solution);
            window.display();
        
        
        }
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}
