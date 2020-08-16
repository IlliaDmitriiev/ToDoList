//
// Created by Илля on 01.08.2020.
//

#ifndef TODOLIST_VIEWINTERFACE_H
#define TODOLIST_VIEWINTERFACE_H

#include "model/FullTask.h"
#include <map>
#include <vector>

/*
 *  Class w
 *
 *  @author: Ilya Dmitriev
 */
class ViewInterface {

public:
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of TaskDTO
     */
    virtual std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior() = 0;
    /*
     * Gives all tasks for today already sorted by priority.
     *
     * @return vector of TaskDTO
     */
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForToday(boost::gregorian::date date) = 0;
    /*
     * Gives all tasks for this week already sorted by priority.
     *
     * @return vector of TaskDTO
     */
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForWeek(boost::gregorian::date date)= 0;

public:
    /*
     * adds task to view
     *
     * @param: task link
     *
     * @return true if operation was successful, otherwise false
     */
    virtual bool addTask(const std::weak_ptr<FullTask>& ft)= 0;
    /*
     * deletes task from view
     *
     * @param: task link
     *
     * @return true if operation was successful, otherwise false
     */
    virtual bool deleteTask(const std::weak_ptr<FullTask>& ft)= 0;

    virtual ~ViewInterface() = default;
};


#endif //TODOLIST_VIEWINTERFACE_H
