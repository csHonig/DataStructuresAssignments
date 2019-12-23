#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "FamilyMember.hpp"
#include "Inventory.hpp"
#include <iostream>
#include <vector>
using namespace std;

struct Room;

struct adjRoom
{
    Room *v;
};

struct Room
{
    Room()
    {
        roomName = "";
        member = NULL;
        items = {""};
    }
    string roomName;
    vector<string> items;
    vector<adjRoom> nearRoom;
    FamilyMember* member;
};

class House
{
    private:
        Room* start; //starting room
        Room* current; //current room
        int numRooms;
        vector<Room*> roomList;//List Rooms
    public:
        House();
        ~House();
        void addRoom(string n);
        void addEdge(string s1, string s2);
        void makeItemInRoom(string n, Room* room);
        void printItemsInRoom(Room* r);
        void setFamilyMemberInRoom(Room* r, FamilyMember* m);
        FamilyMember* getFamilyMemberInRoom(Room* r);
        Room* getRoom(string name);
        Room* getCurrentRoom();
        void setCurrentRoom(Room* c);
        void stringSetCurrRoom(string name);
        void displayRooms();
        int numAdjRooms(string name);
        void displayEdges();
        void displayCurrentEdges();
        void removeItemFromRoom(Room* r, int index);
};

#endif