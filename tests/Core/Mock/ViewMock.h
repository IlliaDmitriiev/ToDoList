//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_VIEWMOCK_H
#define TODOLIST_VIEWMOCK_H

#include <gmock/gmock.h>
#include "Core/model/logic/ViewInterface.h"

class MockView : public ViewInterface{

public:
    MOCK_METHOD(bool, addTask, (const std::weak_ptr<FullTask>&), (override));
    MOCK_METHOD(bool, deleteTask, (const std::weak_ptr<FullTask>&), (override));

    MOCK_METHOD(std::vector<std::weak_ptr<FullTask>>, getAllTasksByPrior, (),(override));
    MOCK_METHOD(std::vector<std::weak_ptr<FullTask>>, getTasksForToday, (boost::gregorian::date),(override));
    MOCK_METHOD(std::vector<std::weak_ptr<FullTask>>, getTasksForWeek, (boost::gregorian::date),(override));
};

#endif //TODOLIST_VIEWMOCK_H
