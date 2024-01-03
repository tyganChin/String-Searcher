/*
 *  WordHash.cpp
 *  Tygan Chin tchin02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Implementation for WordHash class. Implements the funcitons that
 *  insert words and their instances into the index and  prints out a word in 
 *  the index.
 *
 */

#include "WordHash.h"
#include "Word.h"
#include <functional>
#include <iostream>


/*
 * name: wordHash
 * purpose: Initilize a wordHash instance
 * arguments: n/a
 * returns: n/a
 */
WordHash::WordHash()
{
    //set member variables
    tableSize = 50;
    numWords = 0;

    //create new table of instance pointers
    hashTable = new Word *[tableSize];

    //initilize all of the entries to nullptr
    for (int i = 0; i < tableSize; i++) 
        hashTable[i] = nullptr;
}

/*
 * name: ~WordHash
 * purpose: Delete the memory of the word hash
 * arguments: n/a
 * returns: n/a
 */
WordHash::~WordHash()
{
    //delete each Word list in the table
    for (int i = 0; i < tableSize; ++i)
        deleteList(hashTable[i]);
    
    //delete the table itself
    delete [] hashTable;
}

/*
 * name: deleteList
 * purpose: Deletes the given list of Word objects at a single table spot
 * arguments: The current Word object in the list
 * returns: n/a
 */
void WordHash::deleteList(Word *curr)
{
    //if node is the nullptr return
    if (curr == nullptr)
        return;

    //delete list starting at next word in the list
    deleteList(curr->getNext());

    //delete current word
    delete curr;
}

/*
 * name: insert
 * purpose: Add a new Word/exact word and instance to the hash
 * arguments: Case-insens word, case-sens word, filename, line number
 * returns: n/a
 */
void WordHash::insert(string &word, string &file, int &line)
{
    //assign hash value
    size_t slot = hash<string>{}(makeLower(word)) % tableSize;

    //add the the instance of the word to the Word object if it exists
    Word *curr = hashTable[slot];
    while (curr != nullptr)
    {
        if (curr->insert(word, file, line))
            return; 
        curr = curr->getNext();       
    }

    //if word doesn't exist already, declare a new one and add it to slot
    Word *newWord = new Word(word, file, line);
    if (listLength(hashTable[slot]) == 0)
        hashTable[slot] = newWord;
    else
        getLast(hashTable[slot])->setNext(newWord);

    //increment size and expand if necesary
    numWords++;
    expand();
}

/*
 * name: getWord
 * purpose: Gets the Word object using the given word
 * arguments: A word
 * returns: Word object corresponding to given word, nullptr if nonexistent
 */
void WordHash::print(FileHash &fIndex, string &userW, bool sens, ofstream &out)
{
    //assign hash value
    size_t slot = hash<string>{}(makeLower(userW)) % tableSize;

    //loop through hash bucket and return Word if it exists
    Word *curr = hashTable[slot];
    while (curr != nullptr)
    {
        if ((curr->isWord(userW)) and (not sens))
        {
            curr->printAll(fIndex, out);
            return;            
        }
        else if ((curr->isWord(userW)) and (sens))
        {
            curr->printExact(fIndex, userW, out);
            return;
        }
        curr = curr->getNext();
    }

    //error message if word is not found
    out << userW << " Not Found. Try with @insensitive or @i." << endl;
}

/*
 * name: listLength
 * purpose: Gets the length of given table's bucket 
 * arguments: The current word in the bucket's list
 * returns: The amount of Word objects in bucket
 */
int WordHash::listLength(Word *curr)
{
    //check if nullptr, add 0 to length if so
    if (curr == nullptr)
        return 0;

    //return 1 plus the length of the rest of the list
    return 1 + listLength(curr->getNext());
}

/*
 * name: getLast
 * purpose: Get the last Word in a given table bucket
 * arguments: The current Word in the bucket
 * returns: A pointer to the last word in the bucket
 */
Word *WordHash::getLast(Word *curr)
{
    //return the current node if it's next node is nullptr
    if (curr->getNext() == nullptr)
        return curr;

    //check for the last node using the next node
    return getLast(curr->getNext());
}

/*
 * name: expand
 * purpose: Increase the size of the table if too many Words
 * arguments: n/a
 * returns: n/a
 * effects: The size of the table is doubled
 */
void WordHash::expand()
{
    //check if expansion is needed
    if ((float(numWords) / float(tableSize)) < 0.7)
        return;

    //declare a new hash table with the updated size and initilize it
    tableSize += tableSize;
    Word **newTable = new Word *[tableSize];
    for (int i = 0; i < tableSize; i++) 
        newTable[i] = nullptr;

    //rehash the words into the new table
    for (int i = 0; i < tableSize / 2; ++i)
    {
        Word *curr = hashTable[i];
        while (curr != nullptr)
        {
            insert(curr, newTable);
            Word *temp = curr->getNext();
            curr->setNext(nullptr);
            curr = temp;
        }
    }

    //delete old table and assing new one to variable
    delete [] hashTable;
    hashTable = newTable;
} 

/*
 * name: insert
 * purpose: Rehash the given word and insert it into the new table
 * arguments: The word to be rehashed and the newTable
 * returns: n/a
 */
void WordHash::insert(Word *copyWord, Word *table[])
{
    //assign hash value
    string word = copyWord->getWord();
    size_t slot = hash<string>{}(makeLower(word)) % tableSize;
   
    //get the length of the list of Chained nodes at the given hash value
    int numItems = listLength(table[slot]);

    //Add it to the specified slot
    if (numItems == 0)
        table[slot] = copyWord;
    else
        getLast(table[slot])->setNext(copyWord);
}

/*
 * name: makeLower
 * purpose: Return a copy of the given string as all lowercase
 * arguments: The word to make lowercase
 * returns: The lowercase string
 */
string WordHash::makeLower(string &userWord)
{
    //initilize lowercase string
    string lowerCase = "";

    //add the lowercase version of each word to the back of the new string
    int wordLength = userWord.length();
    for (int i = 0; i < wordLength; ++i)
        lowerCase += tolower(userWord[i]);

    return lowerCase;
}


//TEST FUNCTIONS;

// void WordHash::printChainNode(Word *curr)
// {
//     cout << "key:  " << curr->word;
//     cout <<  "; exactWords:  " << curr->exactWords.size() << " ";
//     cout << "; instances: " << curr->totalInstances.size() << " ";
// }

// /*
//  * Print both hash tables
//  * Could break this up into two print functions
//  */
// void WordHash::print()
// {
//         cout << "Chained table" << endl;
        
//         for (int i = 0; i < tableSize; ++i) {
//                 Word *curr = hashTable[i];
//                  cout << i << ":  [ ";   
//                 while (curr != NULL) {
//                         printChainNode(curr);
//                         curr = curr->next;
//                         if (curr != NULL)
//                                 cout << ", ";
//                 }
//             cout << "]" << endl;
//         }
//         cout << endl;
// }

// /*
//  * name: getWord
//  * purpose: Gets the Word object using the given word
//  * arguments: A word
//  * returns: Word object corresponding to given word, nullptr if nonexistent
//  */
// Word *WordHash::getWord(string &userW)
// {
//     //assign hash value
//     size_t slot = hash<string>{}(userW) % tableSize;

//     //loop through hash bucket and return Word if it exists
//     Word *curr = hashTable[slot];
//     while (curr != nullptr)
//     {
//         if (curr->isWord(userW))
//         {
//             return curr;
//         }
//     }

//     return nullptr;
// }
