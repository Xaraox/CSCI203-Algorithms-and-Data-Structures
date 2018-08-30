/**********************************************************************
 * ass1.cpp - CSCI205 - Ass1 - 
 * Arvy Salazar - ags531 - 11/Aug/18
 **********************************************************************/
/*
TO DO LIST: 
 - Implement AVL for sorting the words
*/
#include<fstream>
#include<iostream>
#include<string>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

//Structs
struct Word{
    //char word[20];
    int start, length;
    int count;
};

//Global Variables
Word words[50000];
char pool[5000000];
int NumWords = 0;
int NumLetters = 0;

//Functions
void processWord(char *word);
void add(char *word);
void getWord(Word word, char* copyTo);

int main(){
    char FileName[20];
    //Get filename and readfile
    cout << "Enter file name: ";
    cin >> FileName; 
    ifstream fin;
    fin.open(FileName);
    if (!fin.good()){
        cout << "Unable to open file";
        exit(1);
    }
    char word[20];
    //Process word
    while(!fin.eof()){
        fin >> word;
        processWord(word);
        add(word);
    }
    fin.close();
    // //Print word stats


    // for(int currWord = 0; currWord <= NumWords; currWord++) {
    //     char tmp[20];
    //     getWord(words[currWord], tmp);
    //     cout << tmp <<" "; 
    //    memset(tmp, 0, sizeof tmp);
    // }

    //for(int currWord = 0; currWord <= NumWords; currWord++) {  
    //     for(int currLetter=words[currWord].start; currLetter < words[currWord].end; currLetter++){
    //     cout << pool[words[currWord].start - words[currWord].end];
    //     }
    //  //   cout << endl;
    // }
    return 0;
}

void processWord(char *word){
    char processedWord[20] = { 0 };
    for(int i=0; i != strlen(word); i++){
        if(isalpha(word[i])){
            processedWord[strlen(processedWord)] = tolower(word[i]);
        }
    }
    strcpy(word, processedWord);
    return;
}


void getWord(Word word, char* copyTo){
    for(int i = 0; i<word.length; i++){
        copyTo[i] = pool[word.start+i];
    }
}

void add(char *word){
    //Binary Search if word exists
    int start = 0;
    int end = NumWords;
    int mid;
    char cmp[20];
    //int cmpCurrLetter = 0;

    if(NumLetters != 0){
        do{ 
            mid = (start+end)/2;
          //  cmpCurrLetter = 0;
         //   cout << mid << endl;
            // for(int currLetter =words[mid].start; currLetter < words[mid].end; currLetter++){
            //     cmp[cmpCurrLetter] = pool[currLetter];
            //     cmpCurrLetter++;
            // } 
            getWord(words[mid], cmp);
            //    cout << "strcmp("<< word << ", " << cmp << ") =" << strcmp(word, cmp) << endl;     
            if (strcmp(word,cmp) == 0){ 
                words[mid].count ++;
                return;
            } else if (strcmp(word, cmp) < 0){ 
                end = mid-1; 
            } else if (strcmp(word, cmp) > 0){
                start = mid+1;
            }
            memset(cmp, 0, sizeof cmp);
        }while(start-end <= 0); //(!start>end) does not work ?
    } //========================IF WORD DOES NOT EXIST==============================//
    //Create new word
    //strcpy(words[NumWords].word, word);
    strcat(pool, word);//add word to word pool;
    words[NumWords].start = NumLetters;
    words[NumWords].length = strlen(word);
    words[NumWords].count++;
    NumWords++;
    NumLetters += strlen(word);
    //Insert Sort to correct position
    char currWord[20];
    char nextWord[20];
    int currPos = NumWords;
    Word tmp;


    // for(int i=words[currPos].start; i != words[currPos].; i++){
    //   //  nextWord[strlen(nextWord)] = pool[i];
    //     cout << pool[i];
    // }
    //cout << endl;

    getWord(words[currPos], currWord);
    cout << currWord;
    getWord(words[currPos-1], nextWord);
    while(currPos > 0 && strcmp(word, nextWord) <= 0){
        tmp  = words[currPos];
        words[currPos] = words[currPos-1];
        words[currPos-1] = tmp; 
        currPos--;
        memset(currWord, 0, sizeof currWord);
        memset(nextWord, 0, sizeof nextWord);
        getWord(words[currPos], currWord);
        getWord(words[currPos-1], nextWord);   
    }

    // // for(int i=words[mid].start; i != words[mid].end; i++){
    //     cmp[strlen(cmp)] = pool[i];
    // }
    // while(i >= 0 && strcmp(words[i].word, words[i-1].word) <= 0){
    //     tmp  = words[i];
    //     words[i] = words[i-1];
    //     words[i-1] = tmp; 
    //     i--;
    // }
    // NumWords++;
}
