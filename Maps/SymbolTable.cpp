#include "SymbolTable.h"

SymbolTable* SymbolTable::instance;

/// Constructor
SymbolTable::SymbolTable() {}

/**
 * Destructor:
 * The destructor deletes all the Var objects.
 */
SymbolTable::~SymbolTable() {
    for (unordered_map <string, Var*>::iterator it = this->varsMap.begin();
         it != this->varsMap.end(); ++it) {
        // If the object is not shared with the simulator
        if ((it->second != nullptr) && (it->second->getDirection() != "<-")) {
            delete it->second;
        }
        it->second = nullptr;
    }
}

/**
 * The function returns an instance of SymbolTable.
 *
 * @return instance of SymbolTable.
 */
SymbolTable* SymbolTable::getInstance() {
    // If there is no SymbolTable
    if (instance == nullptr) {
        // Create SymbolTable
        instance = new SymbolTable();
    }
    return instance;
}

/**
 * The function returns if the variable exists in the SymbolTable.
 *
 * @param var variable name.
 * @return true if the variable exists in the SymbolTable, and false otherwise.
 */
bool SymbolTable::isVarExists(string var) {
    return (this->varsMap.find(var) != this->varsMap.end());
}

/**
 * The function inserts a variable name and its Var object to the SymbolTable.
 *
 * @param var variable name.
 * @param value Var object.
 */
void SymbolTable::insertVar(string var, Var* value) {
    // If the variable already exists in the map
    if (this->isVarExists(var)) {
        // Update the variable value
        this->varsMap[var] = value;
    // If the variable doesn't exist in the map
    } else {
        // Insert the variable and its value to the map
        this->varsMap.insert(make_pair(var, value));
    }
}

/**
 * The function returns a variable object from the SymbolTable.
 *
 * @param var variable name.
 * @return Var object.
 */
Var* SymbolTable::getVarObject(string var) {
    return this->varsMap.find(var)->second;
}

/**
 * The function returns the value of a variable from the SymbolTable.
 *
 * @param var variable name.
 * @return value of a variable.
 */
double SymbolTable::getVarValue(string var) {
    return this->varsMap.find(var)->second->getValue();
}