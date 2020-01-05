#ifndef FLIGHT_SIMULATOR_DEFINEVARCOMMAND_H
#define FLIGHT_SIMULATOR_DEFINEVARCOMMAND_H

#include "Command.h"
#include "../Maps/SymbolTable.h"
#include "../Maps/SimMap.h"

using namespace std;

/**
 * DefineVarCommand Class
 *
 * This class implements the Command interface. It defines variables the program
 * works with during running.
 * For each new defined variable, the program sets a name, a simulator name (if exists),
 * and the binding direction between the variable in the program and a variable in
 * the simulator, so when one is changed then the other one will also be changed.
 * After defining, the function inserts the variable into the Symbol Table.
 */
class DefineVarCommand : public Command {
    int movement;
    SymbolTable* symbolTable = SymbolTable::getInstance();
    SimMap* simMap = SimMap::getInstance();
public:
    DefineVarCommand();
    virtual ~DefineVarCommand();
    virtual int execute(vector<string> &strArr, int index);
};

#endif //FLIGHT_SIMULATOR_DEFINEVARCOMMAND_H