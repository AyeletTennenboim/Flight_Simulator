#include "OpenServerCommand.h"
#include "../Maps/SimMap.h"
#include "../Expressions/Expression.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <regex>

using namespace std;

/// Constructor
OpenServerCommand::OpenServerCommand() {}

/**
 * Destructor:
 * The destructor stops the while loop in readLineByLine function, closes the
 * socketfd and executes the thread's join() function.
 */
OpenServerCommand::~OpenServerCommand() {
    // Stop the endless while loop that thread1 is running in readLineByLine function
    this->stop = true;
    // Close the socket
    close(this->socketfd);
    // Execute join() function
    if (this->thread1.joinable()) {
        this->thread1.join();
    }
}

/**
 * The function is activated by a thread that runs a server that listens to the
 * simulator and reads values line by line in a while loop. The tempo is
 * controlled by the simulator that connects to the program as a client and writes
 * to the program line by line.
 * The program stores the sampled values in SimMap from which it can get the updated
 * value of a variable in O(1) time complexity.
 *
 * @param client_socket client that server accepted and listens to.
 */
void OpenServerCommand::readLineByLine(int client_socket) {
    try {
        SimMap* simMap = SimMap::getInstance();
        string str = "";
        // While the destructor doesn't called
        while (!this->stop) {
            char buffer[500] = {0};
            // Read from client
            read(client_socket, buffer, 500);
            // Convert to string
            string bufferStr = buffer;
            // Concatenate the rest of the string from the previous iteration to the string from the current iteration
            str = str + bufferStr;
            // Separate from the union string the first 36 values, until finding newline
            string token1 = str.substr(0, str.find("\n"));
            // Save the rest of the string to the next iteration
            string token2 = str.substr(str.find("\n") + 1, str.length());
            regex regex(",");
            // Separate the 36 values by ',' and put them in vector
            vector<string> out(
                    sregex_token_iterator(token1.begin(), token1.end(), regex, -1),
                    sregex_token_iterator()
            );
            // Set the 36 variables in simMap with the values received from the simulator
            simMap->setValue("/instrumentation/airspeed-indicator/indicated-speed-kt", out[0]);
            simMap->setValue("/sim/time/warp", out[1]);
            simMap->setValue("/controls/switches/magnetos", out[2]);
            simMap->setValue("/instrumentation/heading-indicator/offset-deg",out[3]);
            simMap->setValue("/instrumentation/altimeter/indicated-altitude-ft", out[4]);
            simMap->setValue("/instrumentation/altimeter/pressure-alt-ft", out[5]);
            simMap->setValue("/instrumentation/attitude-indicator/indicated-pitch-deg",out[6]);
            simMap->setValue("/instrumentation/attitude-indicator/indicated-roll-deg", out[7]);
            simMap->setValue("/instrumentation/attitude-indicator/internal-pitch-deg", out[8]);
            simMap->setValue("/instrumentation/attitude-indicator/internal-roll-deg", out[9]);
            simMap->setValue("/instrumentation/encoder/indicated-altitude-ft", out[10]);
            simMap->setValue("/instrumentation/encoder/pressure-alt-ft", out[11]);
            simMap->setValue("/instrumentation/gps/indicated-altitude-ft", out[12]);
            simMap->setValue("/instrumentation/gps/indicated-ground-speed-kt", out[13]);
            simMap->setValue("/instrumentation/gps/indicated-vertical-speed", out[14]);
            simMap->setValue("/instrumentation/heading-indicator/indicated-heading-deg", out[15]);
            simMap->setValue("/instrumentation/magnetic-compass/indicated-heading-deg", out[16]);
            simMap->setValue("/instrumentation/slip-skid-ball/indicated-slip-skid", out[17]);
            simMap->setValue("/instrumentation/turn-indicator/indicated-turn-rate", out[18]);
            simMap->setValue("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", out[19]);
            simMap->setValue("/controls/flight/aileron", out[20]);
            simMap->setValue("/controls/flight/elevator", out[21]);
            simMap->setValue("/controls/flight/rudder", out[22]);
            simMap->setValue("/controls/flight/flaps", out[23]);
            simMap->setValue("/controls/engines/engine/throttle", out[24]);
            simMap->setValue("/controls/engines/current-engine/throttle", out[25]);
            simMap->setValue("/controls/switches/master-avionics",out[26]);
            simMap->setValue("/controls/switches/starter", out[27]);
            simMap->setValue("/engines/active-engine/auto-start", out[28]);
            simMap->setValue("/controls/flight/speedbrake", out[29]);
            simMap->setValue("/sim/model/c172p/brake-parking", out[30]);
            simMap->setValue("/controls/engines/engine/primer", out[31]);
            simMap->setValue("/controls/engines/current-engine/mixture", out[32]);
            simMap->setValue("/controls/switches/master-bat", out[33]);
            simMap->setValue("/controls/switches/master-alt", out[34]);
            simMap->setValue("/engines/engine/rpm", out[35]);
            // Clear the vector for the next iteration
            out.clear();
            // Save the rest of the union string (without the 36 first values) in str
            // so it will be unioned to the buffer in the next iteration
            str = token2;
        }
    } catch (exception e) {
        // Close the listening socket
        close(this->socketfd);
    }
}

/**
 * The function receives port from the lexer's vector, creates a socket,
 * binds socket to IP address, makes socket listen to port, accepts a client,
 * calls to function that opens thread and returns number of steps needed to be
 * passed on the vector till the next command.
 *
 * @param strArr vector of strings received from the lexer.
 * @param index current position on the strArr vector.
 * @return number of steps needed to be passed on the vector till the next command.
 */
int OpenServerCommand::execute(vector<string> &strArr, int index) {
    int portInt;
    Interpreter* i = nullptr;
    Expression* ex = nullptr;
    // Interpret and calculate the port string received from lexer's vector
    try {
        i = new Interpreter();
        ex = i->interpret(strArr[index + 1]);
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

    // Create socket
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd == -1) {
        // Error
        cerr << "Could not create a socket" << endl;
        exit(-1);
    }

    // Bind socket to IP address.
    // We first need to create the sockaddr obj.
    sockaddr_in address; // In means IP4
    address.sin_family = AF_INET;
    // Give me any IP allocated for my machine
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portInt);

    // Bind command
    if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        // Error
        cerr << "Could not bind the socket to an IP" << endl;
        exit(-2);
    }

    // Make socket listen to the port
    if (listen(this->socketfd, 5) == -1) {
        // Error
        cerr << "Error during listening command" << endl;
        exit(-3);
    } else {
        cout << "Server is now listening ..." << endl;
    }

    // Accept a client
    int client_socket = accept(this->socketfd, (struct sockaddr *) &address,
                               (socklen_t*) &address);
    if (client_socket == -1) {
        // Error
        cerr << "Error accepting client" << endl;
        exit(-4);
    }
    // Call a function that opens thread1 that runs readLineByLine function
    startThread(client_socket);
    // Return number of steps needed to be passed on the vector till the next command
    return this->movement;
}

/**
 * The function open a thread that runs the readLineByLine function.
 *
 * @param client_socket client that the server accepts and listens to.
 */
void OpenServerCommand::startThread(int client_socket) {
    // Open a thread that runs the readLineByLine function
    this->thread1 = thread(&OpenServerCommand::readLineByLine, this, client_socket);
}