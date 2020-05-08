#include <iostream>
#include <string>
using namespace std;
#include "TreeDB.h"

// the default constructor, creates an empty database.
TreeDB::TreeDB() {
    root=nullptr;
    probesCount=0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    if (root==nullptr)
        //no need to clear if the root is already a nullptr
        return;
    else{
        //call the delete_tree helper funciton to delete all nodes in the tree to prevent memory leak
        delete_tree(root);
        //after deletion set the root to be nullptr to prevent delete it again
        root=nullptr;
    }
}

// inserts the entry pointed to by newEntry into the database.
bool TreeDB::insert(DBentry *newEntry) {
    //call the insert_tree helper function
    return insert_tree(root, newEntry);
}

// searches the database for an entry with a key equal to name.
DBentry* TreeDB::find(string name) {
    //set the probescount to be zero and call the helper function preorder_traversal
    probesCount=0;
    return preorder_traversal(root, name);
}

// deletes the entry with the specified name (key)  from the database.
bool TreeDB::remove(string name) {
    //call the remove_tree helper function
    return remove_tree(root, name);
}

// deletes all the entries in the database.
void TreeDB::clear() {
    if (root==nullptr)
        //no need to clear if the root is already a nullptr
        return;
    else{
        //call the delete_tree helper funciton to delete all nodes in the tree to prevent memory leak
        delete_tree(root);
        //after deletion set the root to be nullptr to prevent delete it again
        root=nullptr;
    }
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const {
    cout<<probesCount<<endl;
}

// computes and prints out the total number of active entries
void TreeDB::countActive() const {
    //call the count_active helper function
    int num;
    num = count_active(root);
    cout<<num<<endl;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs){
    // call the print helper function
    return rhs.print(out, rhs.root);
}

// the helper function to delete the whole tree
void TreeDB::delete_tree(TreeNode *root){
    if (root==nullptr)
        // if nothing in the node
        return;
    //trace right
    delete_tree(root->getRight());
    //trace left
    delete_tree(root->getLeft());
    //delete the particular node as base case
    delete root;
}

// the helper function for find the node
DBentry* TreeDB::preorder_traversal(TreeNode* root, string name){
    if(root==nullptr)
        //if nothing in the node
        return nullptr;
    //number increased as it passed through one node
    probesCount++;
    if (root->getEntry()->getName() == name)
        //return the entry that has been found
        return root->getEntry();
    else if (root->getEntry()->getName() > name)
        //trace left as the node's name is larger than target in alphabetical order
        return preorder_traversal(root->getLeft(),name);
    else if (root->getEntry()->getName() < name)
        //trace right as the node's name is smaller than target in alphabetical order
        return preorder_traversal(root->getRight(),name);
}

// the helper function to count the active entry in the tree
int TreeDB::count_active(TreeNode* root) const{
    int num=0;
    if (root==nullptr){
        // if no node in the tree
        return 0;
    }
    else{
        //if node is active then num++, if not num=num;
        if(root->getEntry()->getActive()==true)
            num++;
        //trace left
        num+=count_active(root->getLeft());
        //trace right
        num+=count_active(root->getRight());
    }
    return num;
}

// the helper function to help insert an newEntry to the tree
bool TreeDB::insert_tree(TreeNode* & root, DBentry* newEntry){
    if (root==nullptr){
        //if nothing in the tree, or it has been count down to the based case set it as the node
        root = new TreeNode(newEntry);
        return true;
    }
    TreeNode* nodeptr;
    //boolean value for return
    bool return_value;
    if(root->getEntry()->getName()==newEntry->getName())
        //if the entry is already exist
        return false;
    else if (root->getEntry()->getName()>newEntry->getName()){
        //if the entry's key is smaller than the root's, then trace to the left
        nodeptr=root->getLeft();
        return_value=insert_tree(nodeptr, newEntry);
        root->setLeft(nodeptr);
    }
    else{
        //if the entry's key is greater than the root's, then trace to the right
        nodeptr=root->getRight();
        return_value=insert_tree(nodeptr, newEntry);
        root->setRight(nodeptr);
    }
    return return_value;
}

// the helper function to delete the desired entry from the tree
bool TreeDB::remove_tree(TreeNode* & root, string name){
    // if nothing in the node
    if (root==nullptr)
        return false;
    // if the input node is the one that you need to remove
    else if (root->getEntry()->getName()==name){
        //if the removed node has no children, then it can be delete directly
        if (root->getRight()==nullptr && root->getLeft()==nullptr) {
            delete root;
            root = nullptr;
        }
        //if the removed node only has one child, replace the removed node to be that child
        else if (root->getLeft()==nullptr) {
            TreeNode *right_ptr;
            right_ptr=root;
            root=root->getRight();
            delete right_ptr;
        }
        //if the removed node only has one child, replace the removed node to be that child
        else if (root->getRight()==nullptr){
            TreeNode *left_ptr;
            left_ptr=root;
            root=root->getLeft();
            delete left_ptr;
        }
        //if the removed node has two children
        else{
            TreeNode* currentNode;
            TreeNode* currentLeft;
            TreeNode* currentRight;
            currentRight=root->getRight();
            currentLeft=root->getLeft();
            //if the right child has no children, then the right child is the target node for replacement
            if (currentLeft->getRight()==nullptr){
                currentNode=currentLeft;
                currentLeft=currentNode->getLeft();
            }
            else{
                //if the right child also has children, traced down to the most largest children on the right
                //call the helper function trace_down_right

                currentNode=trace_down_right(currentLeft);
            }
            //linked the target node to replace the position of the one that has been removed
            currentNode->setLeft(currentLeft);
            currentNode->setRight(currentRight);
            delete root;
            root=currentNode;
        }
        return true;
    }

    // if the input node is not the one that you need to remove
    bool return_value;
    if(name < root->getEntry()->getName()){
        // if the removed name is smaller that the node's name, trace to the left
        TreeNode* new_root;
        new_root=root->getLeft();
        return_value=remove_tree(new_root, name);
        root->setLeft(new_root);
    }
    else if(name > root->getEntry()->getName()){
        // if the removed name is larger that the node's name, trace to the right
        TreeNode* new_root;
        new_root=root->getRight();
        return_value=remove_tree(new_root, name);
        root->setRight(new_root);
    }
    return return_value;
}

// the helper function for remove_tree, finding the right most child from the left trace
TreeNode* TreeDB::trace_down_right(TreeNode* node){
    TreeNode* temp_right;
    temp_right=node->getRight();
    // it will traced to the right until the ->getRight is a null ptr, and linked out that desired node
    if (temp_right->getRight()==nullptr){
        node->setRight(temp_right->getLeft());
        temp_right->setLeft(nullptr);
        return temp_right;
    }
    return trace_down_right(temp_right);
}

// the helper function for operator<< for the tree
ostream& TreeDB::print(ostream& out, TreeNode* rhs) const{
    if (rhs == nullptr)
        // if nothing in the node, noting to add to the out
        return out;
    //trace the tree in order because the entry has to print out in order
    print(out, rhs->getLeft());
    out << *(rhs->getEntry());
    print(out, rhs->getRight());
    return out;
}

