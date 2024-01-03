 /*
 *  main.cpp
 *  Tygan Chin tchin02
 *  4/15/2023
 *
 *  gerp
 * 
 *  purpose: Runs the gerp program. Prompts and executes user commands   
 *  regarding the location of words in a given file directory.
 *
 */

#include "Gerp.h"
#include <iostream>


/*
 * name: main.cpp
 * purpose: Runs the gerp program
 * arguments: A directory to search and an output file
 * returns: n/a
 * effects: Updates output file with instances of given words in directory
 */
int main(int argc, char *argv[])
{
    //Check if enough arguements were passed in
    if (argc != 3)
    {
        std::cerr << "Usage: ./gerp inputDirectory outputFile" << std::endl;
        exit(EXIT_FAILURE);
    }

    //initialize the gerp object
    Gerp gerp(argv[1], argv[2]);

    //run the gerp program
    gerp.run();

    return 0;
}
