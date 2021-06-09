// queue.h

#include "trivia.h"

/* Andy Fleischer - CS163 - Program #2 - 4/30/2021
 * -----------------------------------------------
 * This class is an ADT implementation of the queue
 * data structure. It is organized as a circular
 * linked list of trivia structs.
 * It includes functions to enqueue (add to rear),
 * dequeue (remove from front), and display all. */

struct q_node //holds a single trivia item and a next pointer
{
    trivia item;
    q_node* next;
};

class queue
{
    public:
        queue(); //constructor (task 6)
        ~queue(); //destructor (task 7)

        //these functions return 0 if an error occured or 1 for a success
        int enqueue(const trivia& to_add); //add a new trivia question to the rear (task 8)
        int display_all() const; //display all questions in the queue (task 9)
        int dequeue(trivia& removed); //remove a question from the front and fill data into passed trivia (task 10)

    private:
        q_node* rear; //rear of circular linked list
};
