#include <iostream>
#include <string>
using namespace std;
#include "DBentry.h"

//the defaut constructor
DBentry :: DBentry(){
    //do nothing
}

//the constructor which takes in all three members from input
DBentry ::DBentry(string _name, unsigned int _IPaddress, bool _active) {
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

//the destructor
DBentry :: ~DBentry() {
    //do nothing
}

//the setName function let user to get access and change the private member
void DBentry ::setName(string _name) {
    name = _name;
}

//the setIPaddress function let user to get access and change the private member
void DBentry ::setIPaddress(unsigned int _IPaddress) {
    IPaddress = _IPaddress;
}

//the setActive function let user to get access and change the private member
void DBentry ::setActive(bool _active) {
    active = _active;
}

//the getName function let user to get access to the private member
string DBentry ::getName() const {
    return name;
}

//the getIPaddress function let user to get access to the private member
unsigned int DBentry ::getIPaddress() const {
    return IPaddress;
}

//the getActive function let user to get access to the private member
bool DBentry ::getActive() const {
    return active;
}

// the overloading operator<< let it directly print out the content in style that we want
ostream& operator<<(ostream& out, const DBentry& rhs) {
    if (rhs.active==true)
        out << rhs.name << " : " << rhs.IPaddress<< " : " << "active" <<endl;
    else if (rhs.active==false)
        out << rhs.name << " : " << rhs.IPaddress << " : " << "inactive" <<endl;
    return out;
}
