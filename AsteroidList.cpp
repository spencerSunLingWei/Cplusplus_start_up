#include <galaxy-explorer/AsteroidList.hpp>
#include <iostream>
using namespace std;

AsteroidListItem::AsteroidListItem() {
    //default constructor for each item in the linked list
    this->next = nullptr;
    this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
    //the constructor that takes in each component of the input asteroid and
    //form a item for the list
    this->next = nullptr;
    this->data = new Asteroid(a.getID(),a.getMass(),a.getHealth(), a.getCurrentHitbox(),a.getVelocity());
}

AsteroidListItem::~AsteroidListItem() {
    //the destructor for the item, need to delete data as it is a dynamically
    //allocated array
    this->next = nullptr;
    delete this->data;
}

AsteroidList::AsteroidList(){
    //the default constructor for the list and set the headnext to be null
    //nothing in the list for this case
    this->head.setNext(nullptr);
}

AsteroidList::AsteroidList(const AsteroidList& src){
    //the copy constructor of the list
    //if there is nothing to copy
    if(src.isEmpty()){
        return;
    }
    //if there is a list to be copied is same as inserting it after the new head
    insertAfter(&head, src);   
}

AsteroidList::~AsteroidList() {
    // the destructor for the list, and need to free each item to prevent
    // memory leek
    AsteroidListItem* ptr = nullptr;//counter for traversing the list
    while (this->head.getNext()!= nullptr){
        ptr = this->head.getNext();
        this->head.setNext(ptr->getNext());
        delete ptr;
    }
}

void AsteroidList::pushFront(Asteroid e) {
    //add an asteroid at the beginning of the list
    AsteroidListItem* nptr = nullptr;
    nptr = new AsteroidListItem(e); //changing asteroid to be an list item
    if (this->head.getNext() == nullptr)// if nothing in the list
        this->head.setNext(nptr);
    else{ // if there is something in the list
        nptr->setNext(this->head.getNext());
        this->head.setNext(nptr);
    }
}

Asteroid& AsteroidList::front() {
    if (this->head.getNext()==nullptr) //return any behavior
        return *(Asteroid*)nullptr;
    else //return a reference to the first asteroid
        return this->head.getNext()->getData();
}

const Asteroid& AsteroidList::front() const {
    //const function of front
    if (this->head.getNext()==nullptr)
        return *(const Asteroid*)nullptr;
    else
        return this->head.getNext()->getData();
}

bool AsteroidList::isEmpty() const {
    //to check if the list is empty
    if(this->head.getNext()==nullptr)
        return true;
    //if the list is not empty
    else
        return false;
}

int AsteroidList::size() const {
    //to get the size of the list
    //temp pointer for traversing the list to get the incremented size value
    AsteroidListItem* tptr = (AsteroidListItem*)head.getNext();
    int size = 0;
    while (tptr != nullptr){
        size+=1;
        tptr = tptr->getNext();
    }
    return size;
}

AsteroidListItem* AsteroidList::beforeBegin() {
    //if the list is empty, return nullptr
    if (this->head.getNext() == nullptr)
        return nullptr;
    //if the list has something return the head item
    else
        return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
    //const function for the before begin
    if (this->head.getNext() == nullptr)
        return nullptr;
    else
        return &head;
}

AsteroidListItem* AsteroidList::begin() {
    //if the list is empty, return nullptr
    if (this->head.getNext() == nullptr)
        return nullptr;
    //if the list has something then return the first asteroid time
    else
        return this->head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
    //the const function for begin 
    if (this->head.getNext() == nullptr)
        return nullptr;
    else
        return this->head.getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem *tptr = this->head.getNext();
    //if there is nothing in the list return nullptr
    if (tptr == nullptr){
        return nullptr;
    }
    else{
        //traversing the list
        while (tptr->getNext() != nullptr){
            tptr = tptr->getNext();  
        }
        //return the last asteroid item
        return tptr;
    }
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    // the const function of before end
    const AsteroidListItem *tptr = this->head.getNext();
    if (tptr == nullptr){
        return nullptr;
    }
    else{
        while (tptr->getNext() != nullptr){
            tptr = tptr->getNext();  
        }
        return tptr;
    }
}

AsteroidListItem* AsteroidList::end() {
    //return nullptr because the next of last asteroid always point to null
    return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
    //const function of end
    return nullptr;
}
        
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e){
    AsteroidListItem* nptr=nullptr;
    nptr = new AsteroidListItem(e); // make the asteroid to be a list item
    AsteroidListItem* prevNext = nullptr;
    prevNext=prev->getNext(); // get the rest of the list after prev node
    prev->setNext(nptr); // insert the new node in the list
    nptr->setNext(prevNext); // connect the rest of the list
    return prev->getNext(); // return the new item that has been inserted
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
     AsteroidListItem* output = nullptr;
    //record all nodes after the prev nodes
    AsteroidListItem* prevNext = prev->getNext();
    //create new node for each item and copy the thing in other list 
    //the tptr for traversing the asteroid list after
    AsteroidListItem* tptr = (AsteroidListItem*)others.begin();
    //if nothing inside return the insertion node
    if (tptr==nullptr)
        return prev;
    while (tptr != nullptr) {
        //record the last item that was inserted to be the output
        if (tptr->getNext()==nullptr){
            output = tptr;
        }
        AsteroidListItem* newNode = new AsteroidListItem(tptr->getData());
        newNode->setNext(tptr->getNext());//create and copy for a new item
        prev->setNext(newNode); //add it to the existing list
        tptr = tptr->getNext(); //next node in other
        prev = prev->getNext(); //update the position allowance for next inserting
    }
    // link together
    prev->setNext(prevNext);
    return output;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    bool isFound= false;
    //the temp pointer for traversing the list
    AsteroidListItem* tptr = head.getNext();
    // record the list after prev node
    AsteroidListItem* prevNext = prev->getNext();
    //do the traversing of the list to see if prev node is exist or not
    while (tptr != nullptr ){
        if (tptr==prev){
            isFound = true;
            break;
        }
        tptr=tptr->getNext();
    }
    // if not found, return end
    if (isFound == false)
        return end();
    // if found then erase everything after the node
    else{
        prev->setNext(prev->getNext()->getNext());
        delete prevNext;
    }
}

void AsteroidList::clear() {
    //clear all the item in the node, do the traversing to delete all ptr
    //to prevent memory leek
    AsteroidListItem* ptr=nullptr;
    while (this->head.getNext()!= nullptr){
        ptr = this->head.getNext();
        this->head.setNext(ptr->getNext());
        delete ptr;
    }
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    //if is the same
    if (this==&src)
        return (*this);
    //call the destructor which is the same as clear function
    clear();
    //do the copy constructor which is the same as insert after
    insertAfter(&head, src);
    return (*this);
}