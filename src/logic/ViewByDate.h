//
// Created by Илля on 30.07.2020.
//

#ifndef TODOLIST_VIEWBYPRIORITY_H
#define TODOLIST_VIEWBYPRIORITY_H

#include "ViewInterface.h"

namespace std {

    template <>
    struct hash<boost::gregorian::date>
    {
        size_t operator () (const boost::gregorian::date& date) const
        {
            return std::hash<decltype(date.julian_day())>()(date.julian_day());
        }
    };

}

class ViewByDate: public ViewInterface {

public:
    std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior() override;
    std::vector<std::weak_ptr<FullTask>> getTasksForToday(BoostDate date) override ;
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek(BoostDate date) override ;

public:
    bool addTask(const std::weak_ptr<FullTask>& ft)  override ;
    bool deleteTask(const std::weak_ptr<FullTask>& ft) override ;

private:
    std::unordered_map<BoostDate,
        std::map<TaskPriority,
            std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator>
                 >
                      > map_;


};


#endif //TODOLIST_VIEWBYPRIORITY_H
