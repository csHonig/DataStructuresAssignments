#ifndef FAMILYMEMBER_HPP
#define FAMILYMEMBER_HPP

#include <iostream>
using namespace std;

struct Conversation { // A Node For Binary Tree
    Conversation(string t, string lr, string rr) {
        topic = t;
        leftResponse = lr;
        rightResponse = rr;
        left = NULL;
        right = NULL;
    }
    Conversation() {
        topic = "";
        leftResponse = "";
        rightResponse = "";
        left = NULL;
        right = NULL;
    }
    string topic; // current topic of conversation
    string leftResponse;
    string rightResponse;
    Conversation* left; // left choice Objective pointer
    Conversation* right; // right choice Objective pointer
};

class FamilyMember { // A Binary Tree Data Structure
    private:
        Conversation* root; // head of tree, the first encounter with the family member
        Conversation* current; // current node
        string name; //Family Member's name
        bool completed;
        int mood; // -1 is mad, 0 is neutral, 1 is happy
    public:
        FamilyMember();
        FamilyMember(string n);
        ~FamilyMember();
        void goLeft(); // go to left story conversation
        void goRight(); // go to right story conversation
        void addTopic(string t, string lr, string rr);
        void setCurrent(Conversation* d);
        Conversation* getCurrent();
        Conversation* getRoot(); // returns root
        void setMood(int m);
        int getMood();
        bool checkIfOver();
        void markCompleted();
        string getName();
        bool getCompleted();
};
#endif