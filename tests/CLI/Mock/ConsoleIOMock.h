//
// Created by ilya on 04.10.2020.
//

#ifndef TODOLIST_CONSOLEIOMOCK_H
#define TODOLIST_CONSOLEIOMOCK_H

#include <gmock/gmock.h>
#include "CLI/Utils/IO.h"

class MockConsoleIO : public IO {
public:
    MOCK_METHOD(std::string, input, (), (override));
    MOCK_METHOD(void, output, (std::string), (override));
};

#endif //TODOLIST_CONSOLEIOMOCK_H
