//
// Created by ilya on 13.10.2020.
//

#include "ParseFilename.h"

bool ParseFilename::read(IO& io, ParameterStorage& buffer) {
    auto filename = io.input();
    if (filename.empty()){
        return false;
    }
    buffer.getParameters().filename_ = filename;
    return true;
}

void ParseFilename::print(IO& io) {
    io.output("Enter the filename(Example of input: testname):\n");
}

ParseState::Type ParseFilename::changeState() {
    return ParseState::Type::Filename;
}