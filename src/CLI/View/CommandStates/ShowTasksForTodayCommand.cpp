//
// Created by hp on 15.09.2020.
//

#include "ShowTasksForTodayCommand.h"
#include "CLI/Utils/Creators/GraphCreator.h"
#include "ViewTaskCommand.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"

CommandState::Type ShowTasksForTodayCommand::read(IO&) {
    return CommandState::Type::Submenu;
}

void ShowTasksForTodayCommand::print(IO&) {

}

void ShowTasksForTodayCommand::execute(IO& io, Context& context) {
    auto &service = context.getService();
    auto &vector = context.getTaskList();
    vector = service.getTasksForToday();


    io.output("Tasks for today:\n");
    for (int i = 0; i<vector.size(); ++i){
        io.output("{ Number: ["+std::to_string(i + 1) + "] Name: [" +
                   vector[i].getName() + "] Date: ["
                   + to_simple_string(vector[i].getDate()) + "] }\n");
    }
}

std::unique_ptr<CommandState> ShowTasksForTodayCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
