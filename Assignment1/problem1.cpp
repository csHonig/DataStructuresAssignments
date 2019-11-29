#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int insertIntoSortedArray(int myArray[], int numEntries, int newValue);
void sortArray(int inArray);
void printArray(int inArray[], int inEntries);

int main(int argc,char *argv[]){
    int arr[100] = {};
    int entries = 0;
    ifstream fs(argv[1]);
    if(fs.is_open()){
        string temp;
        while(getline(fs,temp)){
            entries = insertIntoSortedArray(arr,entries,stoi(temp));
            printArray(arr,entries);
        }
    }
    else
        cout << "Failed to open the file." << endl;
}

int insertIntoSortedArray(int myArray[], int numEntries, int newValue){
    int newEntries = numEntries;
    myArray[numEntries] = newValue;
    int i,j,temp;
    for(i = 0;i < numEntries; i++)
	{		
		for(j = i + 1;j <= numEntries;j++)
		{
			if(myArray[i] >= myArray[j])
			{
				temp = myArray[i];
				myArray[i] = myArray[j];
				myArray[j] = temp;
			}
		}
	}
    newEntries++;
    return newEntries;
}

void printArray(int inArray[], int inEntries){
    for(int i = 0; i < inEntries;i++){
        if(i == inEntries - 1)
            cout << inArray[i];
        else   
            cout << inArray[i] << ",";
    }
    cout << endl;
}