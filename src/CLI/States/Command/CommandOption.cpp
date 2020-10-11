//
// Created by hp on 07.09.2020.
//

#include "CommandOption.h"
#include "ViewTaskCommand.h"
#include "CLI/Namespaces/Validate.h"
#include "CLI/Namespaces/CommandMapCreator.h"

CommandState::Type CommandOption::read(IO& io) {
    return validate::make(io.input());
}

void CommandOption::print(IO& io) {
    io.output("Available commands:\nadd task\nadd subtask\ndelete task\n"
              "complete task\npostpone task\nshow all tasks\nshow all tasks for today\n"
              "show all tasks for week\nsave\nload\nexit\nWrite any command.\n");
}

void CommandOption::execute(IO&, Context&) {

}

std::unique_ptr<CommandState> CommandOption::change(CommandState::Type type){
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}

