//
// Created by hp on 15.09.2020.
//

#include "ParseLabel.h"

bool ParseLabel::read(IO& io, ParameterStorage& buffer) {
    buffer.getParameters().label_ = io.input();
    return true;
}

void ParseLabel::print(IO& io) {
    io.output("Enter the label(Example of input: sport):\n");
}

ParseState::Type ParseLabel::changeState() {
    return ParseState::Type::Label;
}
