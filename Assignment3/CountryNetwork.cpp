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
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
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
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message) {
    Country* current = head;
    if(current==NULL) {
        cout << "Empty list" << endl;
    }
    else if (searchNetwork(receiver) == NULL){
        cout << "Country not found" << endl;
     }
    else {
        while(current != NULL) {
            current->message = message;
            current->numberMessages++;
            cout << current->name << " [# messages received: " << current->numberMessages << "] received: " << current->message << endl;
            if(current->name == receiver) {
                break;
            }
            current = current->next;
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
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
