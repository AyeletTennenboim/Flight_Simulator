cmake_minimum_required(VERSION 3.15)
project(flight_simulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(flight_simulator main.cpp RunTheSimulator/RunTheSimulator.cpp RunTheSimulator/RunTheSimulator.h Commands/Command.h Commands/OpenServerCommand.cpp Commands/OpenServerCommand.h Commands/ConnectCommand.cpp Commands/ConnectCommand.h Commands/DefineVarCommand.cpp Commands/DefineVarCommand.h Commands/PrintCommand.cpp Commands/PrintCommand.h Commands/SleepCommand.cpp Commands/SleepCommand.h Commands/ConditionParser.h Commands/IfCommand.cpp Commands/IfCommand.h Commands/LoopCommand.cpp Commands/LoopCommand.h Expressions/Expression.cpp Expressions/Expression.h Maps/SymbolTable.cpp Maps/SymbolTable.h Commands/ConditionParser.cpp Maps/CommandsMap.cpp Maps/CommandsMap.h Maps/Var.cpp Maps/Var.h Maps/SimMap.cpp Maps/SimMap.h Maps/SimMessages.cpp Maps/SimMessages.h)
target_link_libraries(${PROJECT_NAME} pthread)