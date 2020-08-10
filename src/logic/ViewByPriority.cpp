//
// Created by Илля on 31.07.2020.
//

#include "ViewByPriority.h"

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getAllTasks(){
    auto map = storage_.getMap();
    std::vector<std::weak_ptr<FullTask>> v;
    for(auto i: map[1])
        v.push_back(i.second);
    for(auto i: map[2])
        v.push_back(i.second);
    for(auto i: map[3])
        v.push_back(i.second);
    for(auto i: map[0])
        v.push_back(i.second);

    return v;
}

StorageByPriority &ViewByPriority::getStorage(){
    return storage_;
}
