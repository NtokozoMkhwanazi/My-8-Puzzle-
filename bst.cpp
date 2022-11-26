#include<bits/stdc++.h>

using namespace std;

class Node{

    public:
        int data;
        Node* left;
        Node* right;    

};


void createNode(Node* node,int value){

    node->data = value;
    node->left = nullptr;
    node->right = nullptr;

}
void insertNode(Node* root,queue<Node*>nodes){
    
    if(root == NULL){
        return;
    }
    
    while(!nodes.empty()){
    
        if(root->left == nullptr){
            root->left = nodes.front();
            nodes.pop();
        }
        else{
            root = root->left;
        }
        
        if(root->right == nullptr){
            root->right = nodes.front();
            nodes.pop();
            
        }else{
            root = root->right;
        }
    }
    
}

void printInorder(Node* node)
{
    if (node == NULL)
        return;
 
    printInorder(node->left);
 
    cout << node->data << " ";
 
    printInorder(node->right);
}
void printPreorder(Node* node)
{
    if (node == NULL)
        return;
 
    cout << node->data << " ";

    printPreorder(node->left);
    
    printPreorder(node->right);
}

void printPostorder(Node* node)
{
    if (node == NULL)
        return;
 
    printPostorder(node->left);
 
    printPostorder(node->right);
 
    cout << node->data << " ";
}

int main(){

    Node* root = new Node();
    Node* node1 = new Node();
    Node* node2 = new Node();
    Node* node3 = new Node();
    Node* node4 = new Node();
    Node* node5 = new Node();
    Node* node6 = new Node();
 
    createNode(root,10);
    createNode(node1,11);
    createNode(node2,12);
    createNode(node3,13);
    createNode(node4,14);
    createNode(node5,15);
    createNode(node6,16);
   
   queue<Node*>nodes;
   
   nodes.push(node1);
   nodes.push(node2);
   nodes.push(node3);
   nodes.push(node4); 
   nodes.push(node5);
   nodes.push(node6);
     
   insertNode(root,nodes);
   
   printInorder(root);
   cout<<endl;
   printPreorder(root);
   cout<<endl;
   printPostorder(root);
   cout<<endl;
       
return 0;
}

