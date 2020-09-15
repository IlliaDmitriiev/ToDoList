//
// Created by hp on 08.09.2020.
//

#include "ParseMachine.h"

ParseMachine::ParseMachine(
        IO& io,
        ParameterStorage& buffer,
        Parser::Type start_state,
        std::map<Parser::Type, Parser::Type>& links
)
        :io_(io),
         links_(links),
         buffer_(buffer),
         state_(start_state){}

void ParseMachine::run(){
    while(true){
        if (!Parser::parse(io_, buffer_, state_)) {
            io_.output("Incorrect input!\n");
            continue;
        }

        auto next_state = links_[state_];
        if (next_state == Parser::Type::Exit || links_.find(next_state) == links_.end()) {
            break;
        }

        state_ = next_state;
    }
}