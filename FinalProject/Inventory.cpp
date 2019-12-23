#include "Inventory.hpp"
using namespace std;

Inventory::Inventory() { // constructor
    numItems = 0; // initialize number of items player has to 0
    for(int i = 0; i < maxSize; i++) {
        playerInventory[i] = "";
    }
}

void Inventory::addItem(string newItem) { // add item to room
    for(int i = 0; i < maxSize; i++) { // check to see if there is an open slot to put new item in
        if(playerInventory[i] == "") {
            playerInventory[i] = newItem;
            numItems++;
            return;
        }
    }
}

void Inventory::removeItem(string n) { // remove item from room
    for(int i = 0; i < numItems; i++) {
        if(playerInventory[i] == n) {
            playerInventory[i] = "";
            numItems--;
        }
    }
}

string Inventory::getItemAt(int index) { // get room at index
    return playerInventory[index];
}

bool Inventory::checkForItem(string n) { // returns true if item is in inventory
    for(int i = 0; i < maxSize; i++) {
        if(playerInventory[i] == n) 
            return true;
    }
    return false;
}

void Inventory::printInventory() { // print inventory
    cout << "Your Inventory: " << endl;
    for(int i = 0; i < maxSize; i++) {
        if(playerInventory[i] == "") {
            cout << i + 1 << ". " << "empty slot" << endl;    
        }
        else
            cout << i + 1 << ". " << playerInventory[i] << endl;
    }
    cout << endl;
}

int Inventory::getNumItems() { // get number of items in inventory
    return numItems;
}

bool Inventory::checkFull() { // returns true if inventory is full
    if(numItems == maxSize) {
        return true;
    }
    return false;
}

void Inventory::clearInventory() { // delete all items in inventory
    for(int i = 0; i < maxSize; i++) {
        playerInventory[i] = "";
    }
    numItems = 0;
}