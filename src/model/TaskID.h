//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKID_H
#define TODOLIST_TASKID_H

#include<iostream>

class TaskID {

public:
    static TaskID create(int id);

    struct Hasher{
        std::size_t operator()(const TaskID& k) const{
            return k.getId();
        }
    };

    struct Comparator{
        bool operator()( const TaskID& l, const TaskID& r ) const{
            return l.getId() == r.getId();

        }
    };

public:
    int getId() const;

private:
    TaskID(int id);


private:
    int id;
};


#endif //TODOLIST_TASKID_H
