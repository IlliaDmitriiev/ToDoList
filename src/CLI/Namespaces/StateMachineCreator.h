//
// Created by hp on 10.09.2020.
//

#ifndef TODOLIST_STATEMACHINECREATOR_H
#define TODOLIST_STATEMACHINECREATOR_H

#include "CLI/Controller/StateMachine.h"
#include "CLI/Model/ConsoleContext.h"
#include "CLI/Proxy/ClientServer.h"
#include "CLI/States/Command/CommandOption.h"
#include "TaskService.grpc.pb.h"

namespace todo_list_CLI{
    /*
     * Generates StateMachine
     *
     * @return instance of  StateMachine.
     */
    static StateMachine createStateMachine() {
        std::string server_address("0.0.0.0:50051");
        auto channel = grpc::CreateChannel(
                server_address, grpc::InsecureChannelCredentials());
        auto ts = std::make_unique<ClientServer>(std::move(channel));
        auto state = std::make_unique<CommandOption>();
        auto io = std::make_unique<ConsoleIO>();
        auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(ts)));

        return StateMachine::create(std::move(io), std::move(context), std::move(state));
    }

}

#endif //TODOLIST_STATEMACHINECREATOR_H
