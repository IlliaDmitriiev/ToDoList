//
// Created by hp on 17.09.2020.
//

#ifndef TODOLIST_PARSEMAPCREATOR_H
#define TODOLIST_PARSEMAPCREATOR_H

#include "CLI/View/ParseStates/ParseState.h"
#include "CLI/View/ParseStates/ParseDate.h"
#include "CLI/View/ParseStates/ParseID.h"
#include "CLI/View/ParseStates/ParseName.h"
#include "CLI/View/ParseStates/ParseLabel.h"
#include "CLI/View/ParseStates/ParseFilename.h"
#include "CLI/View/ParseStates/ParsePriority.h"

namespace ParseMap{
    static std::map<ParseState::Type, std::unique_ptr<ParseState>> create(){

        std::map<ParseState::Type, std::unique_ptr<ParseState>> links;
        links[ParseState::Type::Date]     = std::make_unique<ParseDate>();
        links[ParseState::Type::ID]       = std::make_unique<ParseID>();
        links[ParseState::Type::Label]    = std::make_unique<ParseLabel>();
        links[ParseState::Type::Name]     = std::make_unique<ParseName>();
        links[ParseState::Type::Filename] = std::make_unique<ParseFilename>();
        links[ParseState::Type::Priority] = std::make_unique<ParsePriority>();

        return links;
    }
}

#endif //TODOLIST_PARSEMAPCREATOR_H
