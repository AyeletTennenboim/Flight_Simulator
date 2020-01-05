#include <iostream>
#include <thread>
#include <chrono>
#include "SleepCommand.h"
#include "../Expressions/Expression.h"

using namespace std;

/// Constructor
SleepCommand::SleepCommand() {}

/// Destructor
SleepCommand::~SleepCommand() {}

/**
 * The function executes a Sleep command. It makes the main thread sleeps for
 * a time that set by interpreting and calculating an expression received as a
 * parameter of Sleep command.
 *
 * @param strArr vector of strings received from the lexer.
 * @param index current position on the strArr vector.
 * @return number of steps needed to be passed on the vector till the next command.
 */
int SleepCommand::execute(vector<string> &strArr, int index) {
    int time;
    Interpreter* i = nullptr;
    Expression* ex = nullptr;
    // Interpret and calculate the expression received as a parameter of Sleep command
    try {
        i = new Interpreter();
        ex = i->interpret(strArr[index + 1]);
        time = (int) ex->calculate();
        // Make the main thread sleeps for the time that was calculated
        this_thread::sleep_for(chrono::milliseconds(time));
        delete i;
        delete ex;
        // Catch if interpretation or calculation throws an exception
    } catch (const char* e) {
        if (ex != nullptr) {
            delete ex;
        }
        if (i != nullptr) {
            delete i;
        }
        // Print the exception message and exit
        cout << e << endl;
        exit(-1);
    }
    // Return number of steps needed to be passed on the vector till the next command
    return this->movement;
}