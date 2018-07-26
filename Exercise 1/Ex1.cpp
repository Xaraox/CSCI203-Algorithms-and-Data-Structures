/**********************************************************************
 * Ex1.cpp - CSCI205 - Ex1 - Stack
 * Arvy Salazar - ags531 - 31/Jul/18
 **********************************************************************/
#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;

//Global Variables
const int wordStackSize = 9;
string  wordStack[wordStackSize];
int topPos = -1;

//Functions
void push(char word[]);
string top();
void pop();
bool isEmpty();

int main(){
    char FileName[20];
    char word[20];

    cout << "Enter FileName: ";
    cin >> FileName;

    ifstream fin;
    fin.open(FileName);

    if(!fin.good()){
        cout << "Unable to open file";
        exit(1);
    }
    
    do {
        fin >> word;
        if (fin.fail()) {
            break;
        }
        push(word);
    } while(!fin.eof());

     fin.close();
    while(!isEmpty()){
        cout << top() << " ";
        pop();
    }
    cout << endl;
    return 0;
}

//puts a word on top of stack
void push(char word[]){
    topPos++;
    wordStack[topPos] = word;
}

//returns the word on top of stack
string top(){
    return  wordStack[topPos];
}

//removes the word on top of stack
void pop(){
    wordStack[topPos] = "";
    topPos--;
}

//checks if stack is empty
bool isEmpty(){
    if(topPos < 0){
        return true;
    }
    return false;
}