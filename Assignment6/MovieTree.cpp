#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <stack>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST

MovieTree::MovieTree() {
  root = NULL;
}

void deleteRecursive(MovieNode* node) { // a function that deletes every element under a node recursively
  if (node!=NULL) {
    deleteRecursive(node->left);
    deleteRecursive(node->right);
    delete node;
  }
}

MovieTree::~MovieTree() {
  deleteRecursive(root); // destroy everything under root
}

void MovieTree::printMovieInventory() {
  if(root == NULL) {
    cout << "Tree is Empty. Cannot print" << endl;
    return;
  }
  stack<MovieNode *> s;
  MovieNode* m = root;
  while (m != NULL || s.empty() == false) 
  { 
    while (m !=  NULL) 
    { 
      s.push(m); 
      m = m->left; 
    } 
    m = s.top(); 
    s.pop(); 
    cout << "Movie: " << m->title << " " << m->rating << endl;
    m = m->right; 
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  if (root == NULL) {
    MovieNode* newNode = new MovieNode(ranking,title,year,rating);
    root = newNode;
    return;
  }
  MovieNode* c = root; // current node
  MovieNode* p = NULL; // previous node
  while (c != NULL) {
    p = c;
    if (title < c->title)
      c = c->left;
    else
      c = c->right;
  }
  MovieNode* node = new MovieNode(ranking,title,year,rating);
  if (title < p->title)
    p->left = node;
  else
    p->right = node;
}

void MovieTree::findMovie(string title) {
  MovieNode* currNode = root;
  bool found = false;
  while (currNode != NULL) { 
    if (title > currNode->title) 
      currNode = currNode->right; 
    else if (title < currNode->title) 
      currNode = currNode->left; 
    else if (title == currNode->title) {
      found = true;
      break;
    }
  }
  if(found == true) { // print movie info
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << currNode->ranking << endl;
    cout << "Title :" << currNode->title << endl;
    cout << "Year :" << currNode->year << endl;
    cout << "rating :" << currNode->rating << endl;
    return;
  }
  else 
    cout << "Movie not found." << endl;
}

void MovieTree::queryMovies(float rating, int year) {
  if (root == NULL) {
    cout << "Tree is Empty. Cannot query Movies" << endl;
    return;
  }
  // Create an empty stack and push root to it
  stack<MovieNode *> nodeStack; 
  nodeStack.push(root); 
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  while (!nodeStack.empty()) {
    MovieNode* m = nodeStack.top(); 
    if(m->rating >= rating && m->year > year) {
      cout << m->title << "(" << m->year << ") " << m->rating << endl;
    }
    nodeStack.pop();
    // Push right and left children of the popped node to stack
    if (m->right) 
      nodeStack.push(m->right); 
    if (m->left) 
      nodeStack.push(m->left);
  }
}

void MovieTree::averageRating() {
  if(root == NULL) {
    cout << "Average rating:0.0" << endl;
    return;
  }
  float totRatings;
  float numRatings;

  stack<MovieNode *> s;
  MovieNode *curr = root; 
  // traverse linked list inorder
  while (curr != NULL || s.empty() == false) { 
    while (curr !=  NULL) {
      s.push(curr); 
      curr = curr->left; 
    } 
    curr = s.top(); 
    s.pop(); 
    totRatings += curr->rating;
    numRatings++;
    curr = curr->right; 
  }
  float avg = totRatings / numRatings;
  cout << "Average rating:" << avg << endl;
}
