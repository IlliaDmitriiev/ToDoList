//
// Created by hp on 15.09.2020.
//

#include "AddTaskCommand.h"
#include "CLI/Utils/Creators/GraphCreator.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"

CommandState::Type AddTaskCommand::read(IO&) {
    return CommandState::Type::Option;
}

void AddTaskCommand::print(IO&) {

}

void AddTaskCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::add_task::create();
    auto buffer = ParameterStorage::create();

    ParseMachine pm(io, buffer, ParseState::Type::Name, links);
    pm.run();

    auto params = buffer.getParameters();
    auto &service = context.getService();
    auto result = service.addTask(
            TaskDTO::create(TaskID::create(0),
                            params.date_,
                            params.name_,
                            params.label_,
                            params.priority_,
                            false));

    if (result.result == ResultType::FAILURE) {
        io.output(result.error_message + "\n");
        return;
    }
    io.output("Task added successfully\n");
}

std::unique_ptr<CommandState> AddTaskCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
