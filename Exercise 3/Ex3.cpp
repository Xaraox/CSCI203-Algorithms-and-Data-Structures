/**********************************************************************
 * Ex2.cpp - CSCI205 - Ex3 - Virtual Initialization
 * Arvy Salazar - ags531 - 07/Aug/18
 **********************************************************************/
#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;

//Global Variables
int data[100];
int forward[100];
int backward[100];

int main(){
    int where, what, validCount = 0;
    char FileName[20];
    int probe;

    cout << "Enter Filename: ";
    cin >> FileName;
    
    ifstream fin;
    fin.open(FileName);
    if (!fin.good()){
        cout << "Unable to open file";
        exit(1);
    }

    //Data storage
    fin >> what;
    fin >> where;
    while(where != -1 && what != -1){  
        data[where] = what;
        forward[validCount] = where;
        backward[where] = validCount;
        fin >> what;
        fin >> where;
        validCount++;
    }

    fin >> probe;
    while(probe != -1){
        cout << "Position " << probe << " ";
        //Checks if valid data
        if(backward[probe]>0 && backward[probe]<=validCount && forward[backward[probe]] == probe){
            cout << "has been initialised to value " << data[probe];  
        } else {
            cout << "has not been intialised";
        }
        cout << endl;
        fin >> probe;
    }
    fin.close();
    return 0;
}