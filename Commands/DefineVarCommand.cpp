#include <iostream>
#include "DefineVarCommand.h"
#include "../Expressions/Expression.h"

using namespace std;

/// Constructor
DefineVarCommand::DefineVarCommand() {}

/// Destructor
DefineVarCommand::~DefineVarCommand() {}

/**
 * This function defines a new var and inserts it into the Symbol Table map.
 * For each new defined variable, the program sets a name, a simulator name (if exists),
 * and the binding direction between the variable in the program and a variable in
 * the simulator, so when one is changed then the other one will also be changed.
 * After defining, the function inserts the variable into the Symbol Table.
 * For each type of definition, the function defines the number of steps to return
 * at the end.
 *
 * @param strArr vector of strings received from the lexer.
 * @param index current position on the strArr vector.
 * @return number of steps needed to be passed on the vector till the next command.
 */
int DefineVarCommand::execute(vector<string> &strArr, int index) {
    // Get from vector the var's name, direction and the simulator variable name
    string varName = strArr[index + 1];
    string direction = strArr[index + 2];
    string sim = strArr[index + 4];
    Var* varObj;
    // If the definition is "new var = something"
    if (direction == "=") {
        // There is no appropriate variable in the simulator
        varObj = new Var("Null");
        // Set the variable value
        varObj->setValue(strArr[index + 3]);
        // Insert the new var into the Symbol Table map
        this->symbolTable->insertVar(varName, varObj);
        // Set the number of steps needed to be passed on the vector till the next command
        this->movement = 4;
    // If the new var needs to update a simulator variable
    } else if (direction == "->") {
        // Set the simulator variable name
        varObj = new Var(sim);
        // Set -> direction to know that this variable should update the simulator when it changes
        varObj->setDirection(direction);
        // Insert the new var into the Symbol Table map
        this->symbolTable->insertVar(varName, varObj);
        // Set the number of steps needed to be passed on the vector till the next command
        this->movement = 5;
    // If the new var should to be updated by the simulator
    } else {
        try {
            // Get the suitable variable object from the simMap that holds the simulator variables
            varObj = this->simMap->getVarObject(sim);
        // Catch if the function can't get this var from simMap
        } catch (const char* e) {
            cout << e << endl;
            exit(-1);
        }
        // Set <- direction to know that the variable should be updated by the simulator
        varObj->setDirection(direction);
        // Insert the new var into the Symbol Table map
        this->symbolTable->insertVar(varName, varObj);
        // Set the number of steps needed to be passed on the vector till the next command
        this->movement = 5;
    }
    // Return number of steps needed to be passed on the vector till the next command
    return this->movement;
}