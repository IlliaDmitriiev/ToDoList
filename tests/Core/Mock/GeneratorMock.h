//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_GENERATORMOCK_H
#define TODOLIST_GENERATORMOCK_H

#include <gmock/gmock.h>
#include "Core/model/logic/IDGeneratorInterface.h"

class MockGenerator : public IDGeneratorInterface {

public:
    MOCK_METHOD(TaskID, generateId, (), (override));
};

#endif //TODOLIST_GENERATORMOCK_H
