//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "FullTask.h"

FullTask FullTask::create(IDGenerator &generator, const Task &task){
    FullTask ft(generator.generateId(), task);
    return ft;
}

void FullTask::Print(const std::weak_ptr<FullTask> &t){
    Task task = t.lock()->getTask();
    Date date = task.getDate();
    std::string label = task.getLabel();
    std::string name =  task.getName();
    Task::Priority prior = task.getPrior();

    std::cout <<"TASK(\n     date: ";
    Date::Print(date);
    std::cout<<"     name: "
             << name<<"\n     label: "<<label<<"\n";
    if (Task::Priority::First ==  prior) std::cout <<"     priority: First\n);\n";
    else if (Task::Priority::Second ==  prior) std::cout <<"     priority: Second\n);\n";
    else if (Task::Priority::Third ==  prior) std::cout <<"     priority: Third\n);\n";
    else if (Task::Priority::None ==  prior) std::cout <<"     priority: None\n);\n";
}

void FullTask::addSubtask(TaskID subtaskID, std::weak_ptr<FullTask> ft){
    subtasks_.insert({subtaskID, ft});
}

void FullTask::removeSubtasks( std::unordered_map<TaskID, std::shared_ptr<FullTask>, TaskID::Hasher, TaskID::Comparator> &allTasks){

    for (auto i: subtasks_){
        if (!i.second.expired())
            i.second.lock()->removeSubtasks(allTasks);

        allTasks[i.first].reset();
        i.second.reset();
        allTasks.erase(i.first);
    }

    subtasks_.clear();
}

const Task &FullTask::getTask() const {
    return task_;
}

FullTask::FullTask(TaskID ID, const Task &t) : id_(ID), task_(t) {}

