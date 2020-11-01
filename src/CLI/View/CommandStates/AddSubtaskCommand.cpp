//
// Created by hp on 15.09.2020.
//

#include "AddSubtaskCommand.h"
#include "CLI/Utils/Creators/GraphCreator.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"

CommandState::Type AddSubtaskCommand::read(IO&) {
    return CommandState::Type::Option;
}

void AddSubtaskCommand::print(IO&) {

}

void AddSubtaskCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::add_subtask::create();
    auto buffer = ParameterStorage::create();

    ParseMachine pm(io, buffer, ParseState::Type::ID, links);
    pm.run();

    auto &service = context.getService();
    auto &tasks = context.getTaskList();
    auto params = buffer.getParameters();

    if (tasks.size() < params.id_){
        io.output("There isn't root task with such id!\n");
        return;
    }
    auto result = service.addSubtask(tasks[params.id_ - 1].getId(),
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
    io.output("Subtask added successfully\n");
}

std::unique_ptr<CommandState> AddSubtaskCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
