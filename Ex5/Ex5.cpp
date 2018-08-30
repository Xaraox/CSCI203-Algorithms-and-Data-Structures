#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;

struct Node {
    int key;
    Node * next;
};

int main (){
    char fileName[20];
    int key;
    Node * hashTable[100] = { NULL }; // Initialise structs key to -1 which means that the element is empty 
    int lastKey = 0;
    int LongestChain = 0;
    int numOfEmpty= 100;

    cout << "Enter filename: ";
    cin >> fileName;
    ifstream fin;
    fin.open(fileName);
    if (!fin.good()){
        cerr << "Unable to open file.";
        exit(1);
    }
    //Insert
    while(!fin.eof()){
        fin >> key;  
        int Hkey = key % 100;
        if(hashTable[Hkey] == NULL)  {
            numOfEmpty--;
            hashTable[Hkey] = new Node;
            hashTable[Hkey]->key = key;     
        } else {
            Node * tmp = hashTable[Hkey];//assign head of linked list to tmp
            int chainLen = 1;
            while(tmp->next != NULL){ //
                tmp = tmp->next;
                chainLen++;
            }
            if(LongestChain < chainLen) LongestChain = chainLen;
            tmp->next = new Node;
            tmp->next->key = key;
        }
    }

    cout << "Num Of empty entries in the hashtable is: " << numOfEmpty << endl;
    cout << "Longest chain in the dictionary is : "<< LongestChain << endl;
    
}

