#include <iostream>
#include "Var.h"
#include "../Expressions/Expression.h"
#include "SimMessages.h"

/**
 * Constructor
 *
 * @param simVar name of the simulator variable.
 */
Var::Var(string simVar) {
    this->sim = simVar;
}

/// Destructor
Var::~Var() {}

/**
 * The function returns the value of the variable.
 *
 * @return value of the variable.
 */
double Var::getValue() {
    return this->value;
}

/**
 * The function sets the variable value and updates the simulator
 * if it is the binding direction.
 *
 * @param val string of the new value.
 */
void Var::setValue(string val) {
    string valStr, message;
    // Get instance of SimMessages
    SimMessages* simMessages = SimMessages::getInstance();
    Interpreter* i = nullptr;
    Expression* ex = nullptr;
    // Calculate the value from the string with the Expression interpreter
    try {
        i = new Interpreter();
        ex = i->interpret(val);
        this->value = ex->calculate();
        delete i;
        delete ex;
    } catch (const char* e) {
        if (ex != nullptr) {
            delete ex;
        }
        if (i != nullptr) {
            delete i;
        }
        cout << e << endl;
        exit(-1);
    }
    // Set the simulator variable value
    if (this->direction == "->") {
        // Convert the value to string
        valStr = to_string(this->value);
        // Create the message to send to the simulator
        message = "set " + this->sim + " " + valStr + "\r\n";
        // Insert the message into the messages queue
        simMessages->insertMessage(message);
    }
}

/**
 * The function sets the binding direction between this variable and the simulator.
 *
 * @param dir binding direction.
 */
void Var::setDirection(string dir) {
    this->direction = dir;
}

/**
 * The function returns the binding direction between this variable and the simulator.
 *
 * @return binding direction.
 */
string Var::getDirection() {
    return this->direction;
}