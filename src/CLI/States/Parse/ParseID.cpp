//
// Created by hp on 15.09.2020.
//

#include "ParseID.h"

bool ParseID::read(IO& io, ParameterStorage& buffer) {
    auto id = io.input();
    for(auto i: id){
        if (i>='0' && i<='9');
        else{
            return false;
        }
    }
    buffer.getParameters().id_ = std::stoi(id);
    return true;
}

void ParseID::print(IO& io) {
    io.output("Enter the number of task which defines it (Number > 0. Example of input: 47):\n");
}

ParseState::Type ParseID::changeState() {
    return ParseState::Type::ID;
}
