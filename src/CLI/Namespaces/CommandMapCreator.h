//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_COMMANDMAPCREATOR_H
#define TODOLIST_COMMANDMAPCREATOR_H

#include "CLI/States/Command/CommandState.h"
#include "CLI/States/Command/CommandOption.h"
#include "CLI/States/Command/ViewTaskCommand.h"
#include "CLI/States/Command/EditTaskCommand.h"
#include "CLI/States/Command/AddTaskCommand.h"
#include "CLI/States/Command/AddSubtaskCommand.h"
#include "CLI/States/Command/DeleteTaskCommand.h"
#include "CLI/States/Command/CompleteTaskCommand.h"
#include "CLI/States/Command/PostponeTaskCommand.h"
#include "CLI/States/Command/ShowAllTasksCommand.h"
#include "CLI/States/Command/ShowTasksForTodayCommand.h"
#include "CLI/States/Command/ShowTasksForWeek.h"

namespace CommandMap{
    static std::map<CommandState::Type, std::unique_ptr<CommandState>> create(){

        std::map<CommandState::Type, std::unique_ptr<CommandState>> links;
        links[CommandState::Type::Option]               = std::make_unique<CommandOption>();
        links[CommandState::Type::Skip]                 = std::make_unique<CommandOption>();
        links[CommandState::Type::Edit]                 = std::make_unique<EditTaskCommand>();
        links[CommandState::Type::View]                 = std::make_unique<ViewTaskCommand>();
        links[CommandState::Type::AddTask]              = std::make_unique<AddTaskCommand>();
        links[CommandState::Type::AddSubtask]           = std::make_unique<AddSubtaskCommand>();
        links[CommandState::Type::DeleteTask]           = std::make_unique<DeleteTaskCommand>();
        links[CommandState::Type::CompleteTask]         = std::make_unique<CompleteTaskCommand>();
        links[CommandState::Type::PostponeTask]         = std::make_unique<PostponeTaskCommand>();
        links[CommandState::Type::ShowAllTasks]         = std::make_unique<ShowAllTasksCommand>();
        links[CommandState::Type::ShowAllTasksForToday] = std::make_unique<ShowTasksForTodayCommand>();
        links[CommandState::Type::ShowAllTasksForWeek]  = std::make_unique<ShowTasksForWeek>();


        return links;
    }
}
#endif //TODOLIST_COMMANDMAPCREATOR_H
