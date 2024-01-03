/*
 *  unit_tests.h
 *  Tygan Chin tchin02 
 *  4/15/2023
 *
 *  gerp
 *
 *  Purpose: Testing framework for the Word, WordHash, fileHash, and Gerp 
 *  classes. Tests a majority of the functionalites of the functions in those 
 *  classes. 
 *
 */

#include "Word.h"
#include "WordHash.h"
#include "fileHash.h"
#include "Gerp.h"
#include <cassert>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;


/********************************************************************\
*                               Word                                 *
\********************************************************************/


/*
// Word(string &userWord, string &ogWord, string &file, int &line)
*/

//tests if contructor accurelty sets up 
void contructor_test()
{
    //declare variables to pass into function
    string userWord = "glory";
    string file = "g.txt";
    int line = 65;

    //initialize the word instance
    Word testWord(userWord, file, line);

    //assert all members are accurate
    assert(testWord.word == "glory");
    assert(testWord.next == nullptr);
    assert(testWord.exactWords.front().word == "glory");
    assert(testWord.exactWords.front().instances.front().fileName == "g.txt");
    assert(testWord.exactWords.front().instances.front().lineNum == 65);
    assert(testWord.totalInstances.size() == 1);
    assert(testWord.totalInstances.front().lineNum == 65);
}

// tests the setExactWord and setInstance as those are crucial for the 
// contstructor to work

/*
// void setNext(Word &nextWord)
*/

//tests if the function sets the next var to the given word
void setNext_test()
{
    //declare variables to pass into function
    string userWord = "glory";
    string file = "glory.txt";
    int line = 65;

    //initialize the word instance
    Word testWord(userWord, file, line);
    Word testWord_2(userWord, file, line);

    //set the next pointer
    testWord.setNext(&testWord_2);
    testWord_2.setNext(&testWord);

    assert(testWord.next == &testWord_2);
    assert(testWord_2.next == &testWord);
}


/*
// bool insert(string &newWord, string &file, int &line)
*/

//tests insert when inserting a differnt case word on diff line of same file
void insert_test()
{
    //declare variables to pass into function
    string userWord = "Glory";
    string file = "glory.txt";
    int line = 65;

    //initialize word instance
    Word testWord(userWord, file, line);

    //insert same word but differnt case
    line = 87;
    userWord = "glory";
    assert(testWord.insert(userWord, file, line));
    assert(testWord.exactWords.size() == 2);
    assert(testWord.exactWords.back().word == "glory");
    assert(testWord.totalInstances.size() == 2);
}

//tests insert when same word and line/file are the same
void insertSameWord_test()
{
    //declare variables to pass into function
    string userWord = "Glory";
    string file = "glory.txt";
    int line = 65;

    //initialize word instance
    Word testWord(userWord, file, line);

    //insert same word but differnt case
    assert(testWord.insert(userWord, file, line));
    assert(testWord.exactWords.size() == 1);
    assert(testWord.totalInstances.size() == 1);
}

//test function when word is the same but file and line number differ
void insertSameWordDifferntLocation_test()
{
    //declare variables to pass into function
    string userWord = "Glory";
    string file = "glory.txt";
    int line = 65;

    //initialize word instance
    Word testWord(userWord, file, line);

    //insert same word but differnet file and line number
    file = "g.txt";
    line = 56;
    assert(testWord.insert(userWord, file, line));
    assert(testWord.exactWords.size() == 1);
    assert(testWord.exactWords.back().instances.size() == 2);
    assert(testWord.totalInstances.size() == 2);
}

//test if word instance is added if the case sensitve word doesn't match
void insertDiffWord_test()
{
    //declare variables to pass into function
    string userWord = "glory";
    string file = "glory.txt";
    int line = 65;

    //initialize word instance
    Word testWord(userWord, file, line);

    //insert same word but differnet file and line number
    string diffWord = "gargoyle";
    assert(not testWord.insert(diffWord, file, line));
    assert(testWord.exactWords.size() == 1);
    assert(testWord.totalInstances.size() == 1);
}


/*
// string isWord()
*/

//tests if funtion returns true if given the smae word as the word object
void isWord_test()
{
    //declare variables to pass into function
    string userWord = "Glory";
    string file = "glory.txt";
    int line = 65;

    //initialize the word instance
    Word testWord(userWord, file, line);

    string diffWord = "nope";
    string sameWord = "glorY";
    assert(testWord.isWord(userWord));
    assert(testWord.isWord(sameWord));
    assert(not testWord.isWord(diffWord));
}

//tests funtion for string with non letters in the middle
void isWord_nonLetter_test()
{
    //declare variables to pass into function
    string userWord = "9B0-19A0";
    string file = "glory.txt";
    int line = 65;

    //initialize the word instance
    Word testWord(userWord, file, line);

    string sameWord = "9b0-19A0";
    assert(testWord.isWord(sameWord));
}


/*
// Word *getNext()
*/

//tests if the funciton gets a Word's next pointer 
void getNext_test()
{
    //declare variables to pass into function
    string userWord = "glory";
    string file = "glory.txt";
    int line = 65;

    //initialize 2 word instances
    Word testWord(userWord, file, line);
    Word testWord_2(userWord, file, line);

    //set the next pointer
    testWord.setNext(&testWord_2);

    assert(testWord.getNext() == &testWord_2);
    assert(testWord_2.getNext() == nullptr);

}


/*
// string getWord()
*/

//tests function on uppercase word, lowercase word, and single letter word
void getWord_test()
{
    //declare variables to pass into function
    string userWord1 = "glory";
    string userWord2 = "Glory";
    string userWord3 = "g";
    string file = "glory.txt";
    int line = 65;

    //initialize 2 word instances
    Word testWord(userWord1, file, line);
    Word testWord_2(userWord2, file, line);
    Word testWord_3(userWord3, file, line);

    assert(testWord.getWord() == userWord1);
    assert(testWord2.getWord() == userWord2);
    assert(testWord3.getWord() == userWord3);
}


/********************************************************************\
*                               WordHash                             *
\********************************************************************/


/*
// WordHash()
*/

//tests the consttructor of the wordhash object
void hashContructor_test()
{
    //declare hash
    WordHash hash;

    //check that the member vars were set
    assert(hash.tableSize == 50);
    assert(hash.numWords == 0);
    
    //check that the table is set
    for (int i = 0; i < hash.tableSize; ++i)
    {
        assert(hash.hashTable[i] == nullptr);
    }  
}

/*
// insert(string word, string ogWord, string file, int line)
*/

//tests insert with one word
void insertOneWord_test()
{
    //declare hash
    WordHash hash;

    //create strings to populate a word in the hash
    string word = "glory";
    string file = "g.txt";
    int line = 65;

    //insert word into hash
    hash.insert(word, file, line);

    assert(hash.numWords == 1);
    assert(hash.getWord(word)->isWord(word));
    assert(hash.getWord(word)->totalInstances.front().fileName == file);
    assert(hash.getWord(word)->totalInstances.front().lineNum == line);
}

//tests insert with muliple of the same word
void insertMultofSameWord_test()
{
    //declare hash
    WordHash hash;

    //create strings to populate a word in the hash
    string word = "glory";
    string file = "g.txt";
    int line = 65;

    //insert word into hash
    hash.insert(word, file, line);
    line++;
    hash.insert(word, file, line);
    line++;
    hash.insert(word, file, line);

    assert(hash.numWords == 1);
    assert(hash.getWord(word)->isWord(word));
    assert(hash.getWord(word)->exactWords.size() == 1);
    assert(hash.getWord(word)->totalInstances.size() == 3);
}

//insert multiple different words;
void insertDifferentWords_test()
{
    WordHash hash;

    //create strings to populate a word in the hash
    string word = "g";
    string file = "g.txt";
    int line = 65;

    //insert words into hash
    for (int i = 97; i < 122; ++i)
    {
        char newChar = char(i);
        word += newChar;
        hash.insert(word, file, line);
    }

    assert(hash.numWords == 25);
    string key = "gab";
    assert(hash.getWord(key)->isWord(key));
    key = "gabcdefg";
    assert(hash.getWord(key)->isWord(key));
}

/*
// int listLength(Word *curr);
*/

//tests function on multi, singular and empty list
void listLength_test()
{
    //declare hash
    WordHash hash;

    //create strings to populate a word in the hash
    string word = "glory";
    string file = "g.txt";
    int line = 65;

    //declare 3 words
    Word word1(word, file, line);
    Word word2(word, file, line);
    Word word3(word, file, line);

    //set the pointers of each word to each other
    word1.setNext(&word2);
    word2.setNext(&word3);

    assert(hash.listLength(&word1) == 3);
    assert(hash.listLength(&word2) == 2);
    assert(hash.listLength(&word3) == 1);
    assert(hash.listLength(word3.getNext()) == 0);
}


// 
// Word *getLast(Word *curr);
//

//tests func on populated list
void getLast_test()
{
    //declare hash
    WordHash hash;

    //create strings to populate a word in the hash
    string word = "glory";
    string file = "g.txt";
    int line = 65;

    //declare 3 words
    Word word1(word, file, line);
    Word word2(word, file, line);
    Word word3(word, file, line);

    //set the pointers of each word to each other
    word1.setNext(&word2);
    word2.setNext(&word3);

    assert(hash.getLast(&word1) == &word3);
}

//tests func on single list
void getLastSingular_test()
{
    //declare hash
    WordHash hash;

    //create strings to populate a word in the hash
    string word = "glory";
    string file = "g.txt";
    int line = 65;

    //declare 3 words
    Word word1(word, file, line);

    assert(hash.getLast(&word1) == &word1);
}


/*
// expand() (also insert(Word *copyWord, Word *table[]))
*/

//MUST SET INITIAL TABLE SIZE TO 4 IN ORDER TO WORK

// tests if function expands
// void expand_test()
// {
//     //declare hash
//     WordHash hash;

//     //create strings to populate a word in the hash
//     string word = "glory";
//     string file = "g.txt";
//     int line = 65;

//     //insert 2 words into hash
//     hash.insert(word, file, line);
//     string word2 = "fish";
//     hash.insert(word2, file, line);

//     assert(hash.numWords == 2);
//     assert(hash.tableSize == 4);

//     //add in another word and check if expansion occured
//     string word3 = "love";
//     hash.insert(word3, file, line);

//     assert(hash.numWords == 3);
//     assert(hash.tableSize == 8);

//     //check if elements are still accesable
//     assert(hash.getWord(word2)->isWord(word2));
//     assert(hash.getWord(word)->isWord(word));
//     assert(hash.getWord(word3)->isWord(word3));
// }


// 
// makeLower
//

//test on word with diff cases, all uppercase, all lowercase, and numbers/symbol
void makeLower_test()
{
    //initialize wordhash object
    WordHash hash;

    //intitilize words to make lower
    string allLower = "abcdefghijklmnopqrstuvwxyz";
    string allUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string mix = "AbcdeFGHijKLmNoPQRsTuVWXyz";
    string numsAndSymbs = "123a45678b9!@#$c%^&*()";

    assert(hash.makeLower(allLower) == allLower);
    assert(hash.makeLower(allUpper) == allLower);
    assert(hash.makeLower(mix) == allLower);
    assert(hash.makeLower(numsAndSymbs) == numsAndSymbs);
}

/********************************************************************\
*                             FileHash                               *
\********************************************************************/


/*
// constructor
*/

//tests if all of the member vars were initilialized
void fileHashConstructor_test()
{
    //declare file hash
    FileHash fhash;

    //assert that it's member variables were declared properly
    assert(fhash.numFiles == 0);
    assert(fhash.tableSize == 10);
    for (int i = 0; i < fhash.tableSize; ++i)
    {
        assert(fhash.fileTable[i].empty);
    }
}


/*
// insert(string fPath, string fName);
*/

//tests insert for multliple different files and pathways
void insertFile_test()
{
    //declare file hash
    FileHash fhash;

    //initialize strings to pass into filehash
    string file1 = "a.txt";
    string file2 = "b.txt";
    string file3 = "c.txt";
    string file4 = "d.txt";
    string path1 = "dir1/dir2/";
    string path2 = "dir1/";
    string path3 = "dir1/dir2/";
    string path4 = "dir1/";

    //insert into hash
    fhash.insert(path1, file1);
    fhash.insert(path2, file2);
    fhash.insert(path3, file3);
    fhash.insert(path4, file4);

    assert(fhash.numFiles == 4);
    assert(fhash.testReturn(file1) == "dir1/dir2/a.txt");
    assert(fhash.testReturn(file2) == "dir1/b.txt");
    assert(fhash.testReturn(file3) == "dir1/dir2/c.txt");
    assert(fhash.testReturn(file4) == "dir1/d.txt");
}


/*
// print
*/

//tests the print funciton
void fHashPrint_test()
{
    //declare file hash
    FileHash fhash;

    //initialize strings to pass into filehash
    int line = 1;
    string file1 = "a.txt";
    string file2 = "b.txt";
    string path1 = "dir1/dir2/";
    string path2 = "dir1/";

    //insert into hash
    fhash.insert(path1, file1);
    fhash.insert(path2, file2);

    //create an output stream (not usable)
    ofstream ss;

    assert(fhash.print(file1, line, ss) == path1);
    assert(fhash.print(file2, line, ss) == path2);
}


/*
// expand
*/

//MUST SET TABLE SIZE TO 4

// void expandFileHash_test()
// {
//     //declare file hash
//     FileHash fhash;

//     //initialize strings to pass into filehash
//     string file1 = "a.txt";
//     string file2 = "b.txt";
//     string file3 = "c.txt";
//     string path1 = "dir1/dir2/";
//     string path2 = "dir1/";
//     string path3 = "dir1/dir2/";

//     fhash.insert(path1, file1);
//     fhash.insert(path2, file2);
//     assert(fhash.tableSize == 4);

//     fhash.insert(file3, path3);
//     assert(fhash.tableSize == 8);
//     assert(fhash.testReturn(file1) == path1 + file1);
//     assert(fhash.testReturn(file2) == path2 + file2);
//     assert(fhash.testReturn(file3) == path3 + file3);
// }



/********************************************************************\
*                             Gerp                                   *
\********************************************************************/


/*
// constructor
*/

//tests to make sure the memeber vars of a gerp object are initialized
void gerpContructor_test()
{
    //initialie gerp object using test directories
    string output = "out";
    Gerp gerp("testTrav", output);

    assert(gerp.wordIndex.numWords == 30);
    assert(gerp.fileIndex.numFiles == 6);
}
