#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>

using namespace std;

class Inventory { // A class for player's inventory
    private:
        const static int maxSize = 4; // max size of player's inventory, subject to change
        string playerInventory[maxSize];
        int numItems; // number of items currently in inventory
    public:
        Inventory();
        void addItem(string newItem);
        void removeItem(string n);
        string getItemAt(int index);
        bool checkForItem(string n);
        void printInventory();
        int getNumItems();
        bool checkFull();
        void clearInventory();
};
#endif