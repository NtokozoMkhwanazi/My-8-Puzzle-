#include<bits/stdc++.h>

using namespace std;

class node{

    public:
        vector<vector<char>>board;
        node* LEFT;
        node* RIGHT;
        node* UP;
        node* DOWN;
        int depth;
};

void print(vector<vector<char>>grid){
    
    cout<<"--------"<<endl;;
    if(!grid.empty()){
        for(vector<char> j: grid){
            cout<<"|";
            for(char i:j){
                cout<<i<<" ";
            }
            cout<<"|";
            cout<<endl;
        }
    }
    cout<<"--------"<<endl;
}
void createNode(node* Node,vector<vector<char>> grid){

    Node->board = grid;
    Node->LEFT = nullptr;
    Node->RIGHT = nullptr;
    Node->UP = nullptr;
    Node->DOWN = nullptr;
}

void insertNode(node* root,node* Node,string Move){
    
    if(root == NULL){
        return;
     }
    
        if(Move == "UP"){
            if(root->UP != nullptr){
                root = root->UP;
            }else if(root->UP == nullptr){
                root->UP = Node; 
            }
        }
        if(Move == "DOWN"){
            if(root->DOWN != nullptr){
                root = root->DOWN;
            }else if(root->DOWN == nullptr){
                root->DOWN = Node; 
            }
        }
        
        if(Move == "LEFT"){
            if(root->LEFT != nullptr){
                root = root->LEFT;
            }else if(root->LEFT == nullptr){
                root->LEFT = Node; 
            }
        }
            
        if(Move == "RIGHT"){
            if(root->RIGHT != nullptr){
                root = root->RIGHT;
            }else if(root->RIGHT == nullptr){
                root->RIGHT = Node; 
            }
        }
        
}

vector<vector<char>> form_Grid(string puzzle,vector<vector<char>> grid){
    
    int N =3;
    int count =0;
    for(int j =0;j<N;j++){
        vector<char>rows;
        for(int i =0;i<N;i++){
            rows.push_back(puzzle[count]); 
            count++;
        }
        grid.push_back(rows);
    }
    return grid;
}

map<string,node*> generateMoves(vector<vector<char>>grid,vector<vector<char>>copyOfgrid){
    
    vector< vector<vector<char>> >grids;
    vector<string>MOVES;
    
    for(int j=0;j<grid.size();j++){
        for(int i=0;i<grid.size();i++){
            if(grid[j][i] == '#'){
                
                if(grid[j-1][i] != 0){
                    int currtemp = grid[j-1][i];
                    int temp = grid[j][i];
                    grid[j-1][i] = temp;
                    grid[j][i] = currtemp;
                    
                    if(isdigit(grid[j][i]))
                        grids.push_back(grid);
                        MOVES.push_back("UP");
                        
                    grid = copyOfgrid;
                }
                 if(grid[j+1][i] != 0){
                    int currtemp = grid[j+1][i];
                    int temp = grid[j][i];
                    grid[j+1][i] = temp;
                    grid[j][i] = currtemp;
                    
                    if(isdigit(grid[j][i]))
                        grids.push_back(grid);
                        MOVES.push_back("DOWN");
                        
                    grid = copyOfgrid;
                }
             
                 if(grid[j][i-1] != 0){
                    int currtemp = grid[j][i-1];
                    int temp = grid[j][i];
                    grid[j][i-1] = temp;
                    grid[j][i] = currtemp;
                    
                    if(isdigit(grid[j][i]))
                        grids.push_back(grid);
                        MOVES.push_back("LEFT");
                
                    grid = copyOfgrid;
                }
            
                if(grid[j][i+1] != 0){
                    int currtemp = grid[j][i+1];
                    int temp = grid[j][i];
                    grid[j][i+1] = temp;
                    grid[j][i] = currtemp;
                    
                    if(isdigit(grid[j][i]))
                        grids.push_back(grid);
                        MOVES.push_back("RIGHT");
                    grid = copyOfgrid;
          
                }
            }
        }
    }
    map<string,node*>map_Moves;
    
    for(int j=0;j<grids.size();j++){  
        node* Node = new node();
        createNode(Node,grids[j]);
        map_Moves[MOVES[j]] = Node;
    }
    return map_Moves;        
}
map<string,node*> valid(map<string,node*>Move){
    
    map<string,node*>valid; 
    
    for(auto &j : Move){
    
        if(j.first == "LEFT"){
            valid["LEFT"] = j.second;
        }
        else if(j.first ==  "RIGHT"){
            valid["RIGHT"] =  j.second;
        }
        else if(j.first == "UP"){
            valid["UP"] = j.second;
        }
        else if(j.first == "DOWN"){
            valid["DOWN"] = j.second;
        }
    }  
  
    return valid;
}
bool verify(node* curr_Node,node* end){
    
    if(curr_Node->board == end->board){
        return true;
    }
        return false;
}

pair<int,int> emptySpot(vector<vector<char>>grid){
    pair<int,int>Co;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid.size();j++){
            
            if(grid[i][j] == '#'){
                 Co.first = i;
                 Co.second = j;      
            }       
         
        }
    }
    return Co;
}

 
pair<int,int> manhattanDistance(map<string,node*>Validated_Moves,pair<int,int>finalCo) {
    int distance = 0;
    pair<int,int>Co;
    for(auto &grid : Validated_Moves){
       
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
       
                   if((grid.second)->board[i][j] == '#'){
                        distance = abs(i - finalCo.first) + abs(j - finalCo.second);
                        if(distance <= 1){
                            Co.first = i;
                            Co.second = j;
                        }
                    }
            
            }
        }
    }
    return Co;
    
}
void DFS(node* START_STATE,node* END_STATE){
    
    stack<node*>S;
    node* startNode = START_STATE;
    S.push(startNode);
    
    while(!S.empty()){
        node* currentNode = S.top();
        node* copyNode = currentNode;
       
        S.pop();
        
        if(verify(currentNode,END_STATE)){
            cout<<"solution"<<endl;
            return;
        }
        
        map<string,node*>T = generateMoves(currentNode->board,copyNode->board);
        pair<int,int>optimalCo = manhattanDistance( valid(T),emptySpot(END_STATE->board));
        
        for(auto &i : valid(T)){
            
            if((i.second)->board[optimalCo.first][optimalCo.second] == '#'){
                node* newNode = i.second;
                print(newNode->board);
                S.push(newNode);
            }
        }
        
    }
   
   cout<<"no Solution"<<endl;
   return;
}

int main(){
     
    string name = "1234#5678";
    string goal = "#23145678";
 
    vector<vector<char>>grid;
    vector<vector<char>>goal_Grid;
    
    grid = form_Grid(name,grid); 
    goal_Grid = form_Grid(goal,goal_Grid);
   
    node* end = new node();
    createNode(end,goal_Grid);
    
    node* root = new node();
    createNode(root,grid);
    cout<<"END STATE: ";
    cout<<endl;
    print(end->board);
    cout<<"SOLUTION STATE:";
    cout<<endl;
    DFS(root,end);
    
   
return 0;}
