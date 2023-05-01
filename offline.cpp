#include <bits/stdc++.h>

using namespace std;

class node
{

public:
    vector<vector<char>> board;
    node *LEFT;
    node *RIGHT;
    node *UP;
    node *DOWN;
    int depth;
    string move;
};

void print(vector<vector<char>> grid)
{
    cout << "--------" << endl;
    if (!grid.empty())
    {
        for (vector<char> j : grid)
        {
            cout << "|";
            for (char i : j)
            {
                cout << i << " ";
            }
            cout << "|";
            cout << endl;
        }
    }
    cout << "--------" << endl;
}
void createNode(node *Node, vector<vector<char>> grid)
{

    Node->board = grid;
    Node->LEFT = nullptr;
    Node->RIGHT = nullptr;
    Node->UP = nullptr;
    Node->DOWN = nullptr;
    int depth;
    string move;
}


void insertNode(node *root, node *Node, string Move, int depth) {
    if (root == NULL) {
        return;
    }

    if (Move == "UP") {
        if (root->UP != nullptr) {
            insertNode(root->UP, Node, Move, depth + 1);
        } else {
            root->UP = Node;
            root->UP->depth = depth + 1;
            root->UP->move = Move;
        }
    } else if (Move == "DOWN") {
        if (root->DOWN != nullptr) {
            insertNode(root->DOWN, Node, Move, depth + 1);
        } else {
            root->DOWN = Node;
            root->DOWN->depth = depth + 1;
            root->DOWN->move = Move;
        }
    } else if (Move == "LEFT") {
        if (root->LEFT != nullptr) {
            insertNode(root->LEFT, Node, Move, depth + 1);
        } else {
            root->LEFT = Node;
            root->LEFT->depth = depth + 1;
            root->LEFT->move = Move;
        }
    } else if (Move == "RIGHT") {
        if (root->RIGHT != nullptr) {
            insertNode(root->RIGHT, Node, Move, depth + 1);
        } else {
            root->RIGHT = Node;
            root->RIGHT->depth = depth + 1;
            root->RIGHT->move = Move;
        }
    }
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

map<string, node *> generateMoves(vector<vector<char>> grid, vector<vector<char>> copyOfgrid)
{

    vector<vector<vector<char>>> grids;
    vector<string> MOVES;

    for (unsigned long j = 0; j < grid.size(); j++)
    {
        for (unsigned long i = 0; i < grid.size(); i++)
        {
            if (grid[j][i] == '#')
            {

                if (j > 0 && grid[j - 1][i] != 0)
                {
                    int currtemp = grid[j - 1][i];
                    int temp = grid[j][i];
                    grid[j - 1][i] = temp;
                    grid[j][i] = currtemp;

                    if (isdigit(grid[j][i]))
                        grids.push_back(grid);
                    MOVES.push_back("UP");

                    grid = copyOfgrid;
                }
                if (j < grid.size() - 1 && grid[j + 1][i] != 0)
                {
                    int currtemp = grid[j + 1][i];
                    int temp = grid[j][i];
                    grid[j + 1][i] = temp;
                    grid[j][i] = currtemp;

                    if (isdigit(grid[j][i]))
                        grids.push_back(grid);
                    MOVES.push_back("DOWN");

                    grid = copyOfgrid;
                }

                if (i > 0 && grid[j][i - 1] != 0)
                {
                    int currtemp = grid[j][i - 1];
                    int temp = grid[j][i];
                    grid[j][i - 1] = temp;
                    grid[j][i] = currtemp;

                    if (isdigit(grid[j][i]))
                        grids.push_back(grid);
                    MOVES.push_back("LEFT");

                    grid = copyOfgrid;
                }

                if (i < grid.size() - 1 && grid[j][i + 1] != 0)
                {
                    int currtemp = grid[j][i + 1];
                    int temp = grid[j][i];
                    grid[j][i + 1] = temp;
                    grid[j][i] = currtemp;

                    if (isdigit(grid[j][i]))
                        grids.push_back(grid);
                    MOVES.push_back("RIGHT");
                    grid = copyOfgrid;
                }
            }
        }
    }
    map<string, node *> map_Moves;

    for (int j = 0; j < grids.size(); j++)
    {
        node *Node = new node();
        createNode(Node, grids[j]);
        // insertNode();
        map_Moves[MOVES[j]] = Node;
    }
    return map_Moves;
}
map<string, node *> valid(map<string, node *> Move)
{

    map<string, node *> valid;

    for (auto &j : Move)
    {

        if (j.first == "LEFT")
        {
            valid["LEFT"] = j.second;
        }
        else if (j.first == "RIGHT")
        {
            valid["RIGHT"] = j.second;
        }
        else if (j.first == "UP")
        {
            valid["UP"] = j.second;
        }
        else if (j.first == "DOWN")
        {
            valid["DOWN"] = j.second;
        }
    }

    return valid;
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

int getMin(vector<pair<string, int>> distances)
{

    vector<int> List;
    for (auto j : distances)
    {
        List.push_back(j.second);
    }

    return *min_element(List.begin(), List.end());
}
int getIndex(vector<int> List, int K)
{

    auto it = find(List.begin(), List.end(), K);

    if (it != List.end())
    {
        int index = it - List.begin();
        return index;
    }
    else
    {
        return -1;
    }
}

pair<int, node *> wrongSpot(node *currBoard, node *finBoard)
{

    int misMatch = 0;
    pair<int, node *> best;

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
    best.first = misMatch;
    best.second = currBoard;

    return best;
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


node* createTree(map<string, node *> Validated_Moves,node *start) {
    
    
    for (auto &grid : Validated_Moves) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if ((grid.second)->board[i][j] == '#') {
                    insertNode(start, grid.second, grid.first, grid.second->depth);
                }
            }
        }
    }
    return start;

}
node* insert(node* currentNode,node* copyNode,node* start){

         map<string, node *> T = generateMoves(currentNode->board, copyNode->board);
         return createTree(valid(T),start);

}

pair<string,node*> Astar(node* grid, pair<int, int> finalCo, node *end, node *start,int level) {
    int distance = 0;
    vector<pair<int, node *>> No_ofWrongSpots;
    vector<int> d;
    vector<string> Moves;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid->board[i][j] == '#') {
                    
                    Moves.push_back(grid->move);
                    distance = abs(i - finalCo.first) + abs(j - finalCo.second);
                    d.push_back(distance);
                    No_ofWrongSpots.push_back(wrongSpot(grid, end));
                }
            }
        }
    

    int count = 0;
    int Total = 0;
    vector<int> TotalCosts;
    if (!No_ofWrongSpots.empty()) {
        for (auto j : No_ofWrongSpots) {
            // calculate linear conflict here
            int linearConflict = calculateLinearConflict(j.second->board);
            Total = j.first + d[count] + linearConflict + level;
            
            TotalCosts.push_back(Total);
            count++;
        }
    }

   // cout<<"TotalCost: "<<Total<<endl;
    int min = *min_element(TotalCosts.begin(), TotalCosts.end());
    int index = getIndex(TotalCosts, min);
    pair<string,node*>best;
   
    best.second = No_ofWrongSpots[index].second;
    best.first = Moves[index];
    
    cout<<best.first<<endl;
    print(best.second->board);
    
    
    
    return best;
}

// use A* search instead;
//  Nodes were not inserted in the tree

/*void DFS(node *START_STATE, node *END_STATE)
{

    stack<node *> S;
    node *startNode = START_STATE;
    startNode->depth =0;
    S.push(startNode);
    node *currentNode = S.top();
    node *copyNode = currentNode;
    while (!S.empty())
    {

        node *currentNode = S.top();
        node *copyNode = currentNode;

        S.pop();

        if (currentNode->board == END_STATE->board)
        {
            cout<<"Success!"<<endl;
            cout<<"Depth: "<<currentNode->depth<<endl;
           
            cout<<"FROM: "<<endl;
            print(START_STATE->board);
            
            cout<<"TO: "<<currentNode->move<<endl;
            print(currentNode->board);
            return;
        }

        pair<string,node*> newBoard = safeBoard(valid(T), emptySpot(END_STATE->board), END_STATE, START_STATE,startNode->depth);
        insertNode(START_STATE, newBoard.second,newBoard.first ,newBoard.second->depth);
        S.push(newBoard.second);
    }

    return;
}*/


void level_order_traversal(node* root) {
    if (root == nullptr) {
        return;
    }

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* current = q.front();
        q.pop();

        cout <<"Depth: " << current->depth << endl;
        cout<<"Move: "<<current->move<< endl;
        print(current->board);

        if (current->LEFT != nullptr) {
            q.push(current->LEFT);
        }
        if (current->UP != nullptr) {
            q.push(current->UP);
        }
        if (current->RIGHT != nullptr) {
            q.push(current->RIGHT);
        }
        if (current->DOWN != nullptr) {
            q.push(current->DOWN);
        }
    }
}

int main()
{
    //string name = "#12345678";
    //string goal = "31245867#";
    //string name = "3#7281645";
    //string goal = "12345678#";

    //complex
    //string name = "1238#4765";
    //string goal = "281#43765";
    
    //string name = "12345678#";
    //string goal = "#23145786";
    
    //string name = "1234#5678";
    //string goal = "#13425678"; 
    
    //string name = "1234#5678";
    //string goal = "#23145678";
    
    //string name = "1234#5678";
    //string goal = "123645#78";
    //string goal = "12345867#";
    
    string name = "1234#5678";
    string goal = "12#643785";

    vector<vector<char>> grid;
    vector<vector<char>> goal_Grid;

    grid = form_Grid(name, grid);
    goal_Grid = form_Grid(goal, goal_Grid);

    node *end = new node();
    createNode(end, goal_Grid);

    node *root = new node();
    createNode(root, grid);
 
    root = insert(root,root,root);
   
   level_order_traversal(root);
    return 0;
}

