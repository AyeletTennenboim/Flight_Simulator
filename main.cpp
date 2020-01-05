#include <string>
#include "Commands/Command.h"
#include "RunTheSimulator/RunTheSimulator.h"

using namespace std;

/**
 * This function is responsible for running the program.
 *
 * @param argc number of command line arguments.
 * @param argv command line arguments.
 * @return 0
 */
int main(int argc, char *argv[]) {
    (void) argc;
    string file = argv[1];
    // Create new RunTheSimulator
    RunTheSimulator *simulator = new RunTheSimulator();
    // Separate the code contained in the file into a vector of strings
    vector<string> dataFile = simulator->lexer(file);
    // Execute the file commands
    simulator->parser(dataFile);
    return 0;
}