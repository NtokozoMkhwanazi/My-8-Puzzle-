#include<bits/stdc++.h>
using namespace std;


void printBoard(vector<vector<char>>board){

    for(vector<char> j : board){
        for(char i : j){
            cout<<i<<" ";
        }
        cout<<endl;
    }

}

int main(){

vector<vector<char>>board;
int N = 3;
string Solve = "12345#678";
int count =0;
for(int j =0;j<N;j++){
    vector<char>rows;
    for(int i =0;i<N;i++){
        rows.push_back(Solve[count]);
        count++;
    }
    board.push_back(rows);
}

printBoard(board);

return 0;}
