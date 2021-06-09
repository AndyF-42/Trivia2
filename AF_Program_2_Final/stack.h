// stack.h

#include "trivia.h"

/* Andy Fleischer - CS163 - Program #2 - 4/30/2021
 * -----------------------------------------------
 * This class is an ADT implementation of the stack
 * data structure. It is organized as a linear
 * linked list of arrays of trivia structs.
 * It includes functions to push (add to top), pop
 * (remove from top), and display all. */

const int MAX = 5; //size of trivia array

struct s_node //stack node, holds a dynamically allocated array of trivia and a next pointer
{
    trivia* items;
    s_node* next;
};

class stack
{
    public:
        stack(); //constructor (task 1)
        ~stack(); //destructor (task 2)

        //these functions return 0 if an error occured or 1 for a success
        int push(const trivia& to_add); //add a question to the top of the stack (task 3)
        int display_all() const; //display all questions in the stack (task 4)
        int pop(trivia& removed); //remove a question from the top of the stack and fill data into passed trivia (task 5)

    private:
        s_node* head; //head of stack
        int top_index; //index of where the next trivia should be added
};
