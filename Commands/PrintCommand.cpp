#include <regex>
#include <iostream>
#include "PrintCommand.h"
#include "../Expressions/Expression.h"

using namespace std;

/// Constructor
PrintCommand::PrintCommand() {}

/// Destructor
PrintCommand::~PrintCommand() {}

/**
 * The function executes Print command.
 * It prints a string message or the result of calculating the expression it got.
 *
 * @param strArr vector of strings received from the lexer.
 * @param index current position on the strArr vector.
 * @return number of steps needed to be passed on the vector till the next command.
 */
int PrintCommand::execute(vector<string> &strArr, int index) {
    string str;
    Interpreter* i = nullptr;
    Expression* ex = nullptr;
    // If the parameter to print is an expression
    if (strArr[index + 1].find("\"") == string::npos) {
        // Interpret and calculate the expression
        try {
            i = new Interpreter();
            ex = i->interpret(strArr[index + 1]);
            // Print the result of calculating the expression
            cout << ex->calculate() << endl;
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
    // If the parameter to print is a string
    } else {
        str = strArr[index + 1];
        // Remove the ""
        str.erase(remove(str.begin(), str.end(), '\"'), str.end());
        // Print the string
        cout << str << endl;
    }
    // Return number of steps needed to be passed on the vector till the next command
    return this->movement;
}