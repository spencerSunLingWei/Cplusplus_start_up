#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

//the function main to implement the user input
int main(){
    //take all user input as a string
    string line;
    cout << ">";
    getline(cin,line);

    //dynamically allocated an a tree for the user input
    TreeDB* tree = new TreeDB();

    //do implementation when the line has been take in successfully
    while (!cin.eof()){
        //using string stream for extracting each command and content from the user input line
       stringstream linestream(line);
       string command;
       linestream >> command;

       //if the command is insert, then insert the content in the tree
       if (command=="insert"){
           // take in all the user input to the right place
           string name;
           unsigned int IPaddress;
           string status;
           linestream >> name;
           linestream >> IPaddress;
           linestream >> status;

           //create a new entry based on the user input
           DBentry* entry = new DBentry(name, IPaddress, status=="active");

           //call the insert function from TreeDB, insert the entry to the tree
           if(tree->insert(entry)){
               //if it inserted successfully
               cout<<"Success"<<endl;
           }
           else{
               //if there is already have this entry, then delete the entry that has been created
               delete entry;
               cout<<"Error: entry already exists"<<endl;
           }
       }

       // if the command is find, then find the co-responding content in the tree
       else if (command=="find"){
           // take in all the user input to the right place
           string name;
           linestream >> name;

           //call the find function from TreeDB
           DBentry* entry = tree->find(name);

           if(entry==nullptr)
               //if the entry is a nullptr, then the entry does not exist
               cout<<"Error: entry does not exist"<<endl;
           else
               //print out the content that the DBentry point to to the user
               cout<<*entry;
       }

       //if the command is remove, then find the content in the tree and delete it from the tree
       else if (command=="remove"){
           // take in all the user input to the right place
           string name;
           linestream>>name;

           //call the remove funtion from the TreeDB
           if(tree->remove(name)==false){
               //if the entry is not found
               cout<<"Error: entry does not exist"<<endl;
           }
           else{
               //if been removed successfully
               cout<<"Success"<<endl;
           }
       }

       //if the command is printall, then print all the content in the tree in order
       else if (command=="printall"){
           //use the pre-declared operatior<< to print out all the content in the tree in order
           cout<<*tree;
       }

       //if the command is printprobes, then find the co-responding content and print out the number of probes it passed
       else if (command=="printprobes"){
           // take in all the user input to the right place
           string name;
           linestream>>name;

           //call the find function from the TreeDB
           DBentry* entry = tree->find(name);

           if(entry==nullptr)
               //if the entry is not found
               cout<<"Error: entry does not exist"<<endl;
           else{
               //if the entry has been found, then print out how many probes has been passed
               tree->printProbes();
           }
       }

       //if the command is removeall, then remove all the node and content inside each node of the tree
       else if (command=="removeall"){
           //call the clear function from the TreeDB, to delete all node from the tree
           tree->clear();
           cout<<"Success"<<endl;
       }

       //if the command is countactive, then count through all the node to see if the status is active or not
       else if (command=="countactive"){
           //call the countActive function from the TreeDB, to count how many active entry in the tree
           tree->countActive();
       }

       //if the command is updatestatus, then find the node and update the status
       else if (command=="updatestatus"){
           // take in all the user input to the right place
           string name;
           linestream>>name;
           string status;
           linestream >> status;

           //call the find function from the TreeDB
           DBentry* entry = tree->find(name);

           if(entry==nullptr)
               //if the entry has not been found
               cout<<"Error: entry does not exist"<<endl;
           else{
               //if the entry has been found, then update the state by setActive function
               entry->setActive(status=="active");
               cout<<"Success"<<endl;
           }
       }

       //command for next user input
       cout << ">";
       getline(cin,line);
   }

    //delete the dynamic allocated tree to prevent memory leak
    delete tree;
    return (0);
}