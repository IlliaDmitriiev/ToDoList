//
// Created by hp on 14.09.2020.
//

#include "View.h"
#include "Validate.h"
#include "Edit.h"
#include "Option.h"

CommandState::Type View::read(IO& io) {
    return validate::make(io.input());
}

void View::print(IO& io){
    io.output("Available commands:\nview\nback\nExample of input: back\n");
}

std::unique_ptr<CommandState> View::change(CommandState::Type type) {
    if (type == CommandState::Type::Option){return std::make_unique<Option>();}
    else if (type == CommandState::Type::View) {return std::make_unique<Edit>();}
    else {return std::make_unique<View>();}
}
