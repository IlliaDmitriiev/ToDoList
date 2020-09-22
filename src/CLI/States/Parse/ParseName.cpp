//
// Created by hp on 15.09.2020.
//

#include "ParseName.h"

bool ParseName::read(IO& io, ParameterStorage& buffer) {
    buffer.getParameters().name_ = io.input();
    return true;
}

void ParseName::print(IO& io) {
    io.output("Enter the name(Example of input: go to the shop tomorrow):\n");
}

ParseState::Type ParseName::changeState() {
    return ParseState::Type::Name;
}