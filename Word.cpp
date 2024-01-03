 /*
 *  Word.cpp
 *  Tygan Chin tchin02 Emily Ye eye02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Implementation for Word class. Implements the funcitons that 
 *  insert instances of words into the object, prints the word, etc.
 *
 */

#include "Word.h"
#include "fileHash.h"
#include <iostream>
#include <fstream>
#include <cstring>

/*
 * name: Word
 * purpose: Set the member variables for a word object
 * arguments: The case-inscensitive word, original word, file name, line number
 * returns: n/a
 */
Word::Word(string &userWord, string &file, int &line)
{
    //set member variables
    word = userWord;
    next = nullptr;

    //Create new exact Word and add it to the list of exact words
    exactWord newExactWord;
    setExactWord(newExactWord, userWord, file, line);
}

/*
 * name: setExactWord
 * purpose: Set the member variables of an exactWord instance
 * arguments: The adress of the exactWord struct, exact word, file name, line
 * returns: n/a
 */
void Word::setExactWord(exactWord &exact, string &Word, string &file, int &line)
{
    //set exact word member variable for exactWord struct
    exact.word = Word;

    //set the new instance of that word and add it to the set of intances
    instance newInstance;
    setInstance(newInstance, file, line);

    //add instance to exact word list and Word list
    addInstanceAll(newInstance);
    addInstanceExact(exact, newInstance);

    //add exact word to list of exact words
    exactWords.push_back(exact);
}

/*
 * name: setInstance
 * purpose: Set the member variables of a given instance
 * arguments: The adress to the new instance and the file and line names
 * returns: n/a
 */
void Word::setInstance(instance &newInstance, string &file, int &line)
{
    //set instance memeber variables
    newInstance.fileName = file;
    newInstance.lineNum = line;
}

/*
 * name: addInstanceAll
 * purpose: Add/don't add a given instance to list of overall instances
 * arguments: The new instance
 * returns: n/a
 * effects: Adds instance if it's not on same line and file as other instances
 */
void Word::addInstanceAll(instance &newInstance)
{
    //add instance if total instances is empty
    if (totalInstances.empty())
    {
        totalInstances.push_back(newInstance);
        return;
    }

    //if the filename and line number are the same don't add
    if (totalInstances.back().fileName == newInstance.fileName)
        if (totalInstances.back().lineNum == newInstance.lineNum)
            return;
    
    //if different then add the instance
    totalInstances.push_back(newInstance);
}

/*
 * name: addInstanceExact
 * purpose: Adds/Doesn't add an instance of an exact word to list
 * arguments: An iterator of the exact word and the new instance
 * returns: n/a
 * effects: Adds instance if it isn't a duplicate, does nothing otherwise.
 */
void Word::addInstanceExact(list<exactWord>::iterator exact, instance &newInst)
{
    //if no other instances, add instance to list
    if (exact->instances.empty())
    {
        exact->instances.push_back(newInst);
        return;
    }

    //if the filename and line number are the same then return
    if (exact->instances.back().fileName == newInst.fileName)
        if (exact->instances.back().lineNum == newInst.lineNum)
            return;
    
    //add instnace to list of exactWord instances
    exact->instances.push_back(newInst);

}

/*
 * name: addInstanceExact
 * purpose: Adds/Doesn't add an instance of an exact word to list
 * arguments: The address to an exactWord and the new instance
 * returns: n/a
 * effects: Adds instance if it isn't a duplicate, does nothing otherwise.
 */
void Word::addInstanceExact(exactWord &exact, instance &newInstance)
{
    //if no other instances, add instance to list
    if (exact.instances.empty())
    {
        exact.instances.push_back(newInstance);
        return;
    }

    //if the filename and line number are the same then return
    if (exact.instances.back().fileName == newInstance.fileName)
        if (exact.instances.back().lineNum == newInstance.lineNum)
            return;
    
    //add instnace to list of exactWord instances
    exact.instances.push_back(newInstance);
}

/*
 * name: setNext
 * purpose: Allows user to set varable that stores the next word in list
 * arguments: A word instance that the next pointer should be set to
 * returns: n/a 
 */
void Word::setNext(Word *nextWord)
{
    next = nextWord;
}

/*
 * name: isWord
 * purpose: Get the case-insensitive word stored in the Word object
 * arguments: n/a
 * returns: The case-insensitive word
 */
bool Word::isWord(string &newWord)
{
    //check if the lengths of the words differ
    if (word.length() != newWord.length())
        return false;

    //compare the lowercase version of each character in the words
    int size = word.length();
    for (int i = 0; i < size; ++i)
    {
        if (tolower(word[i]) != tolower(newWord[i]))
            return false;
    }

    //return true if all the letters are the same
    return true;
}

/*
 * name: getNext 
 * purpose: Get the Word instance this Word points to 
 * arguments: n/a
 * returns: The pointer to the next word instance
 */
Word *Word::getNext()
{
    return next;
}

/*
 * name: getWord 
 * purpose: Get the word that the word object represents
 * arguments: n/a
 * returns: The word
 */
string Word::getWord()
{
    return word;
}

 /*
 * name: printAll
 * purpose: Print out all of the total instances of the Word object
 * arguments: A filehash to help print out the pathway and line
 * returns: n/a
 */
 void Word::printAll(FileHash &fileIndex, ofstream &out)
 {
    //iterate through the total instances and print each of them out
    list<instance>::iterator i = totalInstances.begin();
    while (i != totalInstances.end())
    {
        string path = fileIndex.print(i->fileName, i->lineNum, out);
        printLine(path, i->fileName, i->lineNum, out);
        ++i;
    }
 }

/*
 * name: printExact
 * purpose: Print out all of the instaces of an exaxt word in the Word object
 * arguments: A filehash to help print and the exact word
 * returns: n/a
 */
 void Word::printExact(FileHash &fileIndex, string &exact, ofstream &out)
 {
    //find the correct exact word in the Word object
    list<exactWord>::iterator i = exactWords.begin();
    while (i != exactWords.end())
    {
        if (i->word == exact)
        {
            //iterate through its instances and print each of them out
            list<instance>::iterator j = i->instances.begin();
            while (j != i->instances.end())
            {
                string path = fileIndex.print(j->fileName, j->lineNum, out);
                printLine(path, j->fileName, j->lineNum, out);
                ++j;
            }
            return;
        }
        ++i;
    }     

    //print message if exact word not found
    out << exact << " Not Found." << endl;
 }

 /*
 * name: printLine
 * purpose: Prints the given line in the given file
 * arguments: A file name and a line number
 * returns: n/a
 */
void Word::printLine(string &path, string &file, int &lineNum, ofstream &out)
{   
    //open stream and make sure file is open
    ifstream wordFile(path + file);
    if (not wordFile.is_open())
    {
        cerr << "Unable to open file" << endl;
        return;
    }

    //read in previous lines
    string line;
    for (int i = 0; i < lineNum; ++i)
        getline(wordFile, line);

    //print out the line in the file
    out << line << endl;
}

/*
 * name: insert 
 * purpose: Insert a new exactWord or exactWord instance if possible
 * arguments: The word to insert, the exact word, file name, line number
 * returns: True if insertion was made, false otherwise
 */
bool Word::insert(string &newWord, string &file, int &line)
{
    //Return false if case-insensitive words are not identical
    if (not isWord(newWord))
        return false;

    //Check if exactWord already exists in list, insert new instance if so
    list<exactWord>::iterator i = exactWords.begin();
    while (i != exactWords.end())
    {
        //add new instance to list if exactWord is the same
        if (i->word == newWord)
        {
            instance newInstance;
            setInstance(newInstance, file, line);
            addInstanceExact(i, newInstance);
            addInstanceAll(newInstance);
            return true;
        }
        ++i;        
    }

    //initialize new exactWord and add it to back of list of exact words
    exactWord newExactWord;
    setExactWord(newExactWord, newWord, file, line);

    return true;
}

//test print function
// void Word::printWord()
// {
//     cout << "WORD: " << word << endl;

//     list<exactWord>::iterator i = exactWords.begin();
//     while (i != exactWords.end())
//     {
//         cout << "EXACTWORD: " << i->word << endl;
//         cout << "INSTANCES: ";
//         list<instance>::iterator j = i->instances.begin();
//         while (j != i->instances.end())
//         {
//             cout << j->fileName << "-" << j->lineNum << " ";
//             ++j;
//         }
//         cout << endl;
//         ++i;        
//     }

//     list<instance>::iterator j = totalInstances.begin();
//     cout << "TOTAL INSTANCES: ";
//     while (j != totalInstances.end())
//     {
//         cout << j->fileName << "-" << j->lineNum << " ";
//         ++j; 
//     }
//     cout << endl;
// }