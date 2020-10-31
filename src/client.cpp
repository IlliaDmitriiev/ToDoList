//
// Created by ilya on 25.10.2020.
//
#include "CLI/Utils/Creators/StateMachineCreator.h"

int main() {
    auto sm = todo_list_CLI::createStateMachine();
    sm.run();
    return 0;
}
