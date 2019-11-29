#include <iostream>
#include "ProducerConsumer.hpp"

using namespace std;

ProducerConsumer::ProducerConsumer() {
    queueFront = queueEnd = 0;
}

bool ProducerConsumer::isEmpty() {
    if(counter == 0)
        return true;
    return false;
}

bool ProducerConsumer::isFull() {
    if(counter == SIZE)
        return true;
    return false;
}

void ProducerConsumer::enqueue(string item) {
    if(isFull()) {
        cout << "Queue full, cannot add new item" << endl;
        return;
    }
    else {
        queue[queueEnd] = item;
        if(queueEnd == SIZE - 1)
            queueEnd = 0;
        else
            queueEnd++;
        counter++;
    }
}

void ProducerConsumer::dequeue() {
    if(isEmpty()) {
        cout << "Queue empty, cannot dequeue an item" << endl;
        return;
    }
    else {
        queue[queueFront] = "";
        if(queueFront == SIZE - 1)
            queueFront = 0;
        else
            queueFront++;
        counter--;
    }
}

int ProducerConsumer::queueSize() {
    return counter;
}

string ProducerConsumer::peek() {
    if(isEmpty()) {
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }
    return queue[queueFront];
}