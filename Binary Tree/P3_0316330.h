// environment: Dev C++
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;

class TreeNode{ // The node for the tree.
    friend class BT;

public:
    int data; // data of the node.
    TreeNode *left, *right, *parent; // pointer to left child, right child and the parent of the node.

    TreeNode(){ //constructor of the node.
        data = -1;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

};

class BT{

public:
    TreeNode *root; // root node of the tree.

    BT(){
        root = NULL;
    }

    BT(const char *a){

        char* nodeData; // used to store the information of the string strtok from the input string.
        char *b = strdup(a); // copy the original string to b.
        nodeData = strtok(b," ");
        int size; // to determine the size of myData;
        int height; // the height of th tree.
        int counter = 0; // the counter for myData.
        height = atoi(nodeData);
        size = 1<<height;
        int myData[size];
        for(int i=0;i<size;i++){ // initialize myData.
            myData[i] = -1;
        }
        nodeData = strtok(NULL," ");
        while(nodeData != NULL){ // store the information from b to myData.
            int number;
            number = atoi(nodeData);
            myData[counter++] = number;
            nodeData = strtok(NULL," ");
        }
        root = new TreeNode;
        constructTreeDriver(height,root,myData,0); // use height, root node, myData to construct a tree.
    }

    void constructTreeDriver(int height, TreeNode* currentNode,int data[],int position){ // driver of constructing a tree.
        if(currentNode == root){
            root->parent = NULL;
            root->data = data[position]; // determine the data of the node by its level-order position.
            root->left = constructTree(height-1,root,data,position+1); // continue constructing the subtree.
            root->right = constructTree(height-1,root,data,position+2);
        }
        return;
    }

    TreeNode* constructTree(int height,TreeNode *myParent, int* data, int position){ // workhorse of constructing a tree.
        TreeNode *re = new TreeNode;
        if(height == 0){
            return NULL; // no node while height is zero.
        }
        re ->data = data[position];
        re ->parent = myParent;
        re->left = constructTree(height-1,re,data,position*2+1);
        re->right = constructTree(height-1,re,data,position*2+2);
        return re;
    }

    void inorder() // inorder traversal. We can analyse the source of the current node to decide which way to travel next.

    {
        TreeNode *currentNode = root; // start from root node.
        TreeNode *lastNode = NULL; // last node is used to store the source of current node.
        while( !(currentNode ==root && lastNode==currentNode->right)){


            if (currentNode->left && lastNode == currentNode->parent) {
                lastNode = currentNode;
                currentNode = currentNode->left;
            }
            else if(currentNode -> right && lastNode == currentNode->parent){

                lastNode = currentNode;
                currentNode = currentNode->right;
            }
            else if(lastNode == currentNode->parent){ // output the data while lastNode is the parentNode of currentNode and currentNode has no child.
                if(currentNode->data != -1) cout<<currentNode->data<<" ";
                lastNode = currentNode;
                currentNode = currentNode->parent;
            }
            else if(lastNode == currentNode -> left && currentNode -> right){ // output the data while lastNode is the left child of currentNode and the right child of currentNode exists.

                if(currentNode->data != -1) cout<<currentNode->data<<" ";
                lastNode = currentNode;
                currentNode = currentNode->right;

            }
            else if(lastNode == currentNode -> left){

                lastNode = currentNode;
                currentNode = currentNode -> parent;
            }
            else{
                lastNode = currentNode;
                currentNode = currentNode->parent;
            }

        }


    }


    void preorder(){ // preorder traversal. We can analyse the source of the current node to decide which way to travel next.

        TreeNode *currentNode = root; // start from root node.
        TreeNode *lastNode = NULL; // last node is used to store the source of current node.
        while( !(currentNode ==root && lastNode==currentNode->right)){


            if (currentNode->left && lastNode == currentNode->parent) { //output the data while lastNode is the parent of currentNode and currentNode is traveling left.
                if(currentNode->data != -1) cout<<currentNode->data<<" ";
                lastNode = currentNode;
                currentNode = currentNode->left;
            }
            else if(currentNode -> right && lastNode == currentNode->parent){

                lastNode = currentNode;
                currentNode = currentNode->right;
            }
            else if(lastNode == currentNode->parent){ // output the data while lastNode is the parentNode of currentNode and currentNode has no child.
                if(currentNode->data != -1) cout<<currentNode->data<<" ";
                lastNode = currentNode;
                currentNode = currentNode->parent;
            }
            else if(lastNode == currentNode -> left && currentNode -> right){

                lastNode = currentNode;
                currentNode = currentNode->right;

            }
            else if(lastNode == currentNode -> left){

                lastNode = currentNode;
                currentNode = currentNode -> parent;
            }
            else{
                lastNode = currentNode;
                currentNode = currentNode->parent;
            }

        }


    }

    void postorder(){ // postorder traversal. We can analyse the source of the current node to decide which way to travel next.

        TreeNode *currentNode = root; // start from root node.
        TreeNode *lastNode = NULL; // last node is used to store the source of current node.
        while( !(currentNode ==root && lastNode==currentNode->right)){


            if (currentNode->left && lastNode == currentNode->parent) {
                lastNode = currentNode;
                currentNode = currentNode->left;
            }
            else if(currentNode -> right && lastNode == currentNode->parent){

                lastNode = currentNode;
                currentNode = currentNode->right;
            }
            else if(lastNode == currentNode->parent){  // output the data while lastNode is the parentNode of currentNode and currentNode has no child.
                if(currentNode->data != -1) cout<<currentNode->data<<" ";
                lastNode = currentNode;
                currentNode = currentNode->parent;
            }
            else if(lastNode == currentNode -> left && currentNode -> right){

                lastNode = currentNode;
                currentNode = currentNode->right;

            }
            else if(lastNode == currentNode -> left){
                lastNode = currentNode;
                currentNode = currentNode -> parent;
            }
            else { // output the data while the source is coming from the right child of currentNode.
                if(currentNode->data != -1) cout<<currentNode->data<<" ";
                lastNode = currentNode;
                currentNode = currentNode->parent;
            }

        }
        cout<<root->data;

    }

};

