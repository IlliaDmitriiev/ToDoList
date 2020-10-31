//
// Created by ilya on 04.10.2020.
//

#ifndef TODOLIST_SERVICEMOCK_H
#define TODOLIST_SERVICEMOCK_H

#include <gmock/gmock.h>
#include "CLI/Proxy/Proxy.h"

class MockTaskService : public Proxy {

public:
    MOCK_METHOD(AddTaskResult, addTask, (const TaskDTO&), (override));
    MOCK_METHOD(AddTaskResult, addSubtask, (TaskID, const TaskDTO &), (override));
    MOCK_METHOD(RequstTaskResult, deleteTask, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, complete, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, postponeTask, (TaskID, boost::gregorian::date), (override));
    MOCK_METHOD(RequstTaskResult, editTask, (TaskID id, const TaskDTO&), (override));
    MOCK_METHOD(RequstTaskResult, save, (const std::string&), (override));
    MOCK_METHOD(RequstTaskResult, load, (const std::string&), (override));
public:

    MOCK_METHOD(std::vector<TaskDTO>, getSubtasks, (TaskID), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getAllTasksByPriority, (), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getTasksForToday, (), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getTasksForWeek, (), (override));
    MOCK_METHOD(std::optional<TaskDTO>, getTask, (TaskID), (override));

};

#endif //TODOLIST_SERVICEMOCK_H
