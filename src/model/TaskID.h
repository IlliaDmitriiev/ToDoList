//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKID_H
#define TODOLIST_TASKID_H


class TaskID {

public:
    static TaskID create(int id);
public:
    int getId() const;

private:
    TaskID(int id);


private:
    int id;
};


#endif //TODOLIST_TASKID_H
