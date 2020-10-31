//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_COMMANDMAPCREATOR_H
#define TODOLIST_COMMANDMAPCREATOR_H

#include "CLI/View/CommandStates/CommandState.h"
#include "CLI/View/CommandStates/CommandOption.h"
#include "CLI/View/CommandStates/SubmenuCommand.h"
#include "CLI/View/CommandStates/ViewTaskCommand.h"
#include "CLI/View/CommandStates/EditTaskCommand.h"
#include "CLI/View/CommandStates/SaveCommand.h"
#include "CLI/View/CommandStates/LoadCommand.h"
#include "CLI/View/CommandStates/AddTaskCommand.h"
#include "CLI/View/CommandStates/AddSubtaskCommand.h"
#include "CLI/View/CommandStates/DeleteTaskCommand.h"
#include "CLI/View/CommandStates/CompleteTaskCommand.h"
#include "CLI/View/CommandStates/PostponeTaskCommand.h"
#include "CLI/View/CommandStates/ShowAllTasksCommand.h"
#include "CLI/View/CommandStates/ShowTasksForTodayCommand.h"
#include "CLI/View/CommandStates/ShowTasksForWeek.h"

namespace CommandMap{
    static std::map<CommandState::Type, std::unique_ptr<CommandState>> create(){

        std::map<CommandState::Type, std::unique_ptr<CommandState>> links;
        links[CommandState::Type::Option]               = std::make_unique<CommandOption>();
        links[CommandState::Type::Submenu]              = std::make_unique<SubmenuCommand>();
        links[CommandState::Type::Skip]                 = std::make_unique<CommandOption>();
        links[CommandState::Type::Save]                 = std::make_unique<SaveCommand>();
        links[CommandState::Type::Load]                 = std::make_unique<LoadCommand>();
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
