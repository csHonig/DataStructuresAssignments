#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <stack>
using namespace std;

MovieTree::MovieTree() { // constructor
    root = NULL;
}

void deconstruct(TreeNode* node) { // a function that deletes every element under a node recursively
  if (node!=NULL) {
    deconstruct(node->leftChild);
    deconstruct(node->rightChild);
    LLMovieNode* curr = node->head;
    while(curr != NULL) { // to delete LL at every TreeNode
      delete curr;
      curr = curr->next;
    }
    delete node;
  }
}

MovieTree::~MovieTree() { // deconstructor
    deconstruct(root);
}

void MovieTree::printMovieInventory() { // prints contents of BST and LL
  //Traverse Tree Nodes
  stack<TreeNode *> treeStack;
  TreeNode* currTree = root;
  LLMovieNode* currMovieNode;
  while (currTree != NULL || treeStack.empty() == false) {
    while (currTree !=  NULL) {
        treeStack.push(currTree); 
        currTree = currTree->leftChild; 
    }
    currTree = treeStack.top();
    treeStack.pop();
    cout << "Movies starting with letter: " << currTree->titleChar << endl;
    // traverse movie linked list for left subtree
    currMovieNode = currTree->head;
    while(currMovieNode != NULL && currTree != NULL) {
      cout << " >> " << currMovieNode->title << " " << currMovieNode->rating << endl; // print movies in LL
      currMovieNode = currMovieNode->next;
    }
    currTree = currTree->rightChild; // now visit righ subtree
  }
}

void MovieTree::addMovie(int ranking, string title, int year, float rating) { // function to addMovie
  LLMovieNode* newMovieNode = new LLMovieNode(ranking,title,year,rating); // allocate space for new movie node
  stack<TreeNode*> treeStack; // stack for all nodes in the tree
  TreeNode* currTree = root;
  bool found = false;
  while (currTree != NULL || treeStack.empty() == false) {
    while (currTree !=  NULL) {
        treeStack.push(currTree);
        currTree = currTree->leftChild;
    }
    currTree = treeStack.top();
    treeStack.pop();
    if(title[0] == currTree->titleChar) { // if movie starts with a character already in tree, insert into linked list
      found = true;
      LLMovieNode* currMovieNode = currTree->head;
      LLMovieNode* prevMovieNode = NULL;
      if(currMovieNode == NULL) { // if the LL for the letter is empty
        currTree->head = newMovieNode;
        newMovieNode->next = NULL;
        return;
      }
      if(title < currTree->head->title) { // if new item has to be inserted into LL head
        newMovieNode->next = currTree->head;
        currTree->head = newMovieNode;
        return;
      }
      while(currMovieNode != NULL) { // traverse LL to find where to insert
        if(title < currMovieNode->title) { // if title should be before current movie node
          newMovieNode->next = currMovieNode;
          prevMovieNode->next = newMovieNode;
          return;
        }
        else if(currMovieNode->next == NULL) { // if next node is NULL, add to end of LL
          currMovieNode->next = newMovieNode;
          newMovieNode->next = NULL;
          return;
        }
        prevMovieNode = currMovieNode;
        currMovieNode = currMovieNode->next; // move on to next node
      }
    }
    currTree = currTree->rightChild; // now visit righ subtree
  }
  if(found == false) { // make a new tree node and initialize the LL for that node with the data
    TreeNode* newTreeNode = new TreeNode;
    newTreeNode->titleChar = title[0];
    TreeNode* c = root; // current tree node
    TreeNode* p = NULL; // previous tree node
    if(root == NULL) {
      root = newTreeNode;
      newTreeNode->head = newMovieNode;
      return;
    }
    while (c != NULL) {
      p = c;
      if (title[0] < c->titleChar) 
        c = c->leftChild;
      else
        c = c->rightChild;
    }
    if (p == NULL)
      p = newTreeNode;
    else if (title[0] < p->titleChar)
      p->leftChild = newTreeNode;
    else
      p->rightChild = newTreeNode;
    newTreeNode->head = newMovieNode;
  }
}

TreeNode* findMin(TreeNode* root) { // function to find minimum of BST
    while(root->leftChild != NULL) {
        root=root->leftChild;
    }
    return root;
}

TreeNode* Delete(TreeNode* root,char value) { // function to delete a TreeNode in BST
	if(root == NULL) //if BST is empty
		return root;
	else if(value < root->titleChar) // traverse left
		root->leftChild = Delete(root->leftChild,value);
	else if(value > root->titleChar) // traverse right
		root->rightChild= Delete(root->rightChild,value);
	// Node deletion
	else {
		//case 1: Leaf Node
		if(root->leftChild==NULL && root->rightChild == NULL) {
			delete root;
			root=NULL;
			return root;
		}
		//case 2: one child
		else if(root->leftChild == NULL) {
			TreeNode* temp = root;
			root = root->rightChild;
			delete temp;
			return root;
		}
		else if(root->rightChild == NULL) {
			TreeNode* temp = root;
			root = root->leftChild;
			delete temp;
			return root;
		}
		//case 3: 2 child
		else {
			TreeNode* temp = findMin(root->rightChild); // find minimum value of left side to replace root with
			root->titleChar = temp->titleChar; // copy titleChar to new root node
      root->head = temp->head; // copy LL head to new root node
			root->rightChild = Delete(root->rightChild, temp->titleChar);
		}
	}
	return root;
}

void MovieTree::deleteMovie(string title) {
  stack<TreeNode*> treeStack; // stack for all nodes in the tree
  TreeNode* currTree = root; 
  bool deleted = false;
  while (currTree != NULL || treeStack.empty() == false) {
    while (currTree !=  NULL) {
      treeStack.push(currTree);
      currTree = currTree->leftChild;
    }
    currTree = treeStack.top();
    treeStack.pop();
    if(title[0] == currTree->titleChar) {
      LLMovieNode* currentMovieNode = currTree->head;
      LLMovieNode* previousMovieNode = NULL;
      while(currentMovieNode != NULL) {
        if(title == currentMovieNode->title) { // this is the LLMovieNode to be deleted
          if(currentMovieNode == currTree->head) { // if head is to be deleted
            currTree->head = currentMovieNode->next;
            delete currentMovieNode;
            deleted = true;
          }
          else if(currentMovieNode->next == NULL) { // for last element
            previousMovieNode->next = NULL;
            delete currentMovieNode;
            deleted = true;
          }
          else { // for all other elements to be deleted
            previousMovieNode->next = currentMovieNode->next;
            delete currentMovieNode;
            deleted = true;
          }
        }
        previousMovieNode = currentMovieNode;
        currentMovieNode = currentMovieNode->next;
      }
    }
    if(currTree->head == NULL) { // if LL is empty after deletion, also delete TreeNode for that titleChar
      root = Delete(root,currTree->titleChar);
    }
    currTree = currTree->rightChild; // now visit righ subtree
  }
  if(!deleted) { // if movie is not found
    cout << "Movie: " << title << " not found, cannot delete." << endl;
  }
}