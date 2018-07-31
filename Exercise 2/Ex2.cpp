/**********************************************************************
 * Ex2.cpp - CSCI205 - Ex2 - Heap
 * Arvy Salazar - ags531 - 31/Jul/18
 **********************************************************************/
#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;

//Global Variables
int heapArray[500];
int posLastInt = -1;

//Functions
void makeheap();
void siftUp(int i);
void swap(int i, int p);

int main(){
    char FileName[20];
    cout << "Enter Filename: ";
    cin >> FileName;

    ifstream fin;
    fin.open(FileName);

    if (!fin.good()){
        cout << "Unable to open file";
        exit(1);
    }

    while(!fin.eof()){
        posLastInt++;
        int temp;
        fin >> temp;
         heapArray[posLastInt] = temp;
    };

    fin.close();
    makeheap();
    for(int i = 0; i<5; i++){
        cout << heapArray[i] << " ";
    }

    return 0;
}

//goes through the array and siftsup each leaf node
void makeheap(){
 for (int i = 0; i < posLastInt; i++){
    siftUp(i);
 }  
}

//moves the lead node to its right position
void siftUp(int i){
    if (i == 0) return;
    int p = i / 2;
    if (heapArray[p] > heapArray[i]){
        return;
    } else {
        swap(i, p);
        siftUp(p);
    }
}

//swaps elements from position i to position p
void swap(int i, int p){
    int temp = heapArray[i];
    heapArray[i] = heapArray[p];
    heapArray[p] = temp;
}