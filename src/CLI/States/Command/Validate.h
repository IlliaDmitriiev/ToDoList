//
// Created by hp on 14.09.2020.
//

#ifndef TODOLIST_VALIDATE_H
#define TODOLIST_VALIDATE_H

#include "CommandState.h"
#include "ValidMapCreator.h"

/*
 * Namespace which creates type
 * based on given string
 *
 * @author Ilya Dmitriev
 */
namespace validate{

    static CommandState::Type make(std::string input){
        auto valid_map = ValidMap::create();
        if (valid_map.find(input)!=valid_map.end()) return valid_map[input];
        else { return CommandState::Type::Error;}
    }
}

#endif //TODOLIST_VALIDATE_H
