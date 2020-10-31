//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_MODELMOCK_H
#define TODOLIST_MODELMOCK_H

#include <gmock/gmock.h>
#include "Core/model/DataInterface.h"

class DataMock : public DataInterface {

public:
    MOCK_METHOD(AddTaskResult, addTask,(const ModelTaskDTO &taskDto), (override));
    MOCK_METHOD(AddTaskResult, addSubtask,(TaskID taskID, const ModelTaskDTO &subtask), (override));
    MOCK_METHOD(RequstTaskResult, deleteTask,(TaskID id), (override));
    MOCK_METHOD(RequstTaskResult, complete,(TaskID id), (override));
    MOCK_METHOD(RequstTaskResult, editTask,(TaskID id, const ModelTaskDTO &subtask), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getSubtasks,(TaskID id), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getAllTasks,(), (override));
    MOCK_METHOD(std::optional<ModelTaskDTO>, getTask,(TaskID id), (override));
    MOCK_METHOD(std::optional<TaskID>, getParent,(TaskID),(override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getAllTasksByPriority,(), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksForToday,(), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksForWeek,(), (override));
    MOCK_METHOD(bool, removeTask, (const std::weak_ptr<FullTask> &task), (override));
};

#endif //TODOLIST_MODELMOCK_H
