//
// Created by hp on 17.09.2020.
//

#include "SubmenuCommand.h"
#include "CLI/Utils/Creators/Validate.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"

CommandState::Type SubmenuCommand::read(IO& io) {
    return validate::make(io.input());
}

void SubmenuCommand::print(IO& io){
    io.output("Available commands:\nview\nedit\nback\nExample of input: back\n");
}

void SubmenuCommand::execute(IO& io, Context& context) {

}

std::unique_ptr<CommandState> SubmenuCommand::change(CommandState::Type type) {
    auto map = CommandMap::create();
    if (CommandState::Type::Error == type){return std::make_unique<SubmenuCommand>();}
    return std::move(map[type]);
}