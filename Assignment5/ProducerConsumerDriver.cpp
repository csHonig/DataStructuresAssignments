/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu() {
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[]) {
	ProducerConsumer myPC;
	string input,item;
	int num, i,queueSize;
	while(true) {
		menu();
		getline(cin,input);
		switch(stoi(input)){
			case 1: // Producer
				cout << "Enter the number of items to be produced:" << endl;
				getline(cin,input);
				num = stoi(input);
				for(int i = 0; i < num; i++) {
					cout << "Item" << i + 1 << ":" << endl;
					getline(cin,input);
					myPC.enqueue(input);
				}
				break;
			case 2:
				cout << "Enter the number of items to be consumed:" << endl;
				getline(cin,input);
				queueSize = myPC.queueSize();
				if(stoi(input) > myPC.queueSize()) {
					for(int i = 0; i < queueSize; i++) {
						item = myPC.peek();
						myPC.dequeue();
						cout << "Consumed: " << item << endl;
					}
					cout<< "No more items to consume from queue" << endl;
				}
				else {
					for(int i = 0; i < stoi(input);i++) {
						item = myPC.peek();
						myPC.dequeue();
						cout << "Consumed: " << item << endl;
					}
				}
				break;
			case 3:
				cout << "Number of items in the queue:" << myPC.queueSize() << endl;
				return 0;
				break;
		}
	}
	return 0;
}
