//
// Created by ilya on 13.10.2020.
//

#ifndef TODOLIST_PARSEFILENAME_H
#define TODOLIST_PARSEFILENAME_H

#include "ParseState.h"

class ParseFilename: public ParseState{

public:
    bool read(IO&, ParameterStorage&) override;
    void print(IO&) override;
    ParseState::Type changeState() override;

};


#endif //TODOLIST_PARSEFILENAME_H
