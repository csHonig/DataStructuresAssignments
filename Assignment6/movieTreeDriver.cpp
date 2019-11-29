#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Query movies" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Average Rating of movies" << endl;
    cout << "5. Quit" << endl;
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
        movieTree.addMovieNode(stoi(lineArr[0]),lineArr[1],stoi(lineArr[2]),stof(lineArr[3]));
    }
    fs.close();
    while(true) {
        displayMenu();
        string userChoice;
        getline(cin,userChoice);
        if(userChoice == "1") {
            string inputTitle;
            cout << "Enter title:" << endl;
            getline(cin,inputTitle);
            movieTree.findMovie(inputTitle);
        }
        if(userChoice == "2") {
            string inputRating, inputYear;
            cout << "Enter minimum rating:" << endl;
            getline(cin,inputRating);
            cout << "Enter minimum year:" << endl;
            getline(cin,inputYear);
            movieTree.queryMovies(stof(inputRating),stoi(inputYear));
        }
        if(userChoice == "3") {
            movieTree.printMovieInventory();
        }
        if(userChoice == "4") {
            movieTree.averageRating();
        }
        if(userChoice == "5") {
            cout << "Goodbye!" << endl;
            return 0;
        }
    }
    return 0;
}