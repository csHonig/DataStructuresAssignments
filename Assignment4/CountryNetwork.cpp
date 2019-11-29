/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork() {
    head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty() {
    if(head == NULL){
        return true;
    }
    return false;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    // If this is the first country to be inserted
    Country* temp;
    if(previous == NULL) {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        temp = new Country;
        temp->name = countryName;
        temp->next = head;
        head = temp;
    }
    // Put in new node between previous and next nodes
    else {
       cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
       temp = new Country; // make new Country
       temp->name = countryName; // put in the country name
       temp->next = previous->next; // make new node point to next node
       previous->next = temp; // make previous node point to new node
    }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    Country* current = head;
    Country* previous = head;
    bool exists = false;
    while(current != NULL) {
        if(head->name == countryName) {
            exists = true;
            head = current->next;
            free(current);
        }
        else if(current->name == countryName) { // find where the input country name is
            exists = true;
            previous->next = current->next;
            free(current);
        }
        previous = current;
        current = current->next;
    }
    if(exists == false) {
        cout << "Country does not exist." << endl;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
    //deleteEntireNetwork();
    insertCountry(NULL,"United States");
    insertCountry(head,"Canada");
    Country* newPtr1 = head->next;
    insertCountry(newPtr1,"Brazil");
    Country* newPtr2 = newPtr1->next;
    insertCountry(newPtr2,"India");
    Country* newPtr3 = newPtr2->next;
    insertCountry(newPtr3,"China");
    Country* newPtr4 = newPtr3->next;
    insertCountry(newPtr4,"Australia");
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName) {
    Country* current = head;
    while(current!=NULL) {
       if(current->name == countryName) {
           return current;
       }
       current = current->next;
    }
    return NULL;
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork() {
    Country* current = head;
    bool ignore = false;
    if(head==NULL){
        ignore = true;
    }
    while(current != NULL) {
        cout << "deleting: " << current->name << endl;
        free(current);
        current = current->next;
    }
    head = NULL;
    if(ignore == false){
        cout << "Deleted network" << endl;
    }
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
 void CountryNetwork :: rotateNetwork(int n) {
    Country* current = head;
    Country* previous = head;
    int count = 0;
    while(current!=NULL) {
        count++;
        current = current->next;
    }
    current = head;
    if(head == NULL) {
        cout << "Linked List is Empty" << endl;
        return;
    }
    else if(n < 1 || n > count) {
        cout << "Rotate not possible" << endl;
    }
    else {
        int count = 1;
        while(count < n && current != NULL) {
            current = current->next;
            count++;
        }
        if(current == NULL) {
            return;
        }
        Country *kthNode = current;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = head;
        head = kthNode->next;
        kthNode->next = NULL;
        cout << "Rotate Complete" << endl;
    }
}

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork() {
    Country* current = head; 
    Country *prev = NULL, *next = NULL; 
    while (current != NULL) { 
        // Store next 
        next = current->next; 
        // Reverse current node's pointer 
        current->next = prev; 
        // Move pointers one position ahead. 
        prev = current; 
        current = next; 
    } 
    head = prev; 
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    /*if(head==NULL) {
        cout << "nothing in path" << endl << "===" << endl;
    }*/
    Country* current = head;
    cout << "== CURRENT PATH ==" << endl;
    if(current == NULL) {
        cout << "nothing in path" << endl << "===" << endl;
    }
    else {
        while(current != NULL) {
        cout << current->name << " -> ";
        current = current->next;
        }
        cout << "NULL" << endl << "===" << endl;
    }
}
