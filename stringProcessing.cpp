 /*
 *  stringProcessing.cpp
 *  Tygan Chin tchin02
 *  3/28/2023
 *
 *  gerp
 * 
 *  purpose: Implements the stripNonAlphaNum function that strips the   
 *  nonalphanuric characters from the front and back of string.
 *
 */

#include "stringProcessing.h"
#include <string>

#include <iostream>


/*
 * name: stripNonAlphaNum
 * purpose: Strips a given string's leading and trailing non-alphanum values 
 * arguments: A string
 * returns: The stripped string
 */
std::string stripNonAlphaNum(std::string input)
{
    //set length
    std::string::size_type length = input.length();

    //ftrip front
    bool done = false;
    while (((length - input.length()) < length) and (not done))
    {
        if (isalnum(input[0]))
        {
            done = true;
            continue;
        }
        input.erase(input.begin());
    }

    //strip back
    done = false;
    while ((input.length() > 1) and (not done))
    {
        if (isalnum(input[input.length() - 1]))
        {
            done = true;
            continue;
        }
        input.erase(input.begin() + input.length() - 1);
    }

    return input;
}
