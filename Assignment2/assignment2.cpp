#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct wordItem{
    string word = "";
    int count = 0;
};
void getStopWords(const char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length);
void arraySort(wordItem uniqueWords[], int length);
void printNext10(wordItem uniqueWords[], int N, int totalNumWords);
void resize(wordItem *&arrayPtr, int &capacity);
void getUniqueWords(const char *filename,string ignoreArr[], wordItem *&arrPtr, int &capacity, int &currentIndex, int &resizeCount);

int main(int argc,char *argv[]){
    if(argc != 4){
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return -1;
    }
    int N = stoi(argv[1]);

    string ignoreWords[50];
    getStopWords(argv[3],ignoreWords);

    int arrCapacity = 100;
    int length = 0;
    wordItem *arrPtr = new wordItem[arrCapacity];
    int resizeCount = 0;
    getUniqueWords(argv[2],ignoreWords,arrPtr,arrCapacity,length,resizeCount);
    arraySort(arrPtr,length);
    cout << "Array doubled: " << resizeCount << "\n#" << endl;
    int totalWords = getTotalNumberNonStopWords(arrPtr,length);
    cout << "Unique non-common words: " << length << "\n#" << endl;
    cout << "Total non-common words: " << totalWords << "\n#" << endl;
    cout << "Probability of next 10 words from rank " << N << "\n---------------------------------------" << endl;
    printNext10(arrPtr,N,totalWords);

    /*for(int i = 0; i < length; i++){
        cout << "word: " << arrPtr[i].word << " count: " << arrPtr[i].count << endl;
    }*/
    return 0;
}

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]){
    ifstream ws(ignoreWordFileName);
    if(ws.is_open()){
        string line;
        int index = 0;
        while(getline(ws,line)){
            ignoreWords[index] = line;
            index++;
        }
        ws.close();
    }
    else
        cout << "Failed to open " << ignoreWordFileName << endl;
}

bool isStopWord(string word, string ignoreWords[]){
    for(int i = 0; i < 50; i++){
        if(word == ignoreWords[i]){
            return true;
        }
    }
    return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length){
    int sum = 0;
    for(int i = 0; i < length;i++){
        sum += uniqueWords[i].count;
    }
    return sum;
}

void arraySort(wordItem uniqueWords[], int length){
    string tempStr;
    int tempInt;
    for(int i = 0; i < length; i++){		
		for(int j = i + 1; j < length; j++){
			if(uniqueWords[i].count < uniqueWords[j].count){
				tempStr = uniqueWords[i].word;
                tempInt = uniqueWords[i].count;
				uniqueWords[i].word = uniqueWords[j].word;
                uniqueWords[i].count = uniqueWords[j].count;
				uniqueWords[j].word = tempStr;
                uniqueWords[j].count = tempInt;
			}
		}
	}
}

void printNext10(wordItem uniqueWords[], int N, int totalNumWords){
    for(int i = N; i < N + 10; i++){
        cout << fixed << setprecision(4) << (float) uniqueWords[i].count / totalNumWords << " - " << uniqueWords[i].word << endl;
    }
}

void resize(wordItem *&arrayPtr, int &capacity){
	// increase the capacity by two times
	int newCapacity = capacity * 2;
  	//cout << "Resizing from " << capacity << " to " << newCapacity << endl;
	// dynamically allocate an array of size newCapacity
	wordItem *newArray = new wordItem[newCapacity];
	for(int i = 0; i < capacity;i++){ // copy all data from oldArray to newArray
		newArray[i] = arrayPtr[i];
	}
    // clear old array memory
	delete [] arrayPtr;
	arrayPtr = newArray;
	capacity = newCapacity;
}

void getUniqueWords(const char *filename,string ignoreArr[], wordItem *&arrPtr, int &capacity, int &currentIndex, int &resizeCount){
    ifstream fs(filename);
    if(fs.is_open()){
        string line;
        while(getline(fs,line)){
            string word;
            stringstream ws(line);
            bool alreadyExists = false;
            while(getline(ws,word,' ')){
                if(currentIndex == capacity - 1){ // check if the array is full
                    resize(arrPtr,capacity); // if full, double the array
                    resizeCount++;
                }
                bool stop = isStopWord(word, ignoreArr); // check to see if the word should be ignored
                if(stop == false){ // if word should not be ignored
                    for(int i = 0; i < currentIndex;i++){ // check to see if the word is already in the array
                        if(word == arrPtr[i].word){
                            alreadyExists = true;
                            arrPtr[i].count++; // increase count of word
                        }
                    }
                    if(alreadyExists == false){
                        arrPtr[currentIndex].word = word;
                        arrPtr[currentIndex].count++;
                        currentIndex++;
                    }
                    alreadyExists = false;
                }
            }
        }
        fs.close(); // close the file stream
    }
    else
        cout << filename << " could not be opened." << endl;
}