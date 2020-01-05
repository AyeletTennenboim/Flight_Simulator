#ifndef FLIGHT_SIMULATOR_CONNECTCOMMAND_H
#define FLIGHT_SIMULATOR_CONNECTCOMMAND_H

#include <thread>
#include "Command.h"

using namespace std;

/**
 * ConnectCommand Class
 *
 * This class implements the Command interface. In this class the program
 * connects as a client to the simulator, and in a separate thread, it sends
 * flying instructions to the simulator.
 */
class ConnectCommand : public Command {
    bool stop = false;
    thread thread2;
    int client_socket;
    const int movement = 3;
public:
    ConnectCommand();
    virtual ~ConnectCommand();
    virtual int execute(vector<string> &strArr, int index);
    void connectClient(int portInt, string localHost);
    void sendMessage();
};

#endif //FLIGHT_SIMULATOR_CONNECTCOMMAND_H
