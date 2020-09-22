#include "CLI/Namespaces/StateMachineCreator.h"

int main() {
    auto sm = todo_list_CLI::createStateMachine();
    sm.run();
    return 0;
}
