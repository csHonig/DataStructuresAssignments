#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Game.hpp"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

void wait() { // wait for user input
    string c;
    cout << "Enter any key to continue" << endl;
    cout << "> ";
    getline(cin,c);
    cout << endl;
}

void clearConsole() { // clear the console
    wait();
    for(int i = 0; i < 100; i++) {
        cout << endl;
    }
}

int getUserInput(int lowerRange, int upperRange) {
    string choice;
    getline(cin,choice);
    while(choice.size() > 1) {
            cout << "Enter a 1 digit number" << endl;
            cout << "> ";
            getline(cin,choice);
    }
    while(!isdigit(choice[0])) {
        cout << "Input must be a number" << endl;
        cout << "> ";
        getline(cin,choice);
    }
    while(stoi(choice) < lowerRange || stoi(choice) > upperRange) {
        cout << "Enter a valid number" << endl;
        cout << "> ";
        getline(cin,choice);
        while(!isdigit(choice[0])) {
            cout << "Input must be a number" << endl;
            cout << "> ";
            getline(cin,choice);
        }
    }
    return stoi(choice);
}

void split(string line, string arr[], char d, int num) { // splits a string, used for file reading
    int count = 0;
    string temp;
    int l = line.length();
    for(int i = 0; i < l;i++) {
        if(line[i] != d) {
            temp += line[i];
        }
        else {
            arr[count] = temp;
            temp = "";
            count++;
        }
        if(i == line.length() - 2) {
            arr[count] = temp;
        }
        if(count >= num) {
            return;
        }
    }
}

void checkInRange(string input, int lowerBound, int upperBound) {
    
}

Game::Game() { // set up Game
    setupHouse("./SetupFiles/rooms.txt","./SetupFiles/edges.txt");
    setupObjectives("./SetupFiles/testObj.txt"); // change testObj to objectiveSetup to run full game
    FamilyMember aunt("aunt");
    members[0] = aunt;
    FamilyMember dad("dad");
    members[1] = dad;
    FamilyMember uncle("uncle");
    members[2] = uncle;
    FamilyMember mom("mom");
    members[3] = mom;
    FamilyMember sister("sister");
    members[4] = sister;
    setupFamilyMember("./SetupFiles/familyMembers/auntSetup.txt",0);
    setupFamilyMember("./SetupFiles/familyMembers/dadSetup.txt",1);
    setupFamilyMember("./SetupFiles/familyMembers/uncleSetup.txt",2);
    setupFamilyMember("./SetupFiles/familyMembers/momSetup.txt",3);
    setupFamilyMember("./SetupFiles/familyMembers/sisterSetup.txt",4);
    placeFamily("./SetupFiles/famList.txt");
    setupRoomItems("./SetupFiles/items.txt");
    
}

void welcome() { // prints game welcome message
    cout << "Welcome to Surviving Thanksgiving!" << endl;
    wait();
    cout << "This is a text-based scavanger hunt where the objective is to make it through a family Thanksgiving." << endl;
    wait();
    cout << "You will be given objectives you must complete to make it to dinner. You complete objectives by bringing objects into specified rooms." << endl;
    wait();
    cout << "Throughout the game, you will have conversations with your family members. " << endl;
    wait();
    cout << "You will be able to choose how to respond to them, and those choices will affect their mood." << endl;
    wait();
    cout << "At the end, you will recieve a score that is dependant on your family member's mood. The happier they are, the better you will score!" << endl;
    wait();
    cout << "If the score is too low, you will have ruined Thanksgiving and you will lose the game." << endl;
    wait();
    cout << "Let's begin!" << endl;
    clearConsole();
}

void Game::setupHouse(string roomFile, string edgeFile) { // set up house, set up rooms and set up edges
    ifstream roomStream(roomFile);
    if(roomStream.is_open()) {
        string line;
        string lineArr[2];
        while(getline(roomStream,line)) {
            split(line,lineArr,',',2);
            myHouse.addRoom(lineArr[0]);
        }
    }
    else {
        cout << "Cannot open " << roomFile << endl;
    }
    ifstream edgeStream(edgeFile);
    if(edgeStream.is_open()) {
        string line;
        string lineArr[3];
        while(getline(edgeStream,line)) {
            split(line,lineArr,',',3);
            myHouse.addEdge(lineArr[0],lineArr[1]);
        }
    }
    else {
        cout << "Cannot open " << edgeFile << endl;
    }
}

void Game::setupObjectives(string objectiveFile) { // set up objectives
    ifstream objectiveStream(objectiveFile);
    if(objectiveStream.is_open()) {
        string line;
        string objArr[7];
        while(getline(objectiveStream,line)) {
            split(line,objArr,'|',7);
            Room* objRoom = myHouse.getRoom(objArr[2]);
            myObjectives.addObjective(objArr[0],objArr[1],objRoom,objArr[3],objArr[4],objArr[5]);
        }
    }
    else {
        cout << "Cannot open " << objectiveFile << endl;
    }
}

void Game::setupFamilyMember(string memberFile,int index) { // set up family member
    ifstream storyStream(memberFile);
    if(storyStream.is_open()) {
        string line;
        string lineArr[4];
        while(getline(storyStream,line)) {
            split(line,lineArr,'|',4);
            members[index].addTopic(lineArr[0],lineArr[1],lineArr[2]);
        }
    }
    else {
        cout << "Cannot open " << memberFile << endl;
    }
}

void Game::placeFamily(string familyFile) { // set up family members in rooms
    ifstream familyStream(familyFile);
    if(familyStream.is_open())
    {
        string line;
        FamilyMember* fm = NULL;
        Room* r = NULL;
        while(getline(familyStream,line))
        {
            string seg[3];
            split(line, seg, ',',3);
            for(int i = 0; i < 5; i++) {
                if(members[i].getName() == seg[0]) {
                    fm = &members[i];
                }
            }
            r = myHouse.getRoom(seg[1]);
            myHouse.setFamilyMemberInRoom(r, fm);
        }
    }
    else {
        cout << "Cannot open " << familyFile << endl;
    }
}

void Game::setupRoomItems(string itemFile) { // set up items in rooms
    ifstream itemFilestream(itemFile);
    if(itemFilestream.is_open()) {
        string line;
        string lineArr[4];
        while(getline(itemFilestream,line)) {
            split(line,lineArr,',',4);
            Room* r = myHouse.getRoom(lineArr[1]);
            myHouse.makeItemInRoom(lineArr[0],r);
        }
    }
    else {
        cout << "Cannot open " << itemFile << endl;
    }
}

void conversation(FamilyMember* f) { // start up conversation with family member
    f->setCurrent(f->getRoot());
    cout << "Your " << f->getName() << " walks up to you." << endl;
    string choice;
    while(f->checkIfOver()) {
        cout << f->getCurrent()->topic << endl;
        cout << "(1) " << f->getCurrent()->leftResponse << " (2) " << f->getCurrent()->rightResponse << endl;
        cout << "> ";
        int choice = getUserInput(1,2);
        if(choice == 1){
            f->goLeft();
        }
        else {
            f->goRight();
        }
    }
    cout << f->getCurrent()->topic << endl;
    cout << "Conversation is over, your " << f->getName() << " is " << f->getCurrent()->rightResponse << endl;
}

void Game::interaction() { // check if family member interaction should start
    Room* currentRoom = myHouse.getCurrentRoom();
    if(currentRoom->member == NULL)
        return;
    FamilyMember* person = myHouse.getFamilyMemberInRoom(currentRoom);
    if(person->getCompleted()) {
        return;
    }
    conversation(person);
    Conversation* currConvo = person->getCurrent();
    int newMood = stoi(currConvo->leftResponse);
    person->setMood(newMood);
    myHouse.getCurrentRoom()->member->markCompleted(); // mark conversation as completed
    clearConsole();
}

void Game::printObjectiveRequirements() { // prints remaining objective items to be gathered
    cout << "Status: You need to bring these objects to the " << myObjectives.getCurrObjective()->location->roomName << endl;
    int size = myObjectives.getCurrObjective()->objItems.size();
    for(int i = 0; i < size; i++) {
        cout << " - " << myObjectives.getCurrObjective()->objItems[i] << endl;
    }
    cout << endl;
}

void Game::checkObjectiveCompletion() { // check if objective items have been brought into correct room
    Objective* currObj = myObjectives.getCurrObjective();
    int size = currObj->objItems.size();
    string itemName = "";
    if(currObj->location == myHouse.getCurrentRoom()) {
        for(int i = 0; i < size; i++) {
            bool itemFound = false;
            itemName = currObj->objItems[i];
            itemFound = myInventory.checkForItem(itemName); 
            if(itemFound && itemName != "") { // if item needed for objective is found in the inventory
                currObj->objItems.erase(currObj->objItems.begin() + i); // remove element from objective requirement
                myInventory.removeItem(itemName); // remove item from inventory
                cout << itemName << " has been removed from your inventory for objective: " << currObj->title << endl;
                wait();
            }
            size = currObj->objItems.size();
        }
        size = currObj->objItems.size(); // update size
        if(size == 0) { // objective is finished when all items for objective are acquired
            myObjectives.getCurrObjective()->completed = true; // set objective as completed
            myObjectives.nextObjective(); // go on to next objective
            if(myObjectives.getCurrObjective() == NULL) 
                return;
            cout << "New Objective: " << myObjectives.getCurrObjective()->title << endl;
            cout << "Description: " << myObjectives.getCurrObjective()->description << endl;
            wait();
        }
    }
}

bool Game::acquireItem() { // get items from room and place into inventory
    Room* currentRoom = myHouse.getCurrentRoom();
    int numItems = currentRoom->items.size();
    myHouse.printItemsInRoom(currentRoom);
    if(numItems > 0) {
        cout << "What item do you want to pick up? " << endl;
        for(int i = 1; i < numItems; i++) {
            cout << "(" << i << ") " << currentRoom->items[i] << endl;
        }
        cout << "(" << numItems << ") I don't want to pick up or drop off any items." << endl;
        cout << "(" << numItems + 1 << ") I want to drop an item." << endl;
        int numChoice = getUserInput(1,numItems + 1);
        if(numChoice == numItems) { // Pick up no items
            cout << "Moving on!" << endl;
            wait();
            return false;
        }
        else if(numChoice == numItems + 1) { // Leave item here
            if(myInventory.getNumItems() == 0) { // if inv is empty
                cout << "Cannot leave items here, your inventory is empty" << endl;
                return true;
            }
            myInventory.printInventory();
            cout << "What item would you like to leave here? " << endl;
            cout << "> ";
            int choice = getUserInput(1,myInventory.getNumItems());
            string itemName = myInventory.getItemAt(choice - 1);
            if(itemName == "") {
                cout << "You cannot leave nothing" << endl;
                wait();
                return true;
            }
            myInventory.removeItem(itemName);
            myHouse.makeItemInRoom(itemName,currentRoom);
            cout << "Dropping: " << itemName << endl;
            return true;
        }
        else { // pick up item
            if(!myInventory.checkFull()) {
                myInventory.addItem(currentRoom->items[numChoice]);
                myHouse.removeItemFromRoom(currentRoom,numChoice);
            }
            else
                cout << "Your inventory is full, cannot pick up item" << endl;
            return true;
        }
    }
    return false;
}

void Game::promptNextRoom() { // ask user what room to go into next
    cout << "What room do you want to go next? Or enter (0) to exit" << endl;
    myHouse.displayCurrentEdges();
    string choice;
    cout << "> ";
    int numAdj = myHouse.getCurrentRoom()->nearRoom.size();
    int intChoice = getUserInput(0,numAdj);
    if(intChoice == 0) {
        exit(EXIT_SUCCESS);
    }
    Room* newRoom = myHouse.getCurrentRoom()->nearRoom[intChoice - 1].v;
    cout << "Going to " << newRoom->roomName << endl;
    myHouse.setCurrentRoom(newRoom);
    clearConsole();
}

void Game::moods() { // calculate moods and score for game
    int moodTot = 0;
    for(int i = 0; i < 5; i++) {
        int currMood = members[i].getMood();
        string m = "";
        if(currMood < 0) {
            m = "mad";
        }
        else if(currMood > 0) {
            m = "happy";
        }
        else {
            m = "neutral";
        }
        cout << members[i].getName() << "'s mood: " << m << endl;
        moodTot += members[i].getMood();
    }
    if(moodTot < -5)
        moodTot = 0;
    if(moodTot > 5) 
        moodTot = 5;
    int score = (moodTot + 5) * 10;
    cout << "Score: " <<  score << endl;

    if(score < 50) 
        cout << "You have ruined Thanksgiving" << endl;
    else
        cout << "Congratulations, you have survived Thanksgiving" << endl;
}

void Game::run() { // start game
    myHouse.stringSetCurrRoom("kitchen"); // set starting location
    welcome(); // prints welcome message, including rules
    bool gameOver = false;
    while(!gameOver) { // exits when all objectives are completed
        checkObjectiveCompletion();
        if(myObjectives.allCompleted()) {
            gameOver = true;
        }
        else { 
            if(rand() % 100 < 100) // chance of interaction with family member
                interaction();
            cout << "Current Objective: " << myObjectives.getCurrObjective()->title << endl;
            cout << "Description: " << myObjectives.getCurrObjective()->description << endl; 
            cout << "Current room: " << myHouse.getCurrentRoom()->roomName << endl;
            bool gettingItems = true;
            while(gettingItems) {
                clearConsole();
                printObjectiveRequirements();
                myInventory.printInventory();
                gettingItems = acquireItem();
            }
            promptNextRoom();
        }
    }
    moods();
    cout << "Thanks for playing!" << endl;
}

int main () {
    srand(time(NULL)); // seed rand()
    Game myGame;
    myGame.run(); // start game
    return 0;
}