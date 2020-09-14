#include <iostream>
#include "CLI/Controller/StateMachineCreator.h"

int main() {
    auto sm = todo_list_CLI::createStateMachine();
    sm.start();
    return 0;
}
