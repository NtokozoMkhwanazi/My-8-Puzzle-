#include <bits/stdc++.h>

using namespace std;

class node
{

public:
    vector<vector<char>> board;
    vector<node *> neighbors;
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

int startTocurrent(node *currBoard, node *startBoard)
{

    int misMatch = 0;

    for (int i = 0; i < currBoard->board.size(); i++)
    {
        for (int j = 0; j < currBoard->board.size(); j++)
        {
            if (currBoard->board[i][j] != startBoard->board[i][j])
            {
                misMatch = misMatch + 1; 
            }
        }
    }
   
    return misMatch;
}

int currentTofinal(node *currBoard, node *finBoard)
{

    int misMatch = 0;
    
    for (int i = 0; i < currBoard->board.size(); i++)
    {
        for (int j = 0; j < currBoard->board.size(); j++)
        {
            if (currBoard->board[i][j] != finBoard->board[i][j])
            {
                misMatch = misMatch + 1;
            }
        }
    }

    return misMatch;
}

int calculateLinearConflict(vector<vector<char>> board) {
    int linearConflict = 0;

    // check rows for linear conflict
    for (int i = 0; i < 3; i++) {
        int max = -1;
        for (int j = 0; j < 3; j++) {
            int tile = board[i][j];
            if (tile != '#' && (tile - 1) / 3 == i) {
                if (tile > max) {
                    max = tile;
                } else {
                    linearConflict += 2;
                }
            }
        }
    }

    // check columns for linear conflict
    for (int j = 0; j < 3; j++) {
        int max = -1;
        for (int i = 0; i < 3; i++) {
            int tile = board[i][j];
            if (tile != '#' && tile % 3 == j + 1) {
                if (tile > max) {
                    max = tile;
                } else {
                    linearConflict += 2;
                }
            }
        }
    }

    return linearConflict;
}

int Manhattan_End_distance(node* current,node* end){

	pair<int,int>end_xy = emptySpot(end->board);
	pair<int,int>current_xy =  emptySpot(current->board);
	
	
	int end_i = end_xy.first;
	int end_j = end_xy.second;
	
	int i = current_xy.first;
	int j = current_xy.second; 

    return abs(i - end_i) + abs(j - end_j);

}
int Manhattan_Start_distance(node* current,node* start) {
	
	pair<int,int>start_xy = emptySpot(start->board);
	pair<int,int>current_xy =  emptySpot(current->board);
	
	int start_i = start_xy.first;
	int start_j = start_xy.second;
	
	int i = current_xy.first;
	int j = current_xy.second; 
        
    return abs(i - start_i) + abs(j - start_j);
 }

/// work in progress.......
bool isGoalState(const std::vector<std::vector<char>>& board, const std::vector<std::vector<char>>& goalBoard) {
    return board == goalBoard;
}

vector<string> reverse(vector<string>& moves) {
    vector<string> reversedMoves;
    for (int i = moves.size() - 1; i >= 0; --i) {
        reversedMoves.push_back(moves[i]);
    }
    return reversedMoves;
}

node* AStarSearch(vector<vector<char>>& startBoard, vector<vector<char>>& goalBoard) {

    priority_queue<node*, vector<node*>, CompareNodes> openList;
    map<vector<vector<char>>, bool> visited;

    node* startNode = new node();
    node* goalNode = new node();

    createNode(goalNode, goalBoard);
    createNode(startNode, startBoard);

    startNode->h = Manhattan_Start_distance(startNode, goalNode);
    startNode->f = startNode->g + startNode->h;
    startNode->depth = 0;

    openList.push(startNode);
    node* solutionNode = nullptr;

    while (!openList.empty()) {
        node* currentNode = openList.top();
        openList.pop();

        if (isGoalState(currentNode->board, goalBoard)) {
            solutionNode = currentNode;
            break;
        }

        visited[currentNode->board] = true;

        for (node* nextMove : generateMoves(currentNode->board, currentNode)) {
            nextMove->g = currentNode->g + 1;
            nextMove->h = Manhattan_Start_distance(nextMove, goalNode);
            nextMove->f = nextMove->g + nextMove->h;

            if (visited.find(nextMove->board) == visited.end()) {
                insertNode(currentNode, nextMove, nextMove->move, currentNode->depth + 1, nextMove->costMove);
                nextMove->parent = currentNode;
                openList.push(nextMove);
            } else {
                delete nextMove;
            }
        }
    }

    return solutionNode;
}
void printTree(node* root) {
    if (root == nullptr) {
        return;
    }

    cout << "Depth: " << root->depth << endl;
    cout << "Move: " << root->move << endl;
    print(root->board);

    if (root->LEFT != nullptr) {
        cout << "Left:" << endl;
        printTree(root->LEFT);
    }
    if (root->UP != nullptr) {
        cout << "Up:" << endl;
        printTree(root->UP);
    }
    if (root->RIGHT != nullptr) {
        cout << "Right:" << endl;
        printTree(root->RIGHT);
    }
    if (root->DOWN != nullptr) {
        cout << "Down:" << endl;
        printTree(root->DOWN);
    }
}

int main() {

	//string name = "#12345678";
    //string goal = "31245867#";
    
    //complex
   string name = "15#764238";
   string goal = "82#547361";

    vector<vector<char>> grid;
    vector<vector<char>> goal_Grid;

    grid = form_Grid(name, grid);
    goal_Grid = form_Grid(goal, goal_Grid);

    cout << "Goal Board:" << endl;
    print(goal_Grid);

    cout << "Start Board:" << endl;
    print(grid);

    node* solution = AStarSearch(grid, goal_Grid);

    if (solution != nullptr) {
        cout << "Solution Path:" << endl;
        printTree(solution);
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}


