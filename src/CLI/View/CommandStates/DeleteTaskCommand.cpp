//
// Created by hp on 15.09.2020.
//

#include "DeleteTaskCommand.h"
#include "CLI/Utils/Creators/GraphCreator.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"

CommandState::Type DeleteTaskCommand::read(IO&) {
    return CommandState::Type::Option;
}

void DeleteTaskCommand::print(IO&) {

}

void DeleteTaskCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::delete_task::create();
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
    auto result = service.deleteTask(tasks[params.id_ - 1].getId());
    if (result.result == ResultType::FAILURE) {
        io.output(result.error_message + "\n");
        return;
    }
    io.output("Task deleted successfully\n");
}

std::unique_ptr<CommandState> DeleteTaskCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
