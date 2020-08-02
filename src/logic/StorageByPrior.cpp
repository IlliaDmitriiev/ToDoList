//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "StorageByPrior.h"

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVFirstPrior() const {
    return vFirstPrior_;
}

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVSecondPrior() const {
    return vSecondPrior_;
}

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVThirdPrior() const {
    return vThirdPrior_;
}

const std::vector<std::weak_ptr<FullTask>> &StorageByPrior::getVNonePrior() const {
    return vNonePrior_;
}

void StorageByPrior::putTaskInRightPlace(std::weak_ptr<FullTask> cur){
    Task::Priority prior = cur.lock()->getTask().getPrior();
    if (prior == Task::Priority::First) vFirstPrior_.push_back(cur);
    else if (prior == Task::Priority::Second) vSecondPrior_.push_back(cur);
    else if (prior == Task::Priority::Third) vThirdPrior_.push_back(cur);
    else if (prior == Task::Priority::None) vNonePrior_.push_back(cur);
}

void StorageByPrior::deleteDanglingPointers(){
    std::vector<std::weak_ptr<FullTask>> cur1;
    for (int i =0 ; i<vFirstPrior_.size(); ++i)
        if (!vFirstPrior_[i].expired())
            cur1.push_back(vFirstPrior_[i]);
    vFirstPrior_ = cur1;

    std::vector<std::weak_ptr<FullTask>> cur2;
    for (int i =0 ; i<vSecondPrior_.size(); ++i)
        if (!vSecondPrior_[i].expired())
            cur2.push_back(vSecondPrior_[i]);
    vSecondPrior_ = cur2;

    std::vector<std::weak_ptr<FullTask>> cur3;
    for (int i =0 ; i < vThirdPrior_.size(); ++i)
        if (!vThirdPrior_[i].expired())
            cur3.push_back(vThirdPrior_[i]);
    vThirdPrior_ = cur3;

    std::vector<std::weak_ptr<FullTask>> cur4;
    for (int i =0 ; i < vNonePrior_.size(); ++i)
        if (!vNonePrior_[i].expired())
            cur4.push_back(vNonePrior_[i]);
    vNonePrior_ = cur4;
}
