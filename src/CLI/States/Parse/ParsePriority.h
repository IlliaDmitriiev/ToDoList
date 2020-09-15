//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_PARSEPRIORITY_H
#define TODOLIST_PARSEPRIORITY_H

#include "ParseState.h"

class ParsePriority: public ParseState{

public:
    bool read(IO&, ParameterStorage&) override;
    void print(IO&) override;
    ParseState::Type changeState() override;

};


#endif //TODOLIST_PARSEPRIORITY_H
