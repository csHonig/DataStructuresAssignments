#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Print the inventory" << endl;
    cout << "2. Delete a movie" << endl;
    cout << "3. Quit" << endl;
}

void split(string line,string arr[],char d,int num) {
    int count = 0;
    string temp;
    int i = 0;
    while(line[i] != '\n') {
        if(line[i] == d) {
            arr[count] = temp;
            temp = "";
            count++;
        }
        else if(i == line.length()) { // for last item
            arr[count] = temp;
            return;
        }
        else if(count > num - 1) {
            return;
        }
        else {
            temp += line[i];
        }
        i++;
    }
}

int main(int argc, char *argv[]) {
    MovieTree movieTree;
    string filename = argv[1];
    ifstream fs(filename);
    string line, lineArr[4];
    while(getline(fs,line)) {
        split(line,lineArr,',',4);
        movieTree.addMovie(stoi(lineArr[0]),lineArr[1],stoi(lineArr[2]),stof(lineArr[3]));
    }
    fs.close();
    while(true) {
        displayMenu();
        string userChoice;
        getline(cin,userChoice);
        if(userChoice == "1") {
            movieTree.printMovieInventory();
        }
        if(userChoice == "2") {
            cout << "Enter a movie title:" << endl;
            getline(cin,userChoice);
            movieTree.deleteMovie(userChoice);
        }
        if(userChoice == "3") {
            cout << "Goodbye!" << endl;
            return 0;
        }
    }
    return 0;
}