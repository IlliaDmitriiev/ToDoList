//
// Created by Илля on 31.07.2020.
//

#include "ViewByPriority.h"

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getAllTasks(const StorageByPrior& sbp){
    std::vector<std::weak_ptr<FullTask>> v;
    auto vFirst = sbp.getVFirstPrior();
    auto vSecond = sbp.getVSecondPrior();
    auto vThird = sbp.getVThirdPrior();
    auto vNone = sbp.getVNonePrior();
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