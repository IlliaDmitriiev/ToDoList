//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_PARSEID_H
#define TODOLIST_PARSEID_H

#include "ParseState.h"

class ParseID: public ParseState{

public:
    bool read(IO&, ParameterStorage&) override;
    void print(IO&) override;
    ParseState::Type changeState() override;

};


#endif //TODOLIST_PARSEID_H
