/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    int userInput = 0, rotateCount = 0;
    string countryInput, prevInput, messageInput;
    Country* previous;
    while(userInput!=8) {
        displayMenu();
        cin >> userInput;
        cin.ignore();
        switch(userInput) {
            case 1: // Build Network
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
                break;
            case 2: // Print network Path
                CountryNet.printPath();
                break;
            case 3: // Add country
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
                    //cout << endl;
                    CountryNet.insertCountry(previous,countryInput);
                }
                CountryNet.printPath();
                //cout << endl;
                break;
            case 4: // Delete a country
                cout << "Enter a country name:" << endl;
                getline(cin,countryInput);
                CountryNet.deleteCountry(countryInput);
                CountryNet.printPath();
                //cout << endl;
                break;
            case 5: // Reverse entire network
                CountryNet.reverseEntireNetwork();
                CountryNet.printPath();
                //cout << endl;
                break;
            case 6: // Rotate network
                cout << "Enter the count of values to be rotated:" << endl;
                cin >> rotateCount;
                cin.ignore();
                CountryNet.rotateNetwork(rotateCount);
                CountryNet.printPath();
                //cout << endl;
                break;
            case 7: // clear network
                cout << "Network before deletion" << endl;
                CountryNet.printPath();
                CountryNet.deleteEntireNetwork();
                //cout << "Deleted network" << endl;
                cout << "Network after deletion" << endl;
                CountryNet.printPath();
                //cout << endl;
                break;
            case 8: // quit
                cout << "Quitting... cleaning up path: " << endl;
                CountryNet.printPath();
                CountryNet.deleteEntireNetwork();
                if(CountryNet.isEmpty() == true) {
                    cout << "Path cleaned" << endl;
                }
                else {
                    cout << "Error: Path NOT cleaned" << endl;
                }
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Enter a number between 1 and 8" << endl;
                break;
        }
    }
    return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
