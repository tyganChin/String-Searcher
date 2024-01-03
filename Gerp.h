 /*
 *  Gerp.h
 *  Tygan Chin tchin02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Interface for Gerp class. Declares functions that prompt and 
 *  execute user for commands regarding a word and file index it creates. 
 *  Commands include, finding any string case sensitively, case insensitvely 
 *  and printing the output to a given output file. 
 *
 */

#ifndef _GERP_H_
#define _GERP_H_

#include "DirNode.h"
#include "WordHash.h"
#include "fileHash.h"
#include "fstream"
#include "sstream"

using namespace std;

class Gerp
{
public:

    //constructor and destructor
    Gerp(const string &file, const string &output);

    //run function
    void run();

private:
    
    WordHash wordIndex;
    FileHash fileIndex;
    ofstream outStream;
    

    //helper functions
    bool query(string &command);
    void printWord(string &word, bool caseSens);
    void switchOutput();
    void traverse(DirNode *curr, string path);
    void readIn(string &path, string file);
    void readLine(string &line, string &fileName, int &lineCount);
    bool stripNonAlphaNum(std::string &input);
};

#endif
