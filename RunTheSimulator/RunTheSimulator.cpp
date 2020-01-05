#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include "RunTheSimulator.h"
#include "../Commands/Command.h"
#include "../Maps/CommandsMap.h"
#include "../Maps/SymbolTable.h"
#include "../Maps/SimMap.h"

using namespace std;

/// Constructor
RunTheSimulator::RunTheSimulator() {}

/// Destructor
RunTheSimulator::~RunTheSimulator() {}

/**
 * The function reads a file containing code
 * and returns an array of strings of the separated code.
 *
 * @param file a file containing code.
 * @return a vector of strings of the separated code.
 */
vector<string> RunTheSimulator::lexer(string file) {
    vector<string> dataFile;
    ifstream flyFile(file);
    // Read from file
    if (flyFile.is_open()) {
        string line;
        // Read line by line and separate the strings as defined
        while (getline(flyFile, line)) {
            // Find location of first letter in the line
            size_t pos = line.find_first_not_of("\t ");
            // Delete all characters before the first letter
            line.erase(0, pos);

            // Print command
            if (line.find("Print") != string::npos) {
                // Find location of the first '('
                pos = line.find_first_of('(');
                if (pos != string::npos) {
                    // Change '(' by '\t'
                    line[pos] = '\t';
                }
                // Find location of the first ')'
                pos = line.find_last_of(')');
                if (pos != string::npos) {
                    // Change ')' by '\t'
                    line[pos] = '\t';
                }
                regex regex("\t");
                vector<string> out(
                        sregex_token_iterator(line.begin(), line.end(), regex, -1),
                        sregex_token_iterator());
                for (auto &s: out) {
                    if (s != "") {
                        dataFile.push_back(s);
                    }
                }
            // Var command
            } else if (line.find("var") != string::npos) {
                // Variable that does not affect and is not affected by the simulator
                if (line.find("=") != string::npos) {
                    char *token = strtok(&line[0], "=");
                    string str = string(token);
                    regex regex(" |\t");
                    vector<string> out(
                            sregex_token_iterator(str.begin(), str.end(), regex, -1),
                            sregex_token_iterator());
                    out.push_back("=");
                    token = strtok(NULL, "=");
                    str = string(token);
                    str.erase(remove(str.begin(), str.end(), ' '), str.end());
                    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
                    out.push_back(str);
                    for (auto &s: out) {
                        if (s != "") {
                            dataFile.push_back(s);
                        }
                    }
                // A variable that updates the simulator
                } else if (line.find("->") != string::npos) {
                    char *token = strtok(&line[0], "->");
                    string str = string(token);
                    regex regex("\\(|\\)|,|\t|\n| |\"");
                    vector<string> out(
                            sregex_token_iterator(str.begin(), str.end(), regex, -1),
                            sregex_token_iterator());
                    token = strtok(NULL, "\n");
                    string str2 = string(token);
                    str2.erase(0, 1);
                    vector<string> out2(
                            sregex_token_iterator(str2.begin(), str2.end(), regex, -1),
                            sregex_token_iterator());
                    for (auto &s : out) {
                        if (s != "") {
                            dataFile.push_back(s);
                        }
                    }
                    dataFile.push_back(("->"));
                    for (auto &s : out2) {
                        if (s != "") {
                            dataFile.push_back(s);
                        }
                    }
                // A variable that is updated by the simulator
                } else if (line.find("<-") != string::npos) {
                    char *token = strtok(&line[0], "<-");
                    string str = string(token);
                    regex regex("\\(|\\)|,|\t|\n| |\"");
                    vector<string> out(
                            sregex_token_iterator(str.begin(), str.end(), regex, -1),
                            sregex_token_iterator());
                    token = strtok(NULL, "\n");
                    string str2 = string(token);
                    str2.erase(0, 1);
                    vector<string> out2(
                            sregex_token_iterator(str2.begin(), str2.end(), regex, -1),
                            sregex_token_iterator());
                    for (auto &s : out) {
                        if (s != "") {
                            dataFile.push_back(s);
                        }
                    }
                    dataFile.push_back(("<-"));
                    for (auto &s : out2) {
                        if (s != "") {
                            dataFile.push_back(s);
                        }
                    }
                }
            // Set an existing variable's value
            } else if (line.find("=") != string::npos && (line.find("while") == string::npos &&
                        line.find("if") == string::npos && line.find("var") == string::npos)) {
                line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                char *token = strtok(&line[0], "=");
                string str = string(token);
                dataFile.push_back(str);
                dataFile.push_back("=");
                token = strtok(NULL, "=");
                str = string(token);
                dataFile.push_back(str);
            // If and While commands
            } else if ((line.find("while") != string::npos) || (line.find("if") != string::npos)) {
                char *token = strtok(&line[0], " ");
                string str = string(token);
                dataFile.push_back(str);
                token = strtok(NULL, "\n");
                string str2 = string(token);
                str2.erase(remove(str2.begin(), str2.end(), '\t'), str2.end());
                str2.erase(remove(str2.begin(), str2.end(), ' '), str2.end());
                if (line.find(">=") != string::npos || line.find("<=") != string::npos ||
                    line.find("==") != string::npos || line.find("!=") != string::npos) {
                    regex regex("==|>=|<=|!=|\\{");
                    vector<string> out(
                            sregex_token_iterator(str2.begin(), str2.end(), regex, {-1, 0}),
                            sregex_token_iterator());
                    for (auto &s : out) {
                        if (s != "") {
                            dataFile.push_back(s);
                        }
                    }
                } else {
                    regex regex(">|<|\\{");
                    vector<string> out(
                            sregex_token_iterator(str2.begin(), str2.end(), regex, {-1, 0}),
                            sregex_token_iterator());
                    for (auto &s : out) {
                        if (s != "") {
                            dataFile.push_back(s);
                        }
                    }
                }
            // Other commands
            } else {
                regex regex(",|\t|\n|\"| ");
                // Find location of the first '('
                size_t found = line.find_first_of('(');
                if (found != string::npos) {
                    // Change '(' by ','
                    line[found] = ',';
                }
                // Find location of the first ')'
                found = line.find_last_of(')');
                if (found != string::npos) {
                    // Change ')' by ','
                    line[found] = ',';
                }
                line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                vector<string> out(
                        sregex_token_iterator(line.begin(), line.end(), regex, -1),
                        sregex_token_iterator());
                for (auto &s : out) {
                    if (s != "") {
                        dataFile.push_back(s);
                    }
                }
            }
        }
        // Close the file
        flyFile.close();
        return dataFile;
    // If the file can't be opened
    } else {
        // Print message
        cout << "Error opening file" << endl;
        exit(-1);
    }
}

/**
 * The function goes over all the strings in the array received from the lexer,
 * extracts from the CommandsMap a command object according to the string,
 * and calls its execute() function that executes the command.
 *
 * @param strArr vector of strings received from the lexer.
 */
void RunTheSimulator::parser(vector<string> strArr) {
    int arr_size = strArr.size();
    int index = 0;
    // Get instances of all maps
    CommandsMap* commandsMap = CommandsMap::getInstance();
    SymbolTable* symbolTable = SymbolTable::getInstance();
    SimMap* simMap = SimMap::getInstance();
    // Go over the array created by the lexer
    while (index < arr_size) {
        // If the command exists in the CommandsMap
        if (commandsMap->isCommandExists(strArr[index])) {
            // Get the appropriate command
            Command *c = commandsMap->getCommand(strArr[index]);
            index += c->execute(strArr, index);
        // Update a variable value
        } else {
            symbolTable->getVarObject(strArr[index])->setValue((strArr[index + 2]));
            index += 3;
        }
    }
    // Free memory
    delete commandsMap;
    delete symbolTable;
    delete simMap;
}