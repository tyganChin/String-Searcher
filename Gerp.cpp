 /*
 *  Gerp.cpp
 *  Tygan Chin tchin02 Emily Ye eye03
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Implementation for Gerp class. Implements functions that prompt  
 *  and execute user for commands regarding a word and file index it creates. 
 *  Commands include, finding any string case sensitivly, case insensitvly and 
 *  printing the output to a given output file. 
 *
 */

#include "Gerp.h"
#include "WordHash.h"
#include "fileHash.h"
#include "Word.h"
#include "DirNode.h"
#include "FSTree.h"
#include <fstream>
#include <iostream>
#include <sstream>

/*
 * name: Gerp
 * purpose: Initializes the outfile, word and file indexes of given directory
 * arguments: The name of the given directory and the user output file
 * returns: n/a
 */
Gerp::Gerp(const string &file, const string &output)
{
    //open file stream
    outStream.open(output);

    //create file tree with given directory
    FSTree fileTree(file);

    //traverse tree and all of the words and files to index
    traverse(fileTree.getRoot(), "");

    //dispose of tree
    fileTree.burnTree();
}

/*
 * name: run
 * purpose: Prompts and executes user commands regarding the word index. 
 * arguments: n/a
 * returns: n/a
 */
void Gerp::run()
{
    //prompt user for query
    cout << "Query? ";

    //keep prompting user for commands until end of file or quit is entered
    bool done = false;
    string command;
    while ((not done) and (cin >> command))
    {   
        if (query(command))
        {
            done = true;
            continue;            
        }

        cout << "Query? ";
    }

    //farewell messaage
    cout << "Goodbye! Thank you and have a nice day." << endl;

    //close output file 
    outStream.close();
}

/*
 * name: query
 * purpose: Prompts and executes user commands
 * arguments: A user command
 * returns: False if the quit command is inputted, true otherwise
 */
bool Gerp::query(string &command)
{
    if ((command == "@i") or (command == "@insensitive")) //case insens
    {
        string word;
        cin >> word;
        printWord(word, false);
    }
    else if ((command == "@q") or (command == "@quit")) //quit
    {
        return true;
    }
    else if (command == "@f") //switch output files
    {
        switchOutput();
    }
    else //case sens
    {
        printWord(command, true);
    }

    return false;
}

/*
 * name: printWord
 * purpose: Prints the instances of the given word
 * arguments: The word and whether or not to print case sensitively
 * returns: n/a
 */
void Gerp::printWord(string &word, bool caseSens)
{
    //strip string 
    if ((not stripNonAlphaNum(word) and (caseSens)))
    {
        outStream << " Not Found. Try with @insensitive or @i." << endl;
        return;
    }
    else if ((not stripNonAlphaNum(word) and (not caseSens)))
    {
        outStream << " Not Found." << endl;
        return;
    }

    //print instances
    wordIndex.print(fileIndex, word, caseSens, outStream);
}

/*
 * name: switchOutput
 * purpose: Switch the output file to another one
 * arguments: n/a
 * returns: n/a
 */
void Gerp::switchOutput()
{
    //get new output file
    string newOutput;
    cin >> newOutput;

    //close the old output file
    outStream.close();

    //open the new file
    outStream.open(newOutput);
}

/*
 * name: traverse
 * purpose: Add file paths to file index and words in files to word index
 * arguments: Current node in file tree and current pathway to that node 
 * returns: n/a
 * effects: Fully populates the file and word indexes
 */
void Gerp::traverse(DirNode *curr, string path)
{
    //update pathway
    path += curr->getName();

    //check if file is empty
    if (curr->isEmpty())
        return;

    //check subdirectories
    if (curr->hasSubDir())
        for (int i = 0; i < curr->numSubDirs(); ++i)
            traverse(curr->getSubDir(i), path + "/");

    //add path to fileIndex and its words to WordIndex to table if present
    if (curr->hasFiles())
    {
        path += "/";
        for (int i = 0; i < curr->numFiles(); ++i)
        {
            fileIndex.insert(path, curr->getFile(i));
            readIn(path, curr->getFile(i));
        }        
    }

}

/*
 * name: readIn
 * purpose: Reads in words from a given file and inputs them into word index
 * arguments: The name of the file
 * returns: n/a
 */
void Gerp::readIn(string &path, string file)
{
    //intialize file stream and open file
    ifstream userFile(path + file); //WAS PASSING IN ONLY FILENAMES
    if (not userFile.is_open())
    {
        cerr << "file isn't open" << endl;
        return;
    }

    //vars to store line count and current line of file
    int lineCount = 1;
    string line;

    //read in each line of the file and add it to the word hash
    while (getline(userFile, line))
    {
        readLine(line, file, lineCount);
        lineCount++;
    } 
}

/*
 * name: readLine
 * purpose: Reads in the words of a single line in a file into the word index
 * arguments: A string stream containing the line, the filename, and line num
 * returns: n/a
 */
void Gerp::readLine(string &line, string &fileName, int &lineCount)
{
    //declare string stream and insert the file line into it
    stringstream ss(line);
    
    //add word to word index
    string currWord;
    while (ss >> currWord)
    {
        //strip non alphanuermic values from ends of word
        if (not stripNonAlphaNum(currWord))
            continue;

        wordIndex.insert(currWord, fileName, lineCount);
    }
}

/*
 * name: stripNonAlphaNum
 * purpose: Strips a given string's leading and trailing non-alphanum values 
 * arguments: A string
 * returns: True if the string has characters left after strip, false otherwise
 */
bool Gerp::stripNonAlphaNum(std::string &input)
{
    //strip front of word
    std::string::size_type length = input.length();
    bool frontDone = false;
    while (((length - input.length()) < length) and (not frontDone))
    {
        if (isalnum(input[0]))
        {
            frontDone = true;
            continue;
        }
        input.erase(input.begin());
    }

    //strip back of word
    while ((input.length() > 1) and (frontDone))
    {
        if (isalnum(input[input.length() - 1]))
        {
            frontDone = false;
            continue;
        }
        input.erase(input.begin() + input.length() - 1);
    }

    //check if any string is left
    if (input.length() > 0)
        return true;
    else    
        return false;
}