//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

// list of the sub functions that may be used in the main function
bool stringToInt(string x_location, int &value);
bool create(stringstream &restStream);
bool move(stringstream &restStream);
bool rotate(stringstream &restStream);
bool draw(stringstream &restStream);
bool deleteCommand(stringstream &restStream);

// the main function is as below
int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);
        command="";
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here


        //get the number of the array
        //create a shapesArray point to the shape[max_shapes]
        if (command == "maxShapes") {
            lineStream>>max_shapes;
            shapesArray = new shape*[max_shapes];
            for (int y=0; y < max_shapes; y++) {
                shapesArray[y] = NULL;
            }
            cout << "New database: max shapes is " << max_shapes << endl;
        } 
        else if (command == "create") {
            //call the create function
            create(lineStream);
        }
        else if (command == "move") {
            //call the move function
            move(lineStream);
        }
        else if (command == "rotate") {
            //call the rotate function
            rotate(lineStream);
        } 
        else if (command == "draw") {
            //call the draw function
            draw(lineStream);
        } 
        else if (command == "delete") {
            //call the delete function
            deleteCommand(lineStream);
        } 
        else {
            cout << "Error: invalid command" << endl;
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

//the function related to the create command 
bool create(stringstream &restStream){
    //check the invalid conditions
    //check if there is too few arguments
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for name
    string name;
    restStream >> name;
    for (int i=0; i<=6; i++){
        if (name == keyWordsList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    for (int j=0;j<=2; j++){
        if (name == shapeTypesList[j]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    for (int z=0; z<max_shapes; z++){
        if (shapesArray[z]!=NULL && name == shapesArray[z]-> getName()){
            cout<<"Error: shape name exists"<<endl;
            return false;
        }
    }
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for type                
    string type;
    restStream >> type;
    bool shapeTypeStatus=false;
    for (int j=0;j<=2; j++){
        if (type == shapeTypesList[j]){
            shapeTypeStatus=true;
        }   
    }
    if (shapeTypeStatus==false){
        cout<<"Error: invalid shape type"<<endl;
        return false;
    }
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for x_location
    string x_location;
    restStream >> x_location;
    //call the function that make a string into an integer
    int x_loc;
    if (stringToInt(x_location, x_loc)){
        if (x_loc<0){
            cout<<"Error: invalid value"<<endl;
            return false;
        }
    }
    else{
        return false;
    }
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for y_location
    string y_location;
    restStream >> y_location;
    int y_loc;
    if (stringToInt(y_location, y_loc)){
        if (y_loc<0){
            cout<<"Error: invalid value"<<endl;
            return false;
        }
    } 
    else{
        return false;
    }
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for x_size
    string x_size;
    restStream >> x_size;
    int x_sz;
    if (stringToInt(x_size, x_sz)){
        if (x_sz<0){
            cout<<"Error: invalid value"<<endl;
            return false;
        }
    }
    else{
        return false;
    }
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for y_size
    string y_size;
    restStream >> y_size;
    int y_sz;
    if (stringToInt(y_size, y_sz)){
        if (y_sz<0){
            cout<<"Error: invalid value"<<endl;
            return false;
        }
    }
    else{
        return false;
    }
    //check if there is too many arguments
    if (!restStream.eof()){
        cout<<"Error: too many arguments"<<endl;
        return false;
    }
    //check if the the shape array is full
    if (shapeCount>=max_shapes){
        cout<<"Error: shape array is full"<<endl;
        return false;
    }
    //if no error, set this input into the shapesArray
    shape* myshape=  new shape(name,type, x_loc, y_loc, x_sz, y_sz);
    shapesArray[shapeCount] = myshape;
    shapeCount+=1;
    cout<<"Created "<<name<<": "<<type<<" "<<x_loc
            <<" "<<y_loc<<" "<<x_sz<<" "<<y_sz<<endl;
    return true;
}

//the function changes the string in to an integer
bool stringToInt(string x_location, int &value){
    stringstream input;
    if (x_location == "") {
        // input string did not receive anything, 
        //we are likely missing arguments as expected
        cout<<"Error: too few arguments"<<endl;
        return false;   
    }
    input<<x_location;
    input>>value;
    char character;
    if (input.fail()==1){
        cout<<"Error: invalid argument"<<endl;
        return false;
    }
    else{
        character=input.peek();
        if (character != EOF && character != ' '){
            cout<<"Error: invalid argument"<<endl;
            return false;
        }
        else{
            //valid case
            return true;
        }
    }
}

//the function related to the move command
bool move(stringstream &restStream){
    //check the invalid conditions
    //check if there is too few arguments
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for name
    string name;
    restStream >> name;
    for (int i=0; i<=6; i++){
        if (name == keyWordsList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    for (int j=0;j<=2; j++){
        if (name == shapeTypesList[j]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    
    bool output=false;
    for (int p = 0; p<max_shapes; p++){
        if (shapesArray[p]!= NULL && shapesArray[p]->getName()== name){
            output=true;
            break;
        }
    }
    //failed case shape not found
    if (output==false){
        cout<<"Error: shape "<<name<<" not found"<<endl;
        return false;
    }

    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for x_location
    string x_location;
    restStream >> x_location;
    //call the function that make a string into an integer
    int x_loc;
    bool states;
    states = stringToInt(x_location, x_loc);
    if (states==true){
        if (x_loc<0){
            cout<<"Error: invalid value"<<endl;
            return false;
        }
    }
    else{
        return false;
    }
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for y_location
    string y_location;
    restStream >> y_location;
    int y_loc;
    states = stringToInt(y_location, y_loc);
    if (states==true){
        if (y_loc<0){
            cout<<"Error: invalid value"<<endl;
            return false;
        }
    }
    else{
        return false;
    }
    //check for too many arguments
    if (!restStream.eof()){
        cout<<"Error: too many arguments"<<endl;
        return false;
    }
    //if no error, change the position in the shapesArray
    for (int z = 0; z<max_shapes; z++){
        if(shapesArray[z]!=NULL && name == shapesArray[z]-> getName()){
            shapesArray[z]->setXlocation(x_loc);  
            shapesArray[z]->setYlocation(y_loc);
        }
    }
    cout<<"Moved "<<name<<" to "<<x_loc<<" "<<y_loc<<endl;
    return true;
}

//the function related to the rotate command
bool rotate(stringstream &restStream){
    //check the invalid conditions
    //check if there is too few arguments
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for name
    string name;
    restStream >> name;
    for (int i=0; i<=6; i++){
        if (name == keyWordsList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    for (int j=0;j<=2; j++){
        if (name == shapeTypesList[j]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    bool output=false;
    for (int p = 0; p<max_shapes; p++){
        if (shapesArray[p]!= NULL && shapesArray[p]->getName()== name){
            output=true;
            break;
        }
    }
    //failed case shape not found
    if (output==false){
        cout<<"Error: shape "<<name<<" not found"<<endl;
        return false;
    }
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //check the condition for angle
    string angle;
    restStream >> angle;
    int angle_value;
    bool states;
    states= stringToInt(angle, angle_value);
    if (states==true){
        if (angle_value<0 || angle_value >360){
            cout<<"Error: invalid value"<<endl;
            return false;
        }
    }
    else{
        return false;
    }
    //check if there is too many arguments
    if (!restStream.eof()){
        cout<<"Error: too many arguments"<<endl;
        return false;
    }
    //if no error, rotate in the shapesArray
    for (int z=0; z<max_shapes; z++){
        if(shapesArray[z]!=NULL && name == shapesArray[z]-> getName()){
            shapesArray[z]->setRotate(angle_value);  
        }
    }
    cout<<"Rotated "<<name<<" by "<<angle<<" degrees"<<endl;
    return true;
}

//the function related to the draw name and draw all command
bool draw(stringstream &restStream){
    //check the invalid conditions
    //check if there is too few arguments
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //to see the next argument is all or name
    string next_input;
    restStream>>next_input;
    if (next_input!="all"){
        int p=0;
        bool output=false;
        for (p; p<max_shapes; p++){
            if (shapesArray[p]!= NULL&&shapesArray[p]->getName()== next_input){
                output=true;
                break;
            }
        }
        //failed case 1 shape not found
        if (output==false){
            cout<<"Error: shape "<<next_input<<" not found"<<endl;
            return false;
        }
        //failed case 2 too many arguments
        else if(!restStream.eof()){
            cout<<"Error: too many arguments"<<endl;
            return false;
        }
        //if need to print the particular name
        else{
            if (!restStream.eof()) {
                cout<<"Error: too many arguments"<<endl;
                return false;
            }
            cout<<"Drew "<<next_input<<endl;
            cout<<shapesArray[p]->getName()<<": "
                    <<shapesArray[p]->getType()<<" "
                    <<shapesArray[p]->getXlocation()
                    <<" "<<shapesArray[p]->getYlocation()<<" "
                    <<shapesArray[p]->getXsize()
                    <<" "<<shapesArray[p]->getYsize()<<endl;
            return true;
        }
    }
    //print out all shapes in the array
    else {
        if (!restStream.eof()) {
            cout<<"Error: too many arguments"<<endl;
            return false;
        }
        else{
            cout<<"Drew all shapes"<<endl;
            for (int u = 0; u<max_shapes; u++){
                if (shapesArray[u]!=NULL){
                    cout<<shapesArray[u]->getName()
                            <<": "<<shapesArray[u]->getType()<<" "
                            <<shapesArray[u]->getXlocation()<<" "
                            <<shapesArray[u]->getYlocation()<<" "
                            <<shapesArray[u]->getXsize()<<" "
                            <<shapesArray[u]->getYsize()<<endl;
                }
            }
            return true;
        }
    }
}

//the function related to the delete name and delete all command
bool deleteCommand(stringstream &restStream){
    //check the invalid conditions
    //check if there is too few arguments
    if (restStream.eof()){
        cout<<"Error: too few arguments"<<endl;
        return false;
    }
    //to see the next argument is all or name
    string next_input;
    restStream>>next_input;
    if (next_input!="all"){
        int p=0;
        bool output=false;
        for (p; p<max_shapes; p++){
            if (shapesArray[p]!= NULL&&shapesArray[p]->getName()== next_input){
                output=true;
                break;
            }
        }
        //error case for shape name not found
        if (output==false){
            cout<<"Error: shape "<<next_input<<" not found"<<endl;
            return false;
        }
        //error case for too many arguments
        else if(!restStream.eof()){
            cout<<"Error: too many arguments"<<endl;
            return false;
        }
        //case for delete one particular shape
        else{
            cout<<"Deleted shape "<<next_input<<endl;
            delete shapesArray[p];
            shapesArray[p]=NULL;
        }
    }
    //case for delete all shapes
    else {
        if (!restStream.eof()) {
            cout<<"Error: too many arguments"<<endl;
            return false;
        }
        cout<<"Deleted: all shapes"<<endl;
        for (int t=0; t<max_shapes; t++){\
            delete shapesArray[t];
            shapesArray[t]=NULL;
        }
        shapeCount = 0;
    }
}