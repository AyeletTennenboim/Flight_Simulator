#include "CommandsMap.h"
#include "../Commands/Command.h"
#include "../Commands/OpenServerCommand.h"
#include "../Commands/ConnectCommand.h"
#include "../Commands/DefineVarCommand.h"
#include "../Commands/PrintCommand.h"
#include "../Commands/SleepCommand.h"
#include "../Commands/LoopCommand.h"
#include "../Commands/IfCommand.h"

CommandsMap* CommandsMap::instance;

/**
 * Constructor:
 * The constructor creates a new Command object for each command from the file
 * and inserts the command name and its object to a map.
 */
CommandsMap::CommandsMap() {
    this->commandsMap.insert(make_pair("openDataServer", new OpenServerCommand()));
    this->commandsMap.insert(make_pair("connectControlClient", new ConnectCommand()));
    this->commandsMap.insert(make_pair("var", new DefineVarCommand()));
    this->commandsMap.insert(make_pair("Print", new PrintCommand()));
    this->commandsMap.insert(make_pair("Sleep", new SleepCommand()));
    this->commandsMap.insert(make_pair("while", new LoopCommand()));
    this->commandsMap.insert(make_pair("if", new IfCommand()));
}

/**
 * Destructor:
 * The destructor deletes all the Commands objects.
 */
CommandsMap::~CommandsMap() {
    for (unordered_map <string, Command*>::iterator it = this->commandsMap.begin();
         it != this->commandsMap.end(); ++it) {
        delete it->second;
        it->second = nullptr;
    }
}

/**
 * The function returns an instance of CommandsMap.
 *
 * @return instance of CommandsMap.
 */
CommandsMap* CommandsMap::getInstance() {
    // If there is no CommandsMap
    if (instance == nullptr) {
        // Create CommandsMap
        instance = new CommandsMap();
    }
    return instance;
}

/**
 * The function returns if a command exists in the CommandsMap.
 *
 * @param command name of command.
 * @return true if the command exists in the CommandsMap and false otherwise.
 */
bool CommandsMap::isCommandExists(string command) {
    return (this->commandsMap.find(command) != this->commandsMap.end());
}

/**
 * The function returns a command from the CommandsMap.
 *
 * @param command name of command.
 * @return command object.
 */
Command* CommandsMap::getCommand(string command) {
    return this->commandsMap.find(command)->second;
}
