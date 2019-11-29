/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

// declarations for main helper-functions
void displayMenu();

int main(int argc, char* argv[]) {
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    int userInput = 0;
    string countryInput, prevInput, messageInput;
    Country* previous;
    while(userInput!=5) {
        displayMenu();
        cin >> userInput;
        cin.ignore();
        switch(userInput) {
            case 1:
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
                break;
            case 2:
                CountryNet.printPath();
                break;
            case 3:
                cout << "Enter name of the country to receive the message: " << endl;
                getline(cin,countryInput);
                cout << "Enter the message to send: " << endl;
                getline(cin,messageInput);
                cout << endl;
                CountryNet.transmitMsg(countryInput,messageInput);
                break;
            case 4:
                cout << "Enter a new country name:" << endl;
                getline(cin,countryInput);
                cout << "Enter the previous country name (or First):" << endl;
                getline(cin,prevInput);
                if(prevInput  == "First") {
                    CountryNet.insertCountry(NULL,countryInput);
                }
                else {
                    previous = CountryNet.searchNetwork(prevInput);
                    while(previous == NULL) {
                        cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                        getline(cin, prevInput);
                        previous = CountryNet.searchNetwork(prevInput);
                    }
                    CountryNet.insertCountry(previous,countryInput);
                }
                CountryNet.printPath();
                break;
            case 5:
                cout << "Quitting..." << endl;
                cout << "Goodbye!" << endl;
                return 0;
                break;
            default:
                cout << "Enter a number between 1 and 5" << endl;
                break;
        }
    }
    return 0;
}


/*
 * Purpose; displays a menu with options
 */
void displayMenu() {
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
