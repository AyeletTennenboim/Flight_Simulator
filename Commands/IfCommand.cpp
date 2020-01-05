#include "IfCommand.h"
#include "../Maps/CommandsMap.h"
#include "../Maps/SymbolTable.h"

using namespace std;

/// Constructor
IfCommand::IfCommand() {}

/// Destructor
IfCommand::~IfCommand() {}

/**
 * This function executes an If command. It checks if a condition is true.
 * If it is - the function executes all commands in the If scope,
 * it can be a command from the CommandsMap or setting a var from Symbol Table.
 * On each command, the current index is updated according to the number of
 * steps the command's execute() function returns, so the function knows what is
 * the next command to execute.
 * If the condition is false - the current index is updated to be the index after
 * the character '}' that symbolizes the end of the scope, but without executing the
 * commands in the scope.
 * At the end, the function returns number of steps needed to be passed on the vector
 * till the next command after the if scope.
 *
 * @param strArr vector of strings received from the lexer.
 * @param index current position on the strArr vector.
 * @return number of steps needed to be passed on the vector till the next command.
 */
int IfCommand::execute(vector<string> &strArr, int index) {
    int originIndex = index;
    // Update the current index after this If condition
    int curIndex = originIndex + 5;
    // Get from vector the left expression, sign and right expression for checking the condition
    string leftExp = strArr[originIndex + 1];
    string sign = strArr[originIndex + 2];
    string rightExp = strArr[originIndex + 3];
    CommandsMap* commandsMap = CommandsMap::getInstance();
    SymbolTable* symbolTable = SymbolTable::getInstance();
    // If the condition is true
    if (this->conditionIsTrue(leftExp, sign, rightExp)) {
        // While the command is in the scope.
        while (strArr[curIndex] != "}") {
            // If the command exists in the CommandsMap
            if (commandsMap->isCommandExists(strArr[curIndex])) {
                // Get the appropriate command
                Command *c = commandsMap->getCommand(strArr[curIndex]);
                // Execute command and update the current index
                curIndex += c->execute(strArr, curIndex);
            // If the command doesn't exist in the CommandsMap (means it's a var's value updating)
            } else {
                // Get the suitable var from Symbol Table and update its value
                symbolTable->getVarObject(strArr[curIndex])->setValue(strArr[curIndex + 2]);
                // Add 3 to the current index after this action
                curIndex += 3;
            }
        }
    // If the condition is false - get to next command after the If scope without executing the commands in the scope
    } else {
        // Add 1 to the current index until getting to the end of the scope '}'
        while (strArr[curIndex] != "}") {
            curIndex++;
        }
    }
    // Calculate the number of steps needed to be passed on the vector till the next command
    this->movement = curIndex - originIndex + 1;
    return this->movement;
}