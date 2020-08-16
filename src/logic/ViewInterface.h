//
// Created by Илля on 01.08.2020.
//

#ifndef TODOLIST_VIEWINTERFACE_H
#define TODOLIST_VIEWINTERFACE_H

#include "model/FullTask.h"
#include <map>
#include <vector>

/*
 *  Class which gets tasks in right order
 *  and has ability to update views
 *
 *  @author: Ilya Dmitriev
 */
class ViewInterface {

public:
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return collection of links to tasks
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior() = 0;
    /*
     * Gives all tasks for today already sorted by priority.
     *
     * @return collection of links to tasks
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForToday(boost::gregorian::date date) = 0;
    /*
     * Gives all tasks for this week already sorted by priority.
     *
     * @return collection of links to tasks
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForWeek(boost::gregorian::date date)= 0;

public:
    /*
     * adds task to view
     *
     * @param: task link
     *
     * @return true if operation is successful, otherwise false
     */
    virtual bool addTask(const std::weak_ptr<FullTask>& ft)= 0;
    /*
     * deletes task from view
     *
     * @param: task link
     *
     * @return true if operation is successful, otherwise false
     */
    virtual bool deleteTask(const std::weak_ptr<FullTask>& ft)= 0;

    virtual ~ViewInterface() = default;
};


#endif //TODOLIST_VIEWINTERFACE_H
