//
// Created by hp on 15.09.2020.
//

#include "ShowTasksForWeek.h"
#include "CLI/Namespaces/GraphCreator.h"
#include "ViewTaskCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"

CommandState::Type ShowTasksForWeek::read(IO&) {
    return CommandState::Type::View;
}

void ShowTasksForWeek::print(IO&) {

}

void ShowTasksForWeek::execute(IO& io, Context& context) {
    auto &service = context.getService();
    auto &vector = context.getTaskList();
    vector = service.getTasksForWeek();

    io.output("Tasks for this week:\n");
    for (int i = 0; i<vector.size(); ++i){
        io.output("{ Number: ["+std::to_string(i + 1) + "] Name: [" +
                   vector[i].getName() + "] Date: ["
                   + to_simple_string(vector[i].getDate()) + "] }\n");
    }
}

std::unique_ptr<CommandState> ShowTasksForWeek::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
