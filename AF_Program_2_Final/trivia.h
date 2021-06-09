// trivia.h

#include <iostream>
#include <cstring>
#pragma once

/* Andy Fleischer - CS163 - Program #2 - 4/30/2021
 * -----------------------------------------------
 * This file holds the trivia struct to be used by
 * both the stack and queue classes. It may be
 * changed to a class instead in the future.
 * Currently, the struct holds a char array for
 * a question and a char array for an answer. Both
 * are dynamically allocated. */

struct trivia
{
    char* question;
    char* answer;
};
