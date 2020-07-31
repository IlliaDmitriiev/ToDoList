//
// Created by Илля on 31.07.2020.
//

#include "ViewByPriority.h"

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getAllTasks(){
    std::vector<std::weak_ptr<FullTask>> v;
    auto vFirst = storage_.getVFirstPrior();
    auto vSecond = storage_.getVSecondPrior();
    auto vThird = storage_.getVThirdPrior();
    auto vNone = storage_.getVNonePrior();
    for (auto i: vFirst)
        if (!i.expired())
            v.push_back(i);
    for (auto i: vSecond)
        if (!i.expired())
            v.push_back(i);
    for (auto i: vThird)
        if (!i.expired())
            v.push_back(i);
    for (auto i: vNone)
        if (!i.expired())
            v.push_back(i);
    return v;
}

StorageByPrior &ViewByPriority::getStorage(){
    return storage_;
}
