//
// Created by hp on 07.09.2020.
//

#include "Option.h"
#include "View.h"
#include "Validate.h"

CommandState::Type Option::read(IO& io) {
    return validate::make(io.input());
}

void Option::print(IO& io) {
    io.output("Available commands:\nadd task\nadd subtask\ndelete task\n"
              "complete task\npostpone task\nshow all tasks\nshow all tasks for today\n"
              "show all tasks for week\nexit\nWrite any command.\n");
}

std::unique_ptr<CommandState> Option::change(CommandState::Type type){
    if (type == CommandState::Type::ShowAllTasks
     || type == CommandState::Type::ShowAllTasksForToday
     || type == CommandState::Type::ShowAllTasksForWeek) {return std::make_unique<View>();}
    else {return std::make_unique<Option>();}
}

