//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "StorageByPrior.h"

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVFirstPrior() const {
    return vFirstPrior;
}

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVSecondPrior() const {
    return vSecondPrior;
}

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVThirdPrior() const {
    return vThirdPrior;
}

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVNonePrior() const {
    return vNonePrior;
}

void StorageByPrior::putTaskInRightPlace(std::weak_ptr<FullTask> cur, Task::Priority prior){
    if (prior == Task::Priority::First) vFirstPrior.push_back(cur);
    else if (prior == Task::Priority::Second) vSecondPrior.push_back(cur);
    else if (prior == Task::Priority::Third) vThirdPrior.push_back(cur);
    else if (prior == Task::Priority::None) vNonePrior.push_back(cur);
}

void StorageByPrior::updateVectors(){
    std::vector<std::weak_ptr<FullTask>> cur1;
    for (int i =0 ; i<vFirstPrior.size(); ++i)
        if (!vFirstPrior[i].expired())
            cur1.push_back(vFirstPrior[i]);
    vFirstPrior = cur1;

    std::vector<std::weak_ptr<FullTask>> cur2;
    for (int i =0 ; i<vSecondPrior.size(); ++i)
        if (!vSecondPrior[i].expired())
            cur2.push_back(vSecondPrior[i]);
    vSecondPrior=cur2;

    std::vector<std::weak_ptr<FullTask>> cur3;
    for (int i =0 ; i<vThirdPrior.size(); ++i)
        if (!vThirdPrior[i].expired())
            cur3.push_back(vThirdPrior[i]);
    vThirdPrior=cur3;

    std::vector<std::weak_ptr<FullTask>> cur4;
    for (int i =0 ; i<vNonePrior.size(); ++i)
        if (!vNonePrior[i].expired())
            cur4.push_back(vNonePrior[i]);
    vNonePrior = cur4;
}
