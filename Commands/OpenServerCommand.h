#ifndef FLIGHT_SIMULATOR_OPENSERVERCOMMAND_H
#define FLIGHT_SIMULATOR_OPENSERVERCOMMAND_H

#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include "Command.h"

using namespace std;

/**
 * OpenServerCommand Class
 *
 * This class implements the Command interface. It opens in the background
 * a thread that runs a server that listens to a particular port it receives
 * and reads line by line. The tempo is controlled by the simulator that connects
 * to the program as a client and writes to the program line by line.
 * The program stores the sampled values in SimMap from which it can get the updated
 * value of a variable in O(1) time complexity.
 */
class OpenServerCommand : public Command {
    bool stop = false;
    thread thread1;
    int socketfd;
    const int movement = 2;
public:
    OpenServerCommand();
    virtual ~OpenServerCommand();
    virtual int execute(vector<string> &strArr, int index);
    void readLineByLine(int client);
    void startThread(int client_socket);
};

#endif //FLIGHT_SIMULATOR_OPENSERVERCOMMAND_H