#include "House.hpp"
using namespace std;

House::House() { // default constructor
    start = NULL;
    current = NULL;
    numRooms = 0;
}

House::~House() { // deconstructor
    int size = roomList.size();
    for(int i = 0; i < size; i++)
    {
        delete roomList[i];
    }
}

void House::addRoom(string name) { // adds Room Node to House (Graph) Data Structure
    Room* temp = new Room;
    temp->roomName = name;
    roomList.push_back(temp);
    numRooms++;
}

void House::addEdge(string v1, string v2) { // adds connection between two Rooms
    for(int i = 0; i < roomList.size(); i++) {
        if(roomList[i]->roomName == v1) {
            for(int j = 0; j < roomList.size(); j++) {
                if(roomList[j]->roomName == v2 && i != j) {
                    adjRoom av;
                    av.v = roomList[j];
                    roomList[i]->nearRoom.push_back(av);
                    //another vertex for edge in other direction
                    adjRoom av2;
                    av2.v = roomList[i];
                    roomList[j]->nearRoom.push_back(av2);
                }
            }
        }
    }
}

void House::makeItemInRoom(string n, Room* r) { // creates Item in room
    r->items.push_back(n);
}

void House::printItemsInRoom(Room* r) { // prints items in the room
    cout << "Items in " << r->roomName << ": " << endl;
    int size = r->items.size();
    for(int i = 1; i < size; i++){
        cout << "(" << i << ") " << r->items[i] << endl;
    }
    cout << endl;
}

void House::setFamilyMemberInRoom(Room* r, FamilyMember* m) { // sets family member for room
    r->member = m;
}

FamilyMember* House::getFamilyMemberInRoom(Room* r) { // returns family member for room
    return r->member;
}

Room* House::getRoom(string name) { // returns room from given string
    int index = 0;
    for(int i = 0; i < numRooms; i++)
    {
        if(roomList[i]->roomName == name)
            return roomList[i];
    }
    return NULL;
}

Room* House::getCurrentRoom() { // returns current room player is in
    return current;
}

void House::setCurrentRoom(Room* r) { // sets current room player is in
    current = r;
}

void House::stringSetCurrRoom(string s) { // sets current room player is in with a string
    Room* r = getRoom(s);
    current = r;
}

void House::displayRooms() { // prints room list
    int size = roomList.size();
    for(int i = 0; i < size; i++) {
       cout << roomList[i]->roomName << endl;
    }
}

int House::numAdjRooms(string Rname) { // returns number of rooms connected to input room
    Room* C = getRoom(Rname);
    int size = C->nearRoom.size();
    return size;
}

void House::displayEdges() { // print all edges
    int size = roomList.size();
    for(int i = 0; i < size; i++) {
        Room* x = roomList[i];
        cout << roomList[i]->roomName << " is connected to:" << endl;
        int size2 = x->nearRoom.size();
        for(int j = 0; j < size2; j++) {
            cout << x->nearRoom[j].v->roomName << endl;
        }
        cout << endl;
    }
}

void House::displayCurrentEdges() { // print edges for current room
    int sofAdj = current->nearRoom.size();
    cout << current->roomName << " is connected to:" <<endl;
    for(int i = 0; i < sofAdj; i++) {
        cout << "(" << i + 1 << ") " << current->nearRoom[i].v->roomName << endl;
    }
}

void House::removeItemFromRoom(Room* r,int index) { // remove item from input room
    string name = r->items[index];
    r->items.erase(r->items.begin() + index);
    cout << "You have taken " << name << " from the " << r->roomName << endl;
}