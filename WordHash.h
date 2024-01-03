 /*
 *  WordHash.h
 *  Tygan Chin tchin02 Emily Ye eye02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Interface for WordHash class. Declares the funcitons that insert 
 *  words and their instances into the index and  prints out a word in the 
 *  index.
 *
 */

#ifndef _WORDHASH_H_
#define _WORDHASH_H_

#include "Word.h"
#include <string>
#include <list>
#include <fstream>

using namespace std;

class WordHash
{
public:

    //constructor and destructor
    WordHash();
    ~WordHash();

    //setter
    void insert(string &word, string &file, int &line);

    //getter
    void print(FileHash &fIndex, string &userW, bool sens, ofstream &out);

private:

    int tableSize;
    int numWords;
    Word **hashTable;

    //helper funcs
    void deleteList(Word *curr);
    int listLength(Word *curr);
    Word *getLast(Word *curr);
    void expand();
    void insert(Word *copyWord, Word *table[]);
    string makeLower(string &userWord);

    //test functions
    // void print();
    // void printChainNode(Word *curr);
    // Word *getWord(string &userW);
};

#endif