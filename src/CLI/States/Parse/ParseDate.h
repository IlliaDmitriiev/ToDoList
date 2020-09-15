//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_PARSEDATE_H
#define TODOLIST_PARSEDATE_H

#include "ParseState.h"

class ParseDate: public ParseState{

public:
    bool read(IO&, ParameterStorage&) override;
    void print(IO&) override;
    ParseState::Type changeState() override;

};

#endif //TODOLIST_PARSEDATE_H
