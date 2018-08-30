/**********************************************************************
 * Ex4.cpp - CSCI205 - Ex4 - Binary Search Tree
 * Arvy Salazar - ags531 - 20/Aug/18
 **********************************************************************/
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<iomanip>

using namespace std;

//Global Variabls
int bst[5000];
int lineCnt = 1;

//Functions
void insert(int value, int pos);
void inPost(int pos);

int main(){
    char FileName[20];

    cout << "Enter file name: ";
    cin >> FileName;
    ifstream fin;
    fin.open(FileName);
    if (!fin.good()){
        cout << "Unable to open file" << endl;
        exit(1);
    }    
    int value;
    int rootPos = 1;
    fin >> value;
    while(!fin.eof()){
        insert(value, rootPos);
        fin >> value;
    }
    inPost(rootPos);  
    return 0;
}

//Inserts value
void insert(int value, int pos){
    int nextPos = 0; // -1 means that the value has reached its correct position
    if (value < bst[pos] && bst[pos] != 0){
        nextPos = 2*pos;
    } else if (value > bst[pos] && bst[pos] != 0){
        nextPos = 2*pos+1;
    }
    
    if (nextPos == 0){ 
        bst[pos] = value;
    } else {
        insert(value, nextPos);
    }
    return;
} 

//Prints tree using in order transversal
void inPost(int pos){
    if(bst[pos] == 0){
        return;
    }
    
    inPost(2*pos);
    
    cout << setw(5) << bst[pos];
    
    if (lineCnt % 5 == 0){
        cout << endl;
    }
    lineCnt++;
    
    inPost(2*pos+1);

    return;
}