#include <bits/stdc++.h>

using namespace std;

class node
{

public:
	
    vector<vector<char>> board;
    vector<node*>neighbors;
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
            insertNode(root->UP, Node, Move, depth + 1,cost);
        } else {
            root->UP = Node;
            root->UP->depth = depth + 1;
            root->UP->move = Move;
            root->UP->costMove = cost;
        }
    } else if (Move == "DOWN") {
        if (root->DOWN != nullptr) {
            insertNode(root->DOWN, Node, Move, depth + 1,cost);
        } else {
            root->DOWN = Node;
            root->DOWN->depth = depth + 1;
            root->DOWN->move = Move;
            root->DOWN->costMove = cost;
        }
    } else if (Move == "LEFT") {
        if (root->LEFT != nullptr) {
            insertNode(root->LEFT, Node, Move, depth + 1,cost);
        } else {
            root->LEFT = Node;
            root->LEFT->depth = depth + 1;
            root->LEFT->move = Move;
            root->LEFT->costMove = cost;
        }
    } else if (Move == "RIGHT") {
        if (root->RIGHT != nullptr) {
            insertNode(root->RIGHT, Node, Move, depth + 1,cost);
        } else {
            root->RIGHT = Node;
            root->RIGHT->depth = depth + 1;
            root->RIGHT->move = Move;
            root->RIGHT->costMove = cost;
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

vector<node *> generateMoves(vector<vector<char>> grid, vector<vector<char>> copyOfgrid)
{

    vector<vector<vector<char>>> grids;
    vector<string> MOVES;
	vector<node*>nodes;
	
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

                    if (isdigit(grid[j][i])){
                        grids.push_back(grid);
                    	MOVES.push_back("UP");
					}
                    grid = copyOfgrid;
                }
                if (j < grid.size() - 1 && grid[j + 1][i] != 0)
                {
                    int currtemp = grid[j + 1][i];
                    int temp = grid[j][i];
                    grid[j + 1][i] = temp;
                    grid[j][i] = currtemp;

                    if (isdigit(grid[j][i])){
                        grids.push_back(grid);
                    	MOVES.push_back("DOWN");
					}
                    grid = copyOfgrid;
                }

                if (i > 0 && grid[j][i - 1] != 0)
                {
                    int currtemp = grid[j][i - 1];
                    int temp = grid[j][i];
                    grid[j][i - 1] = temp;
                    grid[j][i] = currtemp;

                    if (isdigit(grid[j][i])){
                        grids.push_back(grid);
                   		MOVES.push_back("LEFT");
					}
                    grid = copyOfgrid;
                }

                if (i < grid.size() - 1 && grid[j][i + 1] != 0)
                {
                    int currtemp = grid[j][i + 1];
                    int temp = grid[j][i];
                    grid[j][i + 1] = temp;
                    grid[j][i] = currtemp;

                    if (isdigit(grid[j][i])){
                        grids.push_back(grid);
                    	MOVES.push_back("RIGHT");
                    }
                    grid = copyOfgrid;
                }
            }
        }
    }
    
    for (int j = 0; j < grids.size(); j++)
    {
        node *Node = new node();
        createNode(Node,grids[j]);
        Node->move = MOVES[j];
        nodes.push_back(Node);
        
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

         vector<node *> T = generateMoves(currentNode->board, copyNode->board);
		 
         return createTree(T,start);

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

void dia_star(node *startBoard, node *endBoard)
{
    vector<node *> openList; 
    vector<node *> closedList; 
    
    node *currentNode = startBoard;
    node *copyNode =  startBoard;
    currentNode->g = 0; 
    currentNode->h = Manhattan_Start_distance(currentNode, startBoard); 
    currentNode->f = currentNode->g + currentNode->h;
    openList.push_back(currentNode);
    
    while (!openList.empty())
    {
        sort(openList.begin(), openList.end(), [](node *a, node *b) { return a->f < b->f; });
        currentNode = openList.front();
        if (currentNode == endBoard)
        {
            return;
        }
        openList.erase(openList.begin());
        closedList.push_back(currentNode);
        vector<node *> neighbors = generateMoves(currentNode->board, copyNode->board);
        currentNode->g = startTocurrent(currentNode, startBoard);
        
        for (int i = 0; i < neighbors.size(); i++)
        {
            node *neighbor = neighbors[i];
           
            if (find(closedList.begin(), closedList.end(), neighbor) != closedList.end())
            {
                continue;
            }
            
            neighbor->costMove = startTocurrent(neighbor, startBoard); //+ calculateLinearConflict(neighbor->board);
            int tentativeGScore = currentNode->g + neighbor->costMove;
            
            bool tentativeIsBetter = false; 
            if (find(openList.begin(), openList.end(), neighbor) == openList.end())
            {
                openList.push_back(neighbor); 
                tentativeIsBetter = true;
            }
            else if (tentativeGScore < neighbor->g)
            {
                tentativeIsBetter = true;
            }
            
            if (tentativeIsBetter)
            {
                neighbor->g = tentativeGScore;
                neighbor->h = Manhattan_Start_distance(neighbor, endBoard);
                neighbor->f = neighbor->g + neighbor->h;
            }
        }
    }
}


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
    
    string name = "12345678#";
    string goal = "#23145786";
    
    //string name = "1234#5678";
    //string goal = "#13425678"; 
    
    //string name = "1234#5678";
    //string goal = "#23145678";
    
    //string name = "1234#5678";
    //string goal = "123645#78";
    //string goal = "12345867#";
    
    //string name = "1234#5678";
    //string goal = "12#643785";

    vector<vector<char>> grid;
    vector<vector<char>> goal_Grid;

    grid = form_Grid(name, grid);
    goal_Grid = form_Grid(goal, goal_Grid);

    node *end = new node();
    createNode(end, goal_Grid);
    cout<<"end Board"<<endl;
    print(end->board);
    
    node *root = new node();
    createNode(root, grid);
    cout<<"start Board"<<endl;
    print(root->board);
    
    root->costMove = 0;
    root = insert(root,root,root);
    dia_star(root,end);

    return 0;
}
