//
// Created by ilya on 04.10.2020.
//

#ifndef TODOLIST_SERVICEMOCK_H
#define TODOLIST_SERVICEMOCK_H

#include <gmock/gmock.h>
#include "Core/api/TaskServiceInterface.h"

class MockTaskService : public TaskServiceInterface {

public:
    MOCK_METHOD(AddTaskResult, addTask, (const ServiceTaskDTO&), (override));
    MOCK_METHOD(AddTaskResult, addSubtask, (TaskID, const ServiceTaskDTO &), (override));
    MOCK_METHOD(RequstTaskResult, deleteTask, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, complete, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, postponeTask, (TaskID, boost::gregorian::date), (override));
    MOCK_METHOD(RequstTaskResult, editTask, (TaskID id, const ServiceTaskDTO&), (override));
public:

    MOCK_METHOD(std::vector<ServiceTaskDTO>, getSubtasks, (TaskID), (override));
    MOCK_METHOD(std::vector<ServiceTaskDTO>, getAllTasksByPriority, (), (override));
    MOCK_METHOD(std::vector<ServiceTaskDTO>, getTasksForToday, (), (override));
    MOCK_METHOD(std::vector<ServiceTaskDTO>, getTasksForWeek, (), (override));
    MOCK_METHOD(std::optional<ServiceTaskDTO>, getTask, (TaskID), (override));

};

#endif //TODOLIST_SERVICEMOCK_H
