#ifndef OBJECTIVELIST_HPP
#define OBJECTIVELIST_HPP

#include "House.hpp"
#include "Inventory.hpp"
#include <iostream>
#include <vector>

using namespace std;

struct Objective
{
    Objective()
    {
        title = "NULL";
        description = "NULL";
        next = NULL;
        completed = false;
    }
    string title; // title of objective
    string description; // description of objective
    Room* location;
    bool completed;
    vector<string> objItems; // a vector of all items needed for objective
    Objective* next; // pointer to next objective
};

class MissionList
{
    private:
        Objective* curr;
        Objective* start;
    public:
        MissionList();
        ~MissionList();
        void addObjective(string t, string d, Room* l, string item1, string item2, string item3);
        void printAllObj();
        void nextObjective();
        Objective* getCurrObjective();
        bool allCompleted();
        void removeItem(string n);
};

#endif