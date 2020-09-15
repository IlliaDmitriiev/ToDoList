//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_PARSELABEL_H
#define TODOLIST_PARSELABEL_H

#include "ParseState.h"

class ParseLabel: public ParseState{

public:
    bool read(IO&, ParameterStorage&) override;
    void print(IO&) override;
    ParseState::Type changeState() override;

};

#endif //TODOLIST_PARSELABEL_H
