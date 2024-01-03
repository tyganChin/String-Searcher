 /*
 *  fileHash.h
 *  Tygan Chin tchin02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Interface for fileHash class. Declares the funcitons that insert 
 *  files and their paths into an index and  prints out the paths to each file, 
 *  given the file name index.
 *
 */

#ifndef _FILEHASH_H_
#define _FILEHASH_H_

#include <string>
#include "DirNode.h"
#include <list>
#include <fstream>

using namespace std;

class FileHash
{
public:

    //constructor and destructor
    FileHash();
    ~FileHash();

    //setter
    void insert(string &fPath, string fName);

    //getter
    string print(string &wordFile, int &line, ofstream &out);

private:

    struct filePath
    {
        string file, path;
        bool empty;
    };
    
    //member variables
    int tableSize;
    int numFiles;
    filePath *fileTable;

    //helper funcs
    void sertHelp(string &fPath, string &fName, filePath tab[], bool exp);
    void printLine(string &wordFile, int &lineNum);
    void expand();

    //test functions
    // string testReturn(string &wordFile);
    // void testPrint();
    // void printTableEntry(filePath entry);
};

#endif
