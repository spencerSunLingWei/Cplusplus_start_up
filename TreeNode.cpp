#include <iostream>
#include <string>
using namespace std;
#include "TreeNode.h"

//the constructor that takes in an DBentry pointer to the entry that we want to insert to this node
TreeNode ::TreeNode(DBentry *_entryPtr) {
    entryPtr = _entryPtr;
    left = nullptr;
    right = nullptr;
}

//the destructor
TreeNode ::~TreeNode(){
    //delete the DBentry pointer, to prevent memory leak
    delete entryPtr;
    //set the entryPtr member to be nullptr, to prevent delete it again
    entryPtr=nullptr;
}

//the setLeft function let user to get access and change the private member
void TreeNode ::setLeft(TreeNode *newLeft) {
    left = newLeft;
}

//the setRight function let user to get access and change the private member
void TreeNode ::setRight(TreeNode *newRight) {
    right = newRight;
}

//the getLeft function let user to get access to the private member
TreeNode* TreeNode ::getLeft() const {
    return (left);
}

//the getRight function let user to get access to the private member
TreeNode* TreeNode ::getRight() const {
    return (right);
}

//the getEntry function let user to get access to the private member
DBentry* TreeNode ::getEntry() const {
    return (entryPtr);
}