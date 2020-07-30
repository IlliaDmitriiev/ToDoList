//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "StorageByDate.h"

void StorageByDate::addTask(const FullTask& ft, Task::Priority prior, TaskID id){

    auto cur = std::make_shared<FullTask>(ft);
    Date date = ft.getTask().getDate();
    auto founddDate = mp.find(date);

    if (founddDate != mp.end())
        foundDate->second.putTaskInRightPlace(cur, prior);
    else {
        StorageByPrior  v;
        v.putTaskInRightPlace(cur, prior);
        mp.insert({date, v});
    }

    allTasks.insert({id.getId(), std::move(cur)});
}


void StorageByDate::removeTask(TaskID taskID){
    allTasks[taskID.getId()]->removeSubtasks(allTasks);
    allTasks[taskID.getId()].reset();
    allTasks.erase(taskID.getId());
}

const std::unordered_map<Date, DataVectorsLogic , Date::Hasher, Date::Comparator> &StorageByDate::getMp() const {
    return mp;
}


