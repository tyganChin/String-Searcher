/*
 *  Word.h
 *  Tygan Chin tchin02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Interface for Word class. Declares the funcitons that insert 
 *  instances of words into the object, prints the word, etc. 
 *
 */

#ifndef _WORD_H_
#define _WORD_H_

#include "fileHash.h"
#include <string>
#include <list>

using namespace std;

class Word
{
public:

    //constructor
    Word(string &word, string &file, int &line);
    
    //setters
    void setNext(Word *nextWord);
    bool insert(string &newWord, string &file, int &line);

    //getters
    bool isWord(string &newWord);
    Word *getNext();
    string getWord();
    void printAll(FileHash &fileIndex, ofstream &out);
    void printExact(FileHash &fileIndex, string &exact, ofstream &out);

private:

    struct instance
    {
        string fileName;
        int lineNum;
    };

    struct exactWord
    {
        string word;
        list<instance> instances;
    };

    string word;
    list<exactWord> exactWords;
    list<instance> totalInstances;
    Word *next;

    //helper funcs
    void setExactWord(exactWord &exact, string &Word, string &file, int &line);
    void setInstance(instance &newInstance, string &file, int &line);
    void addInstanceAll(instance &newInstance);
    void addInstanceExact(list<exactWord>::iterator exact, instance &newInst);
    void addInstanceExact(exactWord &exact, instance &newInstance);
    void printLine(string &path, string &file, int &lineNum, ofstream &out);

    //test function
    // void printWord();
};

#endif
