# **Flight Simulator**

This program created by Ayelet Tennenboim and May Bachar for Advance Programming course in Bar Ilan university.

## Authors
**Ayelet Tennenboim**

     - ID: 209026517
     - Submit name: tennena
     
**May Bachar**

     - ID: 313370876
     - Submit name: bacharm3

## Intrudoction
This program interprets code that allows remote control of flight simulator. This project in an advanced programming course is a showcase to our programming experience. The project contains the following elements: use of design and architectural templates, communication and server architecture, use of databases, data streaming, comparison, selection and implementation of algorithms within the system we create and parallel programming using Threads.

In addition, we learned about team work.

## Description
The program receives a text file containing code with commands for the airplane.
Using the lexer function, the program reads the file and decomposes the code into an array of strings. Using a Command Pattern and hash map, the program associates a string with a specific command object that will be executed later (time complexity of extracting an object from the map is O(1)).

At first, the program executes Open Server command that runs in the background and reads line by line from the simulator. The simulator connects to the program as a client and passes values of variables defined in the "generic_small.xml" file‬‬. The values are stored on hash map so the program can extracts the most updated value of a variable in O(1) time complexity.

Then, in a separated thread, the program executes another command and connects as a client to the simulator, so later it could send flight instructions to the simulator.

Thereafter, the program defines variables which will be used during the program. The variables are stored on on another map called "‫‪Symbol‬‬ Table‬‬". This map links the variable's name to a variable object that contains information about the variable.

The program supports openning data server, connecting to client and defining variables as described above. In addition, it supports print command, sleep command, while loops and if conditions.

The program executes all of these commands in order to control the flight simulator.

## Start Running
* Download FlightGear Simulator - link in the list of attached links below.
* In the main menu of flight gear, access the settings and add the following 	settings in "‫‪Additional‬‬ ‫‪Settings‬‬":
--telnet=socket,in,10,127.0.0.1,5402,tcp
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
* Compile the program in the linux terminal:
g++ -std=c++14 */*.cpp *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
* Run the program with a text file:
./a.out file_name.txt
* Press "Fly!" on flight gear simulator for connection.

# Files
* main.cpp

#### RunTheSimulator files
* RunTheSimulator.cpp
* RunTheSimulator.h

#### Maps files
* CommandsMap.cpp
* CommandsMap.h
* SimMap.cpp
* SimMap.h
* SimMessages.cpp
* SimMessages.h
* SymbolTable.cpp
* SymbolTable.h
* Var.cpp
* Var.h

#### Expressions files
* Expression.cpp
* Expression.h

#### Commands files
* Command.h
* ConditionParser.cpp
* ConditionParser.h
* ConnectCommand.cpp
* ConnectCommand.h
* DefineVarCommand.cpp
* DefineVarCommand.h
* IfCommand.cpp
* IfCommand.h
* LoopCommand.cpp
* LoopCommand.h
* OpenServerCommand.cpp
* OpenServerCommand.h
* PrintCommand.cpp
* PrintCommand.h
* SleepCommand.cpp
* SleepCommand.h

## Text Files
* fly.txt

## Links
* Download FlightGear Simulator:
https://www.flightgear.org/download/
