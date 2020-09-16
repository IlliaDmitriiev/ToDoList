//
// Created by hp on 17.09.2020.
//

#ifndef TODOLIST_PARSEMAPCREATOR_H
#define TODOLIST_PARSEMAPCREATOR_H

#include "CLI/States/Parse/ParseState.h"
#include "CLI/States/Parse/ParseDate.h"
#include "CLI/States/Parse/ParseID.h"
#include "CLI/States/Parse/ParseName.h"
#include "CLI/States/Parse/ParseLabel.h"
#include "CLI/States/Parse/ParsePriority.h"

namespace ParseMap{
    static std::map<ParseState::Type, std::unique_ptr<ParseState>> create(){

        std::map<ParseState::Type, std::unique_ptr<ParseState>> links;
        links[ParseState::Type::Date]     = std::make_unique<ParseDate>();
        links[ParseState::Type::ID]       = std::make_unique<ParseID>();
        links[ParseState::Type::Label]    = std::make_unique<ParseLabel>();
        links[ParseState::Type::Name]     = std::make_unique<ParseName>();
        links[ParseState::Type::Priority] = std::make_unique<ParsePriority>();

        return links;
    }
}

#endif //TODOLIST_PARSEMAPCREATOR_H
