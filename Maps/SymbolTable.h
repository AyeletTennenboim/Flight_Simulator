#ifndef FLIGHT_SIMULATOR_SYMBOLTABLE_H
#define FLIGHT_SIMULATOR_SYMBOLTABLE_H

#include <string>
#include <unordered_map>
#include "Var.h"

using namespace std;

/**
 * SymbolTable Class
 *
 * This class contains a map that links a variable name
 * to its variable object.
 */
class SymbolTable {
    static SymbolTable *instance;
    unordered_map <string, Var*> varsMap;
    // Private constructor to force use of getInstance() to create Singleton object
    SymbolTable();
public:
    static SymbolTable* getInstance();
    bool isVarExists(string var);
    void insertVar(string var, Var* value);
    Var* getVarObject(string var);
    double getVarValue(string var);
    ~SymbolTable();
};

#endif //FLIGHT_SIMULATOR_SYMBOLTABLE_H