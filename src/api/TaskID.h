//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKID_H
#define TODOLIST_TASKID_H

#include<iostream>
/*
 *  Class-wrapper of ID to hide its implementation
 *
 *  @author: Ilya Dmitriev
 */
class TaskID {

public:
    static TaskID create(int id);

public:
    /*
     * Structure which has the ability to hash TaskID
     */
    struct Hasher{
        std::size_t operator()(const TaskID& k) const{
            return k.getId();
        }
    };
    /*
     * Structure which has the ability to check equality of TaskIDs
     */
    struct Comparator{
        bool operator()( const TaskID& l, const TaskID& r ) const{
            return l.getId() == r.getId();

        }
    };
    /*
     * Structure which has the ability to compare TaskIDs
     */
    struct MapComparator{
        bool operator()( const TaskID& l, const TaskID& r ) const{
            return l.getId() < r.getId();

        }
    };

public:
    unsigned int getId() const;

private:
    TaskID(unsigned int id);


private:
    unsigned int id_;
};


#endif //TODOLIST_TASKID_H
