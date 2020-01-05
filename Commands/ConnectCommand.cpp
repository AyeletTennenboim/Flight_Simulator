#include "ConnectCommand.h"
#include "../Expressions/Expression.h"
#include "../Maps/SimMessages.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <regex>
#include <unistd.h>

using namespace std;

/// Constructor
ConnectCommand::ConnectCommand() {}

/**
 * Destructor:
 * The destructor stops the while loop in sendMessage function, closes the
 * client socket and executes the thread's join() function.
 */
ConnectCommand::~ConnectCommand() {
    this->stop = true;
    // Close client socket
    close(this->client_socket);
    // Execute join() function
    if (this->thread2.joinable()) {
        this->thread2.join();
    }
}

/**
 * The function executes two other functions: in the first function the program
 * connects as a client to the simulator, and in the second function the program
 * sends messages to the simulator.
 *
 * @param strArr vector of strings received from the lexer.
 * @param index current position on the strArr vector.
 * @return number of steps needed to be passed on the vector till the next command.
 */
int ConnectCommand::execute(vector<string> &strArr, int index) {
    int portInt;
    Interpreter* i = nullptr;
    Expression* ex = nullptr;
    // Convert portInt from string to int
    try {
        i = new Interpreter();
        ex = i->interpret(strArr[index + 2]);
        portInt = (int) ex->calculate();
        delete i;
        delete ex;
    // Catch if interpretation or calculation throws an exception
    } catch (const char* e) {
        if (ex != nullptr) {
            delete ex;
        }
        if (i != nullptr) {
            delete i;
        }
        // Print the exception message and exit
        cout << e << endl;
        exit(-1);
    }
    // Connect as client
    connectClient(portInt, strArr[index+1]);
    // Start thread that sends messages to the simulator
    this->thread2 = thread(&ConnectCommand::sendMessage, this);
    // Return number of steps needed to be passed on the vector till the next command
    return this->movement;
}

/**
 * In this function the program connects as a client to the simulator.
 * It creates a socket and requests a connection with the server on local
 * host with suitable port.
 *
 * @param portInt port number.
 * @param localHost hostname describing the local computer address.
 */
void ConnectCommand::connectClient(int portInt, string localHost) {
    // Create socket
    this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        // Error
        cerr << "Could not create a socket" << endl;
        return;
    }

    // We need to create a sockaddr obj to hold address of server
    sockaddr_in address; // in means IP4
    address.sin_family = AF_INET; // IP4
    address.sin_addr.s_addr = inet_addr(localHost.c_str()); // The localhost address
    address.sin_port = htons(portInt);

    // Requesting a connection with the server on suitable local host and port
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        return;
    } else {
        cout << "Client is now connected to server" << endl;
    }
}

/**
 * This function runs in a separate thread. As long as the destructor of this class
 * has not been called, the function checks if there are messages to send to the
 * simulator, and sends them.
 */
void ConnectCommand::sendMessage() {
    string message;
    char* mesToSend;
    int is_sent;
    // Get instance of SimMessages
    SimMessages* simMessages = SimMessages::getInstance();
    // While there are still commands that have to be executed in the program
    while (!this->stop) {
        // If there are messages in the messages queue
        if (!simMessages->isEmpty()) {
            // Get the first massage of the queue
            message = simMessages->getMessage();
            mesToSend = &message[0];
            // Send the message to the simulator
            is_sent = send(this->client_socket, mesToSend, strlen(mesToSend), 0);
            if (is_sent == -1) {
                cerr << "Could not send message to server" << endl;
                return;
            }
        }
    }
}