#include<bits/stdc++.h>

using namespace std;

void print(vector<vector<char>>grid){

    for(vector<char> j: grid){
        for(char i:j){
            cout<<i<<"";
        }
        cout<<endl;
    }

}

int main(){

    int N =3;
    string name = "12345#678";
    vector<vector<char>>grid;
    int count =0;
    for(int j =0;j<N;j++){
        vector<char>rows;
        for(int i =0;i<N;i++){
            rows.push_back(name[count]);
            count++;
        }
        grid.push_back(rows);
    }
    
    vector<vector<char>>copyOfgrid = grid;
    vector< vector<vector<char>> > grids;
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
                    
                    grid = copyOfgrid;
                }
                 if(grid[j+1][i] != 0){
                    int currtemp = grid[j+1][i];
                    int temp = grid[j][i];
                    grid[j+1][i] = temp;
                    grid[j][i] = currtemp;
                    
                    if(isdigit(grid[j][i]))
                        grids.push_back(grid);
                
                    grid = copyOfgrid;
                }
             
                 if(grid[j][i-1] != 0){
                    int currtemp = grid[j][i-1];
                    int temp = grid[j][i];
                    grid[j][i-1] = temp;
                    grid[j][i] = currtemp;
                    
                    if(isdigit(grid[j][i]))
                        grids.push_back(grid);
                
                    grid = copyOfgrid;
                }
            
                if(grid[j][i+1] != 0){
                    int currtemp = grid[j][i+1];
                    int temp = grid[j][i];
                    grid[j][i+1] = temp;
                    grid[j][i] = currtemp;
                    
                    if(isdigit(grid[j][i]))
                        grids.push_back(grid);
                
                    grid = copyOfgrid;
          
                }
            }
        }
}

for(vector<vector<char>>j:grids){
    print(j);
    cout<<""<<endl;
}
return 0;}
