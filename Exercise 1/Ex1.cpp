#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;

//Global Variables
string  WordStack[9];
int topPos = -1;

void push(char word[]);
string top();
void pop();
bool isEmpty();

int main(){
    char Filename[20];
    char word[20];

    cout << "Enter FileName: ";
    cin >> Filename;

    ifstream fin;
    fin.open(Filename);

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
    return 0;
}

//puts a word on top of stack
void push(char word[]){
    topPos++;
    WordStack[topPos] = word;
}

//returns the word on top of stack
string top(){
    return  WordStack[topPos];
}

//removes the word on top of stack
void pop(){
    WordStack[topPos] = "";
    topPos--;
}

//checks if stack is empty
bool isEmpty(){
    if(topPos < 0){
        return true;
    }
    return false;
}