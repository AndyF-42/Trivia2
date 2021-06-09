// main.cpp

#include "stack.h"
#include "queue.h"
using namespace std;

/* Andy Fleischer - CS163 - Program #2 - 4/30/2021
 * -----------------------------------------------
 * This class is a sample client implementation of
 * the stack and queue ADTs. It is a trivia game
 * with draw queue, discard stack and correct stack. */

void add(queue* draw_pile);
void draw(queue* draw_pile, stack* discard, stack* correct);
void display(stack* discard, stack* correct, queue* draw_pile);
bool is_correct(char* real, char* given);
void help();

int main()
{
    stack* discard = new stack; //initialize stacks and queue
    stack* correct = new stack;
    queue* draw_pile = new queue;

    cout << "-----------------------" << endl;
    cout << " Welcome to Trivia 2.0 " << endl;
    cout << "-----------------------" << endl;
    help();

    bool running = true;
    char input[20];
    while (running) //main program loop
    {
        cout << ">> "; //get input
        cin.get(input, 20);
        cin.clear();
        cin.ignore(20, '\n');

        if (strcmp(input, "add") == 0) //check input
            add(draw_pile);
        else if (strcmp(input, "draw") == 0)
            draw(draw_pile, discard, correct);
        else if (strcmp(input, "dall") == 0)
            display(discard, correct, draw_pile);
        else if (strcmp(input, "help") == 0)
            help();
        else if (strcmp(input, "quit") == 0)
            running = false;
        else
            cout << "Invalid command. Type \"help\" for a list of valid commands." << endl;
    }

    delete discard; //delete and reset structures
    delete correct;
    delete draw_pile;
    discard = NULL;
    correct = NULL;
    draw_pile = NULL;

    return 0;
}

//add a question to the draw pile
void add(queue* draw_pile)
{
    char question[100]; //read in the question and answer
    char answer[100];
    cout << "Question: ";
    cin.get(question, 100);
    cin.clear();
    cin.ignore(100, '\n');
    cout << "Answer: ";
    cin.get(answer, 100);
    cin.clear();
    cin.ignore(100, '\n');
    
    trivia to_add; //copy in the data to a struct
    to_add.question = new char[strlen(question) + 1];
    to_add.answer = new char[strlen(question) + 1];
    strcpy(to_add.question, question);
    strcpy(to_add.answer, answer);
   
    if (draw_pile->enqueue(to_add)) //add to draw pile and handle errors
        cout << "Added." << endl;
    else
        cout << "Could not add." << endl;

    delete [] to_add.question;
    delete [] to_add.answer;
}

//draw the first question from the draw queue and send to correct if user is correct, otherwise to discard
void draw(queue* draw_pile, stack* discard, stack* correct)
{
    struct trivia drawn;
    if (!draw_pile->dequeue(drawn)) //draw pile empty, return
    {
        cout << "Draw pile is empty!" << endl;
        return;
    }
    cout << drawn.question << " "; //display the question, read in the answer
    char answer[100];
    cin.get(answer, 100);
    cin.clear();
    cin.ignore(100, '\n');

    if (is_correct(drawn.answer, answer)) //check answer, say if correct or not, and error handle if something went very wrong
    {
        cout << "Correct!" << endl;
        if (!correct->push(drawn))
            cout << "An error occured while adding the question to the correct pile." << endl;
    }
    else
    {
        cout << "Incorrect! The answer was: " << drawn.answer << endl;
        if (!discard->push(drawn))
            cout << "An error occured while adding the question to the discard pile." << endl;
    }
    delete [] drawn.question; //make sure to deallocate!
    delete [] drawn.answer; 
} 

//compares if two char* are the same, case insensitive (used for checking trivia answers)
bool is_correct(char* real, char* given)
{
    if (strlen(real) != strlen(given)) //not same length, must be wrong (following loop does not check different lengths)
        return false;

    for (size_t i = 0; i < strlen(real); i++)
        if (tolower(real[i]) != tolower(given[i])) //change both to lower and compare
             return false;
    return true;
}

//display all questions from both stacks and queue, saying if empty
void display(stack* discard, stack* correct, queue* draw_pile)
{
    cout << "Discard:" << endl;
    if (!discard->display_all())
        cout << "  Empty.\n" << endl;
    cout << "Correct:" << endl;
    if (!correct->display_all())
        cout << "  Empty.\n" << endl;
    cout << "Draw:" << endl;
    if (!draw_pile->display_all())
        cout << "  Empty.\n" << endl;
}

//show valid commands
void help()
{
    cout << "Valid commands are:" << endl;
    cout << "  add  - Add a trivia question to the draw queue" << endl;
    cout << "  draw - Ask the top question on the draw queue" << endl;
    cout << "  dall - Display all questions and answers in all stacks and queues (for debugging)" << endl;
    cout << "  help - List these commands" << endl;
    cout << "  quit - Stop the program" << endl;
}
