//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_PARSENAME_H
#define TODOLIST_PARSENAME_H

#include "ParseState.h"

class ParseName: public ParseState{

public:
    bool read(IO&, ParameterStorage&) override;
    void print(IO&) override;
    ParseState::Type changeState() override;

};

#endif //TODOLIST_PARSENAME_H
