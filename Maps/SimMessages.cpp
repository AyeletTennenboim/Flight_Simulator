#include "SimMessages.h"

SimMessages* SimMessages::instance;

/// Constructor
SimMessages::SimMessages() {}

/// Destructor
SimMessages::~SimMessages() {}

/**
 * The function returns an instance of SimMessages.
 *
 * @return instance of SimMessages.
 */
SimMessages* SimMessages::getInstance() {
    // If there is no SimMessages
    if (instance == nullptr) {
        // Create SimMessages
        instance = new SimMessages();
    }
    return instance;
}

/**
 * The function inserts a message that needs to be sent to the simulator
 * into the messages queue.
 *
 * @param message string to send to the simulator.
 */
void SimMessages::insertMessage(string message) {
    this->messages.push_back(message);
}

/**
 * The function returns the first message of the messages queue.
 *
 * @return first message of the messages queue.
 */
string SimMessages::getMessage() {
    // Get the first message of the vector
    string message = this->messages.front();
    // Remove the message from the vector
    this->messages.erase(this->messages.begin());
    // Return the message
    return message;
}

/**
 * The function returns if the messages queue is empty.
 *
 * @return true if the messages queue is empty, and false otherwise.
 */
bool SimMessages::isEmpty() {
    return this->messages.empty();
}