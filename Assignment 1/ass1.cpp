/**********************************************************************
 * ass1.cpp - CSCI205 - Ass1 - 
 * Arvy Salazar - ags531 - 11/Aug/18
 **********************************************************************/
#include<fstream>
#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

//Global Variables
string words[100];
int wordCount[100];

int main(){
    char FileName[20];
    
    //Step 1 Read the name of file from the console.
    cout << "Enter file name: ";
    cin >> FileName; 
    ifstream fin;
    fin.open(FileName);
    if (!fin.good()){
        cout << "Unable to open file";
        exit(1);
    }
    
    // Step 2 Read the file line
    string line;
    getline(fin, line);

    string word;
    bool ok = false; // this boolean is used ot check if it is a word. It is a word if there is atleast 1 alphabet
    for(int i = 0; i != line.length()-1; i++){
        if (isalpha(line[i])){
            word += tolower(line[i]);
            ok = true;
        } else if(line[i] == '\'' || line[i] == '-') {// 
           // word += tolower(line[i]);
        } else{
            cout << word;
            ok == false;
            word.clear();
        } 
        //cout << line[i];
    }

    fin.close();

    return 0;
}