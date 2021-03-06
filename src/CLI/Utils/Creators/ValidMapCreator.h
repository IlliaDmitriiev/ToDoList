//
// Created by hp on 14.09.2020.
//

#ifndef TODOLIST_VALIDMAPCREATOR_H
#define TODOLIST_VALIDMAPCREATOR_H

#include "CLI/View/CommandStates/CommandState.h"
#include <map>

/*
 * Namespace which generates a valid map
 *
 * @author Ilya Dmitriev
 */
namespace ValidMap {

    static std::map <std::string, CommandState::Type> create() {

        std::map <std::string, CommandState::Type> links{
                {"add task", CommandState::Type::AddTask},
                {"add subtask", CommandState::Type::AddSubtask},
                {"delete task", CommandState::Type::DeleteTask},
                {"complete task", CommandState::Type::CompleteTask},
                {"postpone task", CommandState::Type::PostponeTask},
                {"show all tasks", CommandState::Type::ShowAllTasks},
                {"show all tasks for today", CommandState::Type::ShowAllTasksForToday},
                {"show all tasks for week", CommandState::Type::ShowAllTasksForWeek},
                {"view", CommandState::Type::View},
                {"edit", CommandState::Type::Edit},
                {"save", CommandState::Type::Save},
                {"load", CommandState::Type::Load},
                {"back", CommandState::Type::Skip},
                {"exit", CommandState::Type::Exit}
        };

        return links;
    }
}

#endif //TODOLIST_VALIDMAPCREATOR_H
