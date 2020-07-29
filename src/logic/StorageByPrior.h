//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_STORAGEBYPRIOR_H
#define TODOLIST_STORAGEBYPRIOR_H


#include "FullTask.h"
#include <vector>

class StorageByPrior {
public:
    const std::vector<std::weak_ptr<FullTask>> &getVFirstPrior() const;

    const std::vector<std::weak_ptr<FullTask>> &getVSecondPrior() const;

    const std::vector<std::weak_ptr<FullTask>> &getVThirdPrior() const;

    const std::vector<std::weak_ptr<FullTask>> &getVNonePrior() const;

    void putTaskInRightPlace(std::weak_ptr<FullTask> cur, Task::Priority prior);
    void updateVectors();

private:
    std::vector<std::weak_ptr<FullTask>> vFirstPrior;
    std::vector<std::weak_ptr<FullTask>> vSecondPrior;
    std::vector<std::weak_ptr<FullTask>> vThirdPrior;
    std::vector<std::weak_ptr<FullTask>> vNonePrior;
};


#endif //TESTP_STORAGEBYPRIOR_H
