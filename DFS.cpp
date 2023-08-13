#include <bits/stdc++.h>


using namespace std;

class node
{

public:
    vector<vector<char>> board;
    vector<node *> neighbors;
    bool visited;
    node *parent;
    node *LEFT;
    node *RIGHT;
    node *UP;
    node *DOWN;
    int depth;
    string move;
    int costMove;
    int g;
    int h;
    int f;
};

void createNode(node* Node,vector<vector<char>>grid){
	
    Node->board = grid;
    Node->neighbors; // not yet generated
    Node->visited = false;
    Node->parent = nullptr;
    Node->LEFT = nullptr;
    Node->RIGHT = nullptr;
    Node->UP = nullptr;
    Node->DOWN = nullptr;
    Node->move;
    Node->depth;
    Node->costMove;
    Node->g;
    Node->h;
    Node->f;
    
}

struct CompareNodes {
    bool operator()(const node* node1, const node* node2) const {
  
        // Compare nodes based on their f values
        // Smaller f value has higher priority
  
        return node1->f > node2->f;
    }
};

void print(vector<vector<char>> grid)
{
    
    if (!grid.empty())
    {
        cout <<"--------"<< endl;
        for (vector<char> j : grid)
        {
            cout <<"|";
            for (char i : j)
            {
                cout << i << "|";
            }
            cout << endl;
        }
         cout << "--------" << endl;
    }
   
}

void insertNode(node *root, node *Node, string Move, int depth,int cost) {
    if (root == NULL) {
        return;
    }

    if (Move == "UP") {
        if (root->UP != nullptr) {
            insertNode(root->UP, Node, Move, depth,cost);
        } else {
            root->UP = Node;
            root->UP->depth = depth;
            root->UP->move = Move;
            root->UP->costMove = cost;
        }
    } else if (Move == "DOWN") {
        if (root->DOWN != nullptr) {
            insertNode(root->DOWN, Node, Move, depth,cost);
        } else {
            root->DOWN = Node;
            root->DOWN->depth = depth;
            root->DOWN->move = Move;
            root->DOWN->costMove = cost;
        }
    } else if (Move == "LEFT") {
        if (root->LEFT != nullptr) {
            insertNode(root->LEFT, Node, Move, depth,cost);
        } else {
            root->LEFT = Node;
            root->LEFT->depth = depth;
            root->LEFT->move = Move;
            root->LEFT->costMove = cost;
        }
    } else if (Move == "RIGHT") {
        if (root->RIGHT != nullptr) {
            insertNode(root->RIGHT, Node, Move, depth,cost);
        } else {
            root->RIGHT = Node;
            root->RIGHT->depth = depth;
            root->RIGHT->move = Move;
            root->RIGHT->costMove = cost;
        }
    }
}

pair<int, int> emptySpot(vector<vector<char>> grid)
{
    pair<int, int> Co;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.size(); j++)
        {

            if (grid[i][j] == '#')
            {
                Co.first = i;
                Co.second = j;
            }
        }
    }
    return Co;
}

vector<vector<char>> form_Grid(string puzzle, vector<vector<char>> grid)
{

    int N = 3;
    int count = 0;
    for (int j = 0; j < N; j++)
    {
        vector<char> rows;
        for (int i = 0; i < N; i++)
        {
            rows.push_back(puzzle[count]);
            count++;
        }
        grid.push_back(rows);
    }
    return grid;
}


vector<node*> generateMoves(const vector<vector<char>>& grid, node* currentNode) {
    
    // Find the empty spot in the grid
    pair<int,int> empty =  emptySpot(currentNode->board);
    int emptyRow = empty.first;
    int emptyCol = empty.second;
    
    vector<node*> nodes;

    vector<vector<int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    vector<string> MOVES = { "UP", "DOWN", "LEFT", "RIGHT" };

    for (int i = 0; i < 4; i++) {
        int newRow = emptyRow + directions[i][0];
        int newCol = emptyCol + directions[i][1];

        if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size()) {
            vector<vector<char>> newGrid = grid;
            swap(newGrid[emptyRow][emptyCol], newGrid[newRow][newCol]);

            node* newNode = new node();
            createNode(newNode, newGrid);
            newNode->move = MOVES[i];
            nodes.push_back(newNode);
        }
    }

    return nodes;
}



node* createTree(vector<node *> Validated_Moves,node *start) {
    
    
    for (auto grid : Validated_Moves) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid->board[i][j] == '#') {
                    insertNode(start, grid, grid->move, grid->depth,grid->costMove);
                }
            }
        }
    }
    return start;

}


node* insert(node* currentNode,node* copyNode,node* start){

         vector<node *> T = generateMoves(currentNode->board,currentNode);
		 
         return createTree(T,start);

}


bool isGoalState(const vector<vector<char>>& board, const vector<vector<char>>& goalBoard) {
    return board == goalBoard;
}


node* dfs(vector<vector<char>>& startBoard, vector<vector<char>>& goalBoard) {
    node* start = new node();
    node* end = new node();

    createNode(start, startBoard);
    createNode(end, goalBoard);

    stack<node*> stack;
    stack.push(start);

    while (!stack.empty()) {
        node* curr = stack.top();
        stack.pop();

        if (isGoalState(curr->board, goalBoard)) {
            return curr;
        }

        curr->visited = true;

        vector<node*> moves = generateMoves(curr->board, curr);
        for (node* next : moves) {
            if (next != nullptr && !next->visited) {
                next->parent = curr;
                next->g = curr->g + next->costMove; // Update g value
                next->depth = curr->depth + 1; 
                stack.push(next);
            } else {
                delete next;
            }
        }
    }

    return nullptr;
}


void printTree(node* root) {
    if (root == nullptr) {
        return;
    }

    if (root->parent != nullptr) {
        cout << "Move: " << root->move << endl;
        cout << "Depth: "<<root->depth <<endl;
        print(root->board);
    } else {
        cout << "Start Board:" << endl;
        print(root->board);
    }

    if (root->LEFT != nullptr) {
        printTree(root->LEFT);
    }
    if (root->UP != nullptr) {
        printTree(root->UP);
    }
    if (root->RIGHT != nullptr) {
        printTree(root->RIGHT);
    }
    if (root->DOWN != nullptr) {
        printTree(root->DOWN);
    }
}



int main() {


    // Load boards from a file
    ifstream file("boards.txt");
    if (!file) {
        cerr << "Error opening file: boards.txt" << endl;
        return 1;
    }

    string line;
    int puzzleNumber = 1;

    while (getline(file, line)) {
        istringstream iss(line);
        string startBoard, endBoard;

        if (iss >> startBoard >> endBoard) {
            vector<vector<char>> startGrid = form_Grid(startBoard, vector<vector<char>>());
            vector<vector<char>> goalGrid = form_Grid(endBoard, vector<vector<char>>());

            cout << "Puzzle #" << puzzleNumber << endl;

            cout << "Start Board:" << endl;
            print(startGrid);

            cout << "Goal Board:" << endl;
            print(goalGrid);

            node* solution = dfs(startGrid, goalGrid);

            if (solution != nullptr) {
                cout << "Solution Path:" << endl;
                printTree(solution);
            } else {
                cout << "No solution" << endl;
            }

            ++puzzleNumber;
        }
    }

    return 0;
}


