//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_STORAGEMOCK_H
#define TODOLIST_STORAGEMOCK_H

#include <gmock/gmock.h>
#include "Core/model/TaskStorage.h"

class MockStorage : public TaskStorageInterface {

public:
    MOCK_METHOD(std::optional<std::weak_ptr<FullTask>>, getTask, (TaskID), (override));
    MOCK_METHOD(bool, addTask, (std::shared_ptr<FullTask>), (override));
    MOCK_METHOD(bool, deleteTask, (TaskID), (override));
    MOCK_METHOD(bool, deleteSubtaskInParent, (TaskID, TaskID), (override));
    MOCK_METHOD(std::vector<std::weak_ptr<FullTask>>, getAllTasks,(),(override));
};

#endif //TODOLIST_STORAGEMOCK_H
