#ifndef FLIGHT_SIMULATOR_SIMMESSAGES_H
#define FLIGHT_SIMULATOR_SIMMESSAGES_H

#include <string>
#include <vector>

using namespace std;

/**
 * SimMessages Class
 *
 * This class contains a vector with messages that need to be sent
 * to the simulator.
 */
class SimMessages {
    static SimMessages *instance;
    vector <string> messages;
    // Private constructor to force use of getInstance() to create Singleton object
    SimMessages();
public:
    static SimMessages* getInstance();
    void insertMessage(string message);
    string getMessage();
    bool isEmpty();
    ~SimMessages();
};

#endif //FLIGHT_SIMULATOR_SIMMESSAGES_H
