//
// Created by hp on 07.09.2020.
//

#include "CommandOption.h"
#include "ViewTaskCommand.h"
#include "CLI/Namespaces/Validate.h"

CommandState::Type CommandOption::read(IO& io) {
    return validate::make(io.input());
}

void CommandOption::print(IO& io) {
    io.output("Available commands:\nadd task\nadd subtask\ndelete task\n"
              "complete task\npostpone task\nshow all tasks\nshow all tasks for today\n"
              "show all tasks for week\nexit\nWrite any command.\n");
}

void CommandOption::execute(IO&, Context&) {

}

std::unique_ptr<CommandState> CommandOption::change(CommandState::Type type){
    if (type == CommandState::Type::ShowAllTasks
     || type == CommandState::Type::ShowAllTasksForToday
     || type == CommandState::Type::ShowAllTasksForWeek) {return std::make_unique<ViewTaskCommand>();}
    else {return std::make_unique<CommandOption>();}
}

