#include <iostream>
#include "RPNCalculator.hpp"

using namespace std;

RPNCalculator::RPNCalculator() {
    stackHead = NULL;
}

RPNCalculator::~RPNCalculator() {
    stackHead = NULL;
}

bool RPNCalculator::isEmpty() {
    if(stackHead == NULL)
        return true;
    return false;
}

void RPNCalculator::push(float num) {
    Operand* newNode = new Operand; // allocate space for new Operand node
    newNode->number = num; // set data for new node
    newNode->next = stackHead; // set next value for node to be the stack head
    stackHead = newNode; // change stack head to be the new node 
}

void RPNCalculator::pop() {
    if(stackHead == NULL) {
        cout << "Stack empty, cannot pop an item." << endl;
    }
    else {
        Operand* temp = stackHead;
        stackHead = stackHead->next;
        delete temp; // delete the old stack head
    }
}

Operand* RPNCalculator::peek() {
    if(stackHead == NULL) {
        cout << "Stack empty, cannot peek." << endl;
        return NULL;
    }
    
    return stackHead;
}

bool RPNCalculator::compute(string symb) {
    if(isEmpty() == true) { // if stackHead is empty
        cout << "err: not enough operands" << endl;
        return false;
    }
    if(symb != "+" && symb != "*") {
        cout << "err: invalid operation" << endl;
        return false;
    }
    
    float first = stackHead->number; // value of first node
    pop(); // pop first node
    if(isEmpty() == true) { // if second value does not exist
        cout << "err: not enough operands" << endl;
        push(first);
        return false;
    }
    float second = stackHead->number; // value of second node
    pop(); // pop second node
    if(symb == "+") {
        float sum = first + second;
        push(sum);
        return true;
    }
    else if (symb == "*") {
        float prod = first * second;
        push(prod);
        return true;
    }
}