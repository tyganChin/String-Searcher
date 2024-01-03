 /*
 *  FSTreeTraversal.cpp
 *  Author: Tygan Chin tchin02 
 *  3/28/2023
 *
 *  gerp
 * 
 *  purpose: Declares, implements and tests the traverse function found in 
 *  Gerp.h.
 *
 */

#include "FSTree.h"
#include <iostream>

using namespace std;

void traverseTree(const string &file);
void traverseHelper(DirNode *curr, string path);


int main(int argc, char *argv[])
{
    (void)argc;

    traverseTree(argv[1]);

    return 1;
}

/*
 * name: traverseTree
 * purpose: Create and traverse a file tree and print out full path to each file
 * arguments: The file name
 * returns: n/a
 * effects: Prints out each file path
 */
void traverseTree(const string &file)
{
    //create tree
    FSTree fileTree(file);

    //helper funciton search through tree
    traverseHelper(fileTree.getRoot(), "");
}

/*
 * name: traverseHelper 
 * purpose: Traverse a file tree and print out the full path to each file 
 * arguments: Current node in file tree and current pathway to that node 
 * returns: n/a
 */
void traverseHelper(DirNode *curr, string path)
{
    //update pathway
    path += curr->getName();

    //check if file is empty
    if (curr->isEmpty())
    {
        return;
    }

    //check subdirectories
    if (curr->hasSubDir())
    {
        for (int i = 0; i < curr->numSubDirs(); ++i)
        {
            traverseHelper(curr->getSubDir(i), path + "/");
        }
    }

    //check for files, print their names if they are present
    if (curr->hasFiles())
    {
        for (int i = 0; i < curr->numFiles(); ++i)
        {
           cout << path << "/" << curr->getFile(i) << endl;
        }
    }
}
