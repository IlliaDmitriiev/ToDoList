//
// Created by hp on 15.09.2020.
//

#include "CompleteTaskCommand.h"
#include "CLI/Namespaces/GraphCreator.h"
#include "CLI/Namespaces/CommandMapCreator.h"

CommandState::Type CompleteTaskCommand::read(IO&) {
    return CommandState::Type::Option;
}

void CompleteTaskCommand::print(IO&) {

}

void CompleteTaskCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::complete_task::create();
    auto buffer = ParameterStorage::create();

    ParseMachine pm(io, buffer, ParseState::Type::ID, links);
    pm.run();

    auto &service = context.getService();
    auto &tasks = context.getTaskList();
    auto params = buffer.getParameters();

    if (tasks.size() < params.id_) {
        io.output("There isn't task with such id!\n");
        return;
    }
    auto result = service.complete(tasks[params.id_ - 1].getId());
    if (result.result == ResultType::FAILURE) {
        io.output(result.error_message + "\n");
        return;
    }
    io.output("Task completed successfully\n");
}

std::unique_ptr<CommandState> CompleteTaskCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
