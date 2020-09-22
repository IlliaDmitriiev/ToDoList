//
// Created by hp on 14.09.2020.
//

#include "ViewTaskCommand.h"
#include "CommandOption.h"
#include "CLI/Namespaces/GraphCreator.h"

CommandState::Type ViewTaskCommand::read(IO& io) {
    return CommandState::Type::View;
}

void ViewTaskCommand::print(IO& io){
}

void ViewTaskCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::complete_task::create();
    auto buffer = ParameterStorage::create();

    ParseMachine pm(io, buffer, ParseState::Type::ID, links);
    pm.run();

    auto &service = context.getService();
    auto &tasks = context.getTaskList();
    auto params = buffer.getParameters();

    if (tasks.size() < params.id_){
        io.output("There isn't task with such id!\n");
        return;
    }
    auto task = tasks[params.id_ - 1];
    io.output("Task: (\n"
               "    Name: [" + task.getName()+ "]\n"
               "    Label: [" + task.getLabel()+"]\n"
               "    Date: [" + to_simple_string(task.getDate())+"]\n"
               "    Priority: [" + std::to_string((int)task.getPriority()) + "]\n"
               "    Completed: [" + (task.isCompleted()?"True":"False") +"]);\n");


    auto vector = service.getSubtasks(tasks[params.id_ - 1].getId());
    for (auto & i : vector){
        io.output("Subtask: { Name: [" + i.getName() + "] Date: ["
                   + to_simple_string(i.getDate()) + "] }\n");
    }
}

std::unique_ptr<CommandState> ViewTaskCommand::change(CommandState::Type type) {
    return std::make_unique<CommandOption>();
}
