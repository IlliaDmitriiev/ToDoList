//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_PARSESTATE_H
#define TODOLIST_PARSESTATE_H

#include "CLI/Utils/ConsoleIO.h"
#include "CLI/Model/ParameterStorage.h"

class ParseState{

public:
    enum class Type{
        Name,
        Label,
        Date,
        ID,
        Priority,
        Filename,
        Exit
    };

public:
    virtual bool read(IO&, ParameterStorage&) = 0;
    virtual void print(IO&) = 0;
    virtual ParseState::Type changeState() = 0;

    virtual ~ParseState() = default;
};
#endif //TODOLIST_PARSESTATE_H
