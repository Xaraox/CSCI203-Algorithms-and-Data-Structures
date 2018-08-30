/**********************************************************************
 * Ass1.cpp - CSCI205 - Ass1 -  Assignment 1
 * Arvy Salazar - ags531 - 25/Aug/18
 **********************************************************************/
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

//Struct used to stores position, length of word in word pool, frequency of word and pointers to left and right nodes 
struct Word{
    int start, length;
    int count;
    struct Word *left;
    struct Word *right;
};

//Global Vatiables
Word words[1000000]; //Word struct that has the words organisied alphabetically
char pool[1000000]; //Stores the unique words read from file
int wordsRead =0; //Number of unique words read
int NumWords = 0; //Number of words
int NumLetters = 0; //Number of letters
int lineCnt =1;

//Global Functions
void getWord(Word word, char* copyTo); //gets word from word pool
void processWord(char *word); //processes word to remove punctuation
void add(char *word); //adds the word to the word pool
struct Word* insert(Word * currPos, Word * nextPos); //puts the word into the BST
void descOrder(Word *word); // Print words in descending order
void  ascOrder(Word *word); // Print words in ascending order

int main(){
    char word[20];
    char Filename[20]; 
    fstream fin;
    Word * root = NULL;
    //Get filename from user
    cout << "Enter file name: ";
    cin >> Filename;
    fin.open(Filename);
    if (!fin.good()){
        cout << "Unable to open file";
        exit(1);
    }
    //Reads the file word by word adding it to the word pool;
    while(!fin.eof()){
        fin >> word;
        processWord(word);
        add(word);
        wordsRead++;
    }
    fin.close();
    
    //Insert words into BST
    for(int i = 0; i <= NumWords-1; i++){
        char tmp[20];
        getWord(words[i], tmp);
        root = insert(&words[i], root);
    }
    //Print word stats
    cout<< "Words Read: " << wordsRead << endl
        << "Unique Words: " << NumWords-1 << endl
        <<"Displaying Top 10 words" << endl
        << "--------------------+--------------------+" <<endl
        << setw(20)<< "WORD"<< "|" << setw(20) <<"COUNT"<< "|" << endl
        << "--------------------+--------------------+" <<endl;
    descOrder(root);
    cout << "--------------------+--------------------+" <<endl;
    lineCnt = 1;
    cout<<"Displaying Bottom 10 words" << endl
        << "+--------------------+--------------------+" <<endl
        << setw(20)<< "WORD"<< "|" << setw(20) <<"COUNT"<< "|" << endl
        << "+--------------------+--------------------+" <<endl;
    ascOrder(root);
    cout << "+--------------------+--------------------+" <<endl;
    return 0;
}

void getWord(Word word, char* copyTo){
    //empty char
    memset(copyTo, 0, 20); 
    //copy word from word pool to copyTo
    for(int i = 0; i<word.length; i++) 
        copyTo[i] = pool[word.start+i];
}

void processWord(char *word){
    //goes through char and only copying alphabets then returning it;
    char processedWord[20] = { 0 };
    for(int i=0; i != strlen(word); i++){
        if(isalpha(word[i])){
            processedWord[strlen(processedWord)] = tolower(word[i]);
        }
    }
    strcpy(word, processedWord);
    return;
}

void add(char *word){

    //Binary Search for word
    int start = 0;
    int end = NumWords;
    int mid;
    char cmp[20];
    if(NumLetters != 0){
        do{ 
            mid = (start+end)/2;
            getWord(words[mid], cmp);
            if (strcmp(word,cmp) == 0){ 
                words[mid].count ++;
                return;
            }
            else if (strcmp(word, cmp) < 0) end = mid-1; 
            else if (strcmp(word, cmp) > 0) start = mid+1;
        
        }while(start-end <= 0); 
    }
    //===========If word does not exist==========//
    //Add word 
    strcat(pool, word);
    words[NumWords].start = NumLetters;
    words[NumWords].length = strlen(word);
    words[NumWords].count++;
    words[NumWords].left = NULL;
    words[NumWords].right = NULL;
    NumLetters += strlen(word);
    //Insertion to correct pos
    char currWord[20];
    char nextWord[20];
    int currPos = NumWords;
    Word tmp;
    if (currPos != 0){
        getWord(words[currPos], currWord);
        getWord(words[currPos-1], nextWord);
        while(currPos > 0 && strcmp(word, nextWord) <= 0){
            tmp  = words[currPos];
            words[currPos] = words[currPos-1];
            words[currPos-1] = tmp; 
            currPos--;
            if (currPos != 0){
            getWord(words[currPos], currWord);
            getWord(words[currPos-1], nextWord);
            }   
        }
    }
    NumWords++;
}

struct Word* insert(Word * currPos, Word * nextPos){
    char currWord[20];
    char nextWord[20];
    Word tmp;
    //BST insertion
    if(nextPos == NULL) return currPos;  
    if (currPos->count < nextPos->count )nextPos->left = insert(currPos, nextPos->left);
    else if (currPos->count > nextPos->count) nextPos->right = insert(currPos, nextPos->right);
    else if (currPos->count == nextPos->count){
        tmp.start = currPos->start;
        tmp.length = currPos->length;
        getWord(tmp, currWord);
        tmp.start = nextPos->start;
        tmp.length = nextPos->length;
        getWord(tmp, nextWord);
        if (strcmp(currWord, nextWord) > 0) nextPos->left = insert(currPos, nextPos->left);
        else if (strcmp(currWord, nextWord) < 0) nextPos->right = insert(currPos, nextPos->right);
    }
    return nextPos;
}

void descOrder(Word *word){
    if (word == NULL || lineCnt % 11 == 0) return;
    descOrder(word->right);
    if (word == NULL || lineCnt % 11 == 0) return;
    
    //Prints the word and count
    char tmp[20];
    Word tmpWord;
    tmpWord.start = word->start;
    tmpWord.length = word->length; 
    getWord(tmpWord, tmp);
    cout << setw(20)<< tmp <<"|"<< setw(20)<< word->count << "|"<< endl;
    if (word == NULL || lineCnt % 11 == 0) return;

    lineCnt++;
    descOrder(word->left);
    return;
}

void ascOrder(Word *word){
    if (word == NULL || lineCnt % 11 == 0) return;
    ascOrder(word->left);
    if (lineCnt % 11 == 0) return;
    
    //Prints the word and count
    char tmp[20];
    Word tmpWord;
    tmpWord.start = word->start;
    tmpWord.length = word->length; 
    getWord(tmpWord, tmp);
    cout << setw(20)<< tmp <<"|"<< setw(20)<< word->count << "|"<< endl;
    
    if (lineCnt % 11 == 0) return;
    lineCnt++;
    ascOrder(word->right);
    
    return;
}