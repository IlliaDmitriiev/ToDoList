//
// Created by hp on 08.09.2020.
//

#include "ParseMachine.h"
#include "CLI/Utils/Creators/ParseMapCreator.h"

ParseMachine::ParseMachine(IO& io,
                           ParameterStorage& buffer,
                           ParseState::Type start_state,
                           std::map<ParseState::Type, ParseState::Type>& next_state)
                           :
                           io_(io),
                           next_state_(next_state),
                           buffer_(buffer)
{
    auto states = ParseMap::create();
    if (states.find(start_state) == states.end() ){state_ = nullptr;}
    else {state_ = std::move(states[start_state]);}
}

void ParseMachine::run(){
    if (!state_ || next_state_.empty()){return;}
    while(true){
        state_->print(io_);
        if(!state_->read(io_, buffer_)){
            io_.output("Incorrect input!\n");
            continue;
        }

        auto current_state = state_->changeState();
        if (next_state_.find(current_state) == next_state_.end()){break;}
        if (next_state_[current_state] == ParseState::Type::Exit){break;}

        auto states = ParseMap::create();
        state_ = std::move(states[next_state_[current_state]]);
    }
}