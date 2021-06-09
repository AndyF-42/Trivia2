// queue.cpp

#include "queue.h"

/* Andy Fleischer - CS163 - Program #2 - 4/30/2021
 * -----------------------------------------------
 * This class is an ADT implementation of the queue
 * data structure. It is organized as a circular
 * linked list of trivia structs.
 * It includes functions to enqueue (add to rear),
 * dequeue (remove from front), and display all. */

//constructor - set rear to NULL
queue::queue()
{
    rear = NULL;
}

//destructor - loop through and delete data from all nodes
queue::~queue()
{
    if (!rear) //no data to delete
        return;

    q_node* current = rear->next;
    while (current != rear) //loop through the queue, deleting until at rear
    {
        delete [] current->item.question;
        current->item.question = NULL;
        delete [] current->item.answer;
        current->item.answer = NULL;
        q_node* temp = current->next;
        delete current;
        current = temp;
    }
    delete [] rear->item.question; //finally, delete rear and set to null
    rear->item.question = NULL;
    delete [] rear->item.answer;
    rear->item.answer = NULL;
    delete rear;
    rear = NULL;
}

//enqueue - add the given trivia question to the rear 
int queue::enqueue(const trivia& to_add)
{
    if (!to_add.question || !to_add.answer)
        return 0; //error: bad input

    q_node* new_node = new q_node; //make the new node and copy in the data
    new_node->item.question = new char[strlen(to_add.question) + 1];
    strcpy(new_node->item.question, to_add.question);
    new_node->item.answer = new char[strlen(to_add.answer) + 1];
    strcpy(new_node->item.answer, to_add.answer);

    if (!rear) //no data yet, rear becomes new_node
    {
        rear = new_node;
        rear->next = rear;
        return 1;
    }
    new_node->next = rear->next; //add at rear
    rear->next = new_node;
    rear = new_node;
    return 1; 
}

//display_all - display all questions and answers
int queue::display_all() const
{
    if (!rear)
        return 0; //error: no data to display

    q_node* current = rear->next;
    do //loop through and display data
    {
        std::cout << "  Q: " << current->item.question << std::endl;
        std::cout << "  A: " << current->item.answer << "\n" << std::endl;
        current = current->next;
    }
    while (current != rear->next);
    return 1;
}

//dequeue - remove question from head, fill data into "removed"
int queue::dequeue(trivia& removed)
{
    if (!rear)
        return 0; //error: no data to remove

    removed.question = new char[strlen(rear->next->item.question) + 1]; //copy in data to "removed"
    strcpy(removed.question, rear->next->item.question);
    removed.answer = new char[strlen(rear->next->item.answer) + 1];
    strcpy(removed.answer, rear->next->item.answer);
    delete [] rear->next->item.question; //now delete rear->next
    rear->next->item.question = NULL;
    delete [] rear->next->item.answer;
    rear->next->item.answer = NULL;
    
    if (rear == rear->next) //if there was only one node (rear), delete rear and set to NULL
    {
        delete rear;
        rear = NULL;
        return 1;
    }
    q_node* temp = rear->next->next; //more than one node, hook up the CLL
    delete rear->next;
    rear->next = temp;
    return 1;
}
