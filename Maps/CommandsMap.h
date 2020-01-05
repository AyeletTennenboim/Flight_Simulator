#ifndef FLIGHT_SIMULATOR_COMMANDSMAP_H
#define FLIGHT_SIMULATOR_COMMANDSMAP_H

#include <unordered_map>
#include <string>
#include "../Commands/Command.h"

using namespace std;

/**
 * CommandsMap Class
 *
 * This class contains a map that links a command string
 * to an object that executes the command.
 */
class CommandsMap {
    static CommandsMap *instance;
    unordered_map <string, Command*> commandsMap;
    // Private constructor to force use of getInstance() to create Singleton object
    CommandsMap();
public:
    static CommandsMap* getInstance();
    bool isCommandExists(string command);
    Command* getCommand(string command);
    ~CommandsMap();
};

#endif //FLIGHT_SIMULATOR_COMMANDSMAP_H
