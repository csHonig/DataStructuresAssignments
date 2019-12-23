#include "ObjectiveList.hpp"
using namespace std;

MissionList::MissionList() { // objective constructor
    start = NULL;
    curr = start;
}

MissionList::~MissionList() { // objective deconstructor
    Objective* current = start;
    while( current != 0 ) {
        Objective* next = current->next;
        delete current;
        current = next;
    }
}

void MissionList::addObjective(string t, string d, Room* l, string item1, string item2, string item3) { // add objective to LL
    Objective* temp = new Objective;
    temp->title = t;
    temp->description = d;
    temp->location = l;
    temp->objItems.push_back(item1);
    temp->objItems.push_back(item2);
    temp->objItems.push_back(item3);
    if(start==NULL)//First Node added will become start Objective
    {
        start = temp;
        curr = start; //curr obj
        return;
    }
    Objective* temp2;
    temp2 = start;
    while(temp2->next!=NULL)
    {
        temp2=temp2->next;
    }
    temp2->next = temp;
}

void MissionList::printAllObj() { // print all objectives 
    Objective* temp;
    temp=start;
    if(temp==NULL)
    {
        cout << "Empty List\n";
        return;
    }
    while(temp->next!=NULL)
    {
        cout << temp->title <<endl;
        temp=temp->next;
    }
    cout << temp->title << endl;
}

void MissionList::nextObjective() { // change current objective to next objective
    curr = curr->next;
}

Objective* MissionList::getCurrObjective() { // returns current objective
    return curr;
}

bool MissionList::allCompleted() { // checks if objectives have been completed
    Objective* temp = start;
    while(temp != NULL) {
        if(temp->completed == false)
            return false;
        temp = temp->next;
    }
    return true;
}

void MissionList::removeItem(string n) { // remove item from vector 
    int size = curr->objItems.size();
    for(int i= 0; i < size; i++) {
        if(curr->objItems[i] == n)
            curr->objItems.erase(curr->objItems.begin() + i);
    }
}