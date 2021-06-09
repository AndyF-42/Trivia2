// stack.cpp

#include "stack.h"

/* Andy Fleischer - CS163 - Program #2 - 4/30/2021
 * -----------------------------------------------
 * This class is an ADT implementation of the stack
 * data structure. It is organized as a linear
 * linked list of arrays of trivia structs.
 * It includes functions to push (add to top), pop
 * (remove from top), and display all. */

//constructor - set all data members
stack::stack()
{
    head = NULL;
    top_index = 0;
}

//destructor - delete the data in the head, then delete the data in all other nodes
stack::~stack()
{
    if (!head)
        return;

    s_node* current = head->next;

    for (int i = 0; i < top_index; i++) //delete only the used data for the head
    {
        delete [] head->items[i].question;
        head->items[i].question = NULL;
        delete [] head->items[i].answer;
        head->items[i].answer = NULL;
    }
    delete [] head->items;
    head->items = NULL;
    delete head;

    while (current) //go through list
    {
        for (int i = 0; i < MAX; i++) //delete and reset data in trivia
        {
            delete [] current->items[i].question;
            current->items[i].question = NULL;
            delete [] current->items[i].answer;
            current->items[i].answer = NULL;
        }
        delete [] current->items;
        current->items = NULL;

        s_node* temp = current->next; //move to next
        delete current;
        current = temp;
    }
    head = NULL;
    top_index = 0;
}

//push - add given trivia to head
int stack::push(const trivia& to_add)
{
    if (!to_add.question || !to_add.answer)
        return 0; //error: bad input(s)

    if (!head || top_index == MAX) //need new node, add at head and reset top_index
    {
        s_node* temp = head;
        head = new s_node;
        head->next = temp;
        head->items = new trivia[MAX];
        top_index = 0;
    }

    head->items[top_index].question = new char[strlen(to_add.question) + 1]; //copy in q and a
    strcpy(head->items[top_index].question, to_add.question);
    head->items[top_index].answer = new char[strlen(to_add.answer) + 1];
    strcpy(head->items[top_index].answer, to_add.answer);
    ++top_index;

    return 1;
}

//display_all - display all questions and answers
int stack::display_all() const
{
    if (!head)
        return 0; //error: no data to display

    for (int i = top_index - 1; i >= 0; i--) //first display up to top_index from head
    {
        std::cout << "  Q: " << head->items[i].question << std::endl;
        std::cout << "  A: " << head->items[i].answer << "\n" << std::endl;
    }

    s_node* current = head->next;
    while (current) //second display all the contents of all the nodes past the head
    {
        for (int i = MAX - 1; i >= 0; i--)
        {
            std::cout << "  Q: " << current->items[i].question << std::endl;
            std::cout << "  A: " << current->items[i].answer << "\n" << std::endl;
        }
        current = current->next;
    }

    return 1;
}

//pop - remove question from head and fill data into "removed"
int stack::pop(trivia& removed)
{
    if (!head)
        return 0; //error: no data to be removed

    removed.question = new char[strlen(head->items[top_index - 1].question) + 1]; //copy in the data we will remove
    strcpy(removed.question, head->items[top_index - 1].question);
    removed.answer = new char[strlen(head->items[top_index - 1].answer) + 1];
    strcpy(removed.answer, head->items[top_index - 1].answer);


    delete head->items[top_index - 1].question; //delete the data in the trivia
    head->items[top_index - 1].question = NULL;
    delete head->items[top_index - 1].answer;
    head->items[top_index - 1].answer = NULL;
    --top_index;

    if (top_index == 0) //if we removed everything in a node, delete the node
    {
        s_node* temp = head->next;
        delete head->items;
        delete head;
        head = temp;
        top_index = MAX;
    }
    return 1;
}
