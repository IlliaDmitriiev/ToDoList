//
// Created by ilya on 11.10.2020.
//

#include "LoadCommand.h"
#include "CLI/Namespaces/GraphCreator.h"
#include "CLI/Namespaces/CommandMapCreator.h"

CommandState::Type LoadCommand::read(IO&) {
    return CommandState::Type::Option;
}

void LoadCommand::print(IO&) {

}

void LoadCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::load_data::create();
    auto buffer = ParameterStorage::create();

    ParseMachine pm(io, buffer, ParseState::Type::Filename, links);
    pm.run();

    auto &service = context.getService();
    auto params = buffer.getParameters() ;
    auto result = service.load(params.filename_+".txt");
    if ( ResultType::FAILURE == result.result) {
        io.output(result.error_message+"\n");
    }
    else {
        io.output("System was loaded successfully.\n");
    }

}

std::unique_ptr<CommandState> LoadCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
