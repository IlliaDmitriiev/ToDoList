//
// Created by hp on 13.09.2020.
//

#include "EditTaskCommand.h"
#include "CommandOption.h"
#include "CLI/Namespaces/Validate.h"
#include "CLI/Namespaces/GraphCreator.h"

CommandState::Type EditTaskCommand::read(IO& io){
    return validate::make(io.input());
}

void EditTaskCommand::print(IO& io){
    io.output("Available commands:\nedit\nback\nExample of input: edit\n");
}

void EditTaskCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::add_subtask::create();
    auto buffer = ParameterStorage::create();

    ParseMachine pm(io, buffer, ParseState::Type::ID, links);
    pm.run();

    auto &service = context.getService();
    auto &tasks = context.getTaskList();
    auto params = buffer.getParameters() ;
    if (tasks.size() < params.id_){
        io.output("There isn't task with such id!\n");
        return;
    }
    auto result = service.editTask(
            tasks[params.id_ - 1].getId(),
            TaskDTO::create(params.date_, params.name_, params.label_, params.priority_));

    if (result.result == ResultType::FAILURE) {
        io.output(result.error_message + "\n");
        return;
    }
    io.output("Task edited successfully\n");

}

std::unique_ptr<CommandState> EditTaskCommand::change(CommandState::Type){
    return std::make_unique<CommandOption>();
}