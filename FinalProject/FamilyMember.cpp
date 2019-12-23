#include "FamilyMember.hpp"
#include <queue>
using namespace std;

FamilyMember::FamilyMember() { // default constructor
    root = NULL;
    current = root;
    name = "";
    mood = 0;
}

void deconstruct(Conversation* node) { // a function that deletes every element under a node recursively
  if (node!=NULL) {
    deconstruct(node->left);
    deconstruct(node->right);
    delete node;
  }
}

FamilyMember::~FamilyMember() { // deconstructor
    deconstruct(root);
}

FamilyMember::FamilyMember(string n) { // parameterized constructor
    name = n;
    root = NULL;
    current = NULL;
    completed = false;
    mood = 0;
}

void FamilyMember::goLeft() { // set current pointer to left child of previous current pointer
    if(current->left == NULL) {
        cout << "Left child does not exist" << endl;
        return;
    }   
    current = current->left;
}

void FamilyMember::goRight() { // set current pointer to right child of previous current pointer
    if(current->right == NULL) {
        cout << "Right child does not exist" << endl;
        return;
    }
    current = current->right;
}

void FamilyMember::addTopic(string t, string lr, string rr) { // add topic (Node) to FamilyMember Tree
    Conversation* newNode = new Conversation(t,lr,rr);
    if (root == NULL) {
        root = newNode;
        return;
    }
    Conversation* temp = root;
    queue<struct Conversation*> q;
    q.push(temp);
    // Do level order traversal until we find an empty place.
    while (!q.empty()) { 
        temp = q.front(); 
        q.pop(); 
  
        if (!temp->left) { 
            temp->left = newNode; 
            break; 
        } 
        else
            q.push(temp->left); 
        if (!temp->right) { 
            temp->right = newNode; 
            break; 
        } 
        else
            q.push(temp->right); 
    } 
}

void FamilyMember::setCurrent(Conversation* d) { // set current node
    current = d;
}

Conversation* FamilyMember::getCurrent() { // returns current node
    return current;
}

Conversation* FamilyMember::getRoot() { // returns root node
    return root;
}

void FamilyMember::setMood(int m) { // changes mood value for Family Member object
    mood = m;
}
int FamilyMember::getMood() { // returns mood for Family Member Object
    return mood;
}

bool FamilyMember::checkIfOver() { // Checks to See if Family Member Tree is over
    if(current->left == NULL || current->right == NULL) {
        int newMood = stoi(current->leftResponse);
        mood = newMood;
        return false;
    }
    return true;
}
void FamilyMember::markCompleted() { // mark conversation completed
    completed = true;
}
string FamilyMember::getName() { // returns name of Family Memeber
    return name;
}

bool FamilyMember::getCompleted() { // checks if Binary Tree has been completed
    return completed;
}