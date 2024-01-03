/*
 *  fileHash.cpp
 *  Tygan Chin tchin02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Implementation for fileHash class. Declares the functions that 
 *  insert files and their paths into an index and  prints out the paths to 
 *  each file, given the file name. 
 *
 */

#include "fileHash.h"
#include <functional>
#include <string>
#include <iostream>


/*
 * name: FileHash
 * purpose: Create hash using given file directory w/ filenames serving the keys
 * arguments: A given file directory
 * returns: n/a
 */
FileHash::FileHash()
{
    //initialize member varaibles
    tableSize = 10;
    numFiles = 0;

    //create an initialize a hash table of filePaths
    fileTable = new filePath[tableSize];
    for (int i = 0; i < tableSize; ++i)
        fileTable[i].empty = true;
}

/*
 * name: ~FileHash
 * purpose: Delete the file table from memory
 * arguments: n/a
 * returns: n/a
 */
FileHash::~FileHash()
{
    delete [] fileTable;
}

/*
 * name: insert
 * purpose: Insert a given pathway and file into a given table
 * arguments: Path to file, file, table to insert into, bool whether expanding
 * returns: n/a
 */
void FileHash::insert(string &fPath, string fName)
{
    sertHelp(fPath, fName, fileTable, true);
}

/*
 * name: insert
 * purpose: Insert a given pathway and file into a given table
 * arguments: Path to file, file, table to insert into, bool whether expanding
 * returns: n/a
 */
void FileHash::sertHelp(string &fPath, string &fName, filePath tab[], bool exp)
{
    //assign hash value
    size_t slot = hash<string>{}(fName) % tableSize;

    //add filePath to table in the first open spot found
    int attempt = 0;
    bool found = false;
    while (not found)
    {
        //reset the slot and attempt if tableSize is reached FORGOT THIS
        if ((int(slot) + attempt) == tableSize)
            slot = attempt = 0;
        
        //insert path into table when empty slot is fount
        if (tab[slot + attempt].empty)
        {
            tab[slot + attempt].file = fName;
            tab[slot + attempt].path = fPath;
            tab[slot + attempt].empty = false;
            found = true;
        }
        attempt++;   
    }

    //increment size and expand if necesary 
    if (exp)
    {
        numFiles++;
        expand();
    }
}

/*
 * name: printPath
 * purpose: Prints the path to the given file and the given line in that file
 * arguments: A file and a line number
 * returns: n/a
 */
string FileHash::print(string &wordFile, int &line, ofstream &out)
{   
    //assign hash value
    size_t slot = hash<string>{}(wordFile) % tableSize;
    
    //find file path and print it out
    int attempt = 0;
    bool found = false;
    while (not found)
    {
        //reset attempt and hash index if they reach end of the table
        if ((int(slot) + attempt) == tableSize)
            slot = attempt = 0;
        
        //check for the file and it's path
        if (not fileTable[slot + attempt].empty)
            if (fileTable[slot + attempt].file == wordFile)
            {
                out << fileTable[slot + attempt].path << wordFile;
                out << ":" << line << ": ";
                return fileTable[slot + attempt].path;
            }
        attempt++;   
    }
    return "";
}

/*
 * name: expand 
 * purpose: Allocate more space for table if too many spots are taken up
 * arguments: n/a
 * returns: n/a
 * effects: FileTable is double the size
 */
void FileHash::expand()
{
    //check if expansion is needed
    if ((float(numFiles) / float(tableSize)) < 0.7)
        return;

    //declare a new hash table with the updated size and initilize it
    tableSize += tableSize;
    filePath *newTable = new filePath[tableSize];
    for (int i = 0; i < tableSize; i++) 
        newTable[i].empty = true;

    //initialize the new table
    for (int i = 0; i < tableSize / 2; ++i)
    {
        filePath curr = fileTable[i];
        if (not curr.empty)
            sertHelp(curr.path, curr.file, newTable, false); //I HAD TRUE
    }

    //delete old table and assing new one to variable
    delete [] fileTable;
    fileTable = newTable;
}


//TEST FUNCTIONS;

/*
 * name: printPath
 * purpose: Prints the path to the given file and the given line in that file
 * arguments: A file and a line number
 * returns: n/a
 */
// string FileHash::testReturn(string &wordFile)
// {   
//     //assign hash value
//     size_t slot = hash<string>{}(wordFile) % tableSize;

//     //find file path and print it out
//     int attempt = 0;
//     bool found = false;
//     while ((not found))
//     {
//         if ((int(slot) + attempt) == tableSize)
//             slot = attempt = 0;
        
//         if (not fileTable[slot + attempt].empty)
//         {
//             return fileTable[slot + attempt].path + wordFile;
//         }
//         attempt++;   
//     }
//     return "";
// }

//prints the file index
// void FileHash::testPrint()
// {
//         cout << "Linear table" << endl;
        
//         for (int i = 0; i < tableSize; ++i) {
//                 cout << i << ":  ";
//                 printTableEntry(fileTable[i]);
//                 cout << endl;
//         }
// }

//prints an a single entry in the file index
// void FileHash::printTableEntry(filePath entry)
// {
//         if (entry.empty)
//                 cout << "empty";
//         else
//                 cout << "key:  "
//                      << entry.file
//                      << "; value:  {"
//                      << entry.path
//                      << "}";
// }
