#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Park {
    string parkname;
    string state;
    int area;
};

void addPark(Park parks[], string parkname, string state, int area, int length);
void printList(const Park parks[], int length);

int main(int argc,char *argv[]){
    Park parks[100];
    int length = 0;
    ifstream inStream(argv[1]);
    if(inStream.is_open()){
        string line,temp,tempParkName,tempState;
        int tempArea,index;
        while(getline(inStream,line)){
            index = 0;
            stringstream ss(line);
            while(getline(ss,temp,',')){
                switch(index){
                    case 0: tempParkName = temp; 
                        break;
                    case 1: tempState = temp;
                        break;
                    case 2: tempArea = stoi(temp);  
                        break;
                }
                index++;
            }
            addPark(parks,tempParkName,tempState,tempArea,length);
            length++;
        }
        printList(parks,length);

        ofstream outStream(argv[2]);
        for(int i = 0; i < length; i++){
            if(parks[i].area > stoi(argv[3])){
                outStream << parks[i].parkname << "," << parks[i].state << "," << parks[i].area << "\n";
            }
        }
    }
    else
        cout << "Failed to open file." << endl;
}

void addPark(Park parks[], string parkname, string state, int area, int length){
    parks[length].parkname = parkname;
    parks[length].state = state;
    parks[length].area = area;
}

void printList(const Park parks[], int length){
    for(int i = 0; i < length; i++){
        cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area << endl;
    }
}