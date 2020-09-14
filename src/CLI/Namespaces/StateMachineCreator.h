//
// Created by hp on 10.09.2020.
//

#ifndef TODOLIST_STATEMACHINECREATOR_H
#define TODOLIST_STATEMACHINECREATOR_H

#include "CLI/Controller/StateMachine.h"
#include "CLI/Model/ConsoleContext.h"
#include "Core/api/TaskServiceCreator.h"
#include "CLI/States/Command/Option.h"

namespace todo_list_CLI{
    /*
     * Generates StateMachine
     *
     * @return instance of  StateMachine.
     */
    static StateMachine createStateMachine() {

        auto ts = todo_list_Core::createService();
        auto state = std::make_unique<Option>();
        auto io = std::make_unique<ConsoleIO>();
        auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(ts)));

        return StateMachine::create(std::move(io), std::move(context), std::move(state));
    }

}

#endif //TODOLIST_STATEMACHINECREATOR_H
