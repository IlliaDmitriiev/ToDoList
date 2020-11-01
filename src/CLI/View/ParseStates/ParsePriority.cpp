//
// Created by hp on 15.09.2020.
//

#include "ParsePriority.h"

bool ParsePriority::read(IO& io, ParameterStorage& buffer) {
    auto priority = io.input();

    if (priority.size()==1 && (priority[0]>'0' && priority[0]<'5')) {
        buffer.getParameters().priority_ = (TaskPriority)(std::stoi(priority) % 4);
        return true;
    }
    else {
        return false;
    }
}

void ParsePriority::print(IO& io) {
    io.output("Enter the priority of task:\n1 - First\n2 - Second\n3 - Third\n4 - None(Example of input: 2):\n");
}

ParseState::Type ParsePriority::changeState() {
    return ParseState::Type::Priority;
}
