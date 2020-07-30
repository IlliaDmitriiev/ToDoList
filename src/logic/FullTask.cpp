//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "FullTask.h"

FullTask FullTask::create(IDGenerator &generator, const Task &t){
    FullTask ft(TaskID::create(generator.generateId()), t);
    return ft;
}

void FullTask::addSubtask(TaskID subtaskID, std::weak_ptr<FullTask> ft){
    subtasks.insert({subtaskID, ft});
}

void FullTask::removeSubtasks( std::unordered_map<TaskID, std::shared_ptr<FullTask> > &allTasks){

    for (auto i: subtasks){
        if (!i.second.expired())
            i.second.lock()->removeSubtasks(allTasks);

        allTasks[i.first].reset();
        i.second.reset();
        allTasks.erase(i.first);
    }

    subtasks.clear();
}

const Task &FullTask::getTask() const {
    return t;
}

