//
// Created by ilya on 04.10.2020.
//

#include "PriorityConvertor.h"

TaskPriority PriorityConvertor::tranferToPriority(TaskStructure::Priority priority){
    if (TaskStructure_Priority_FIRST == priority){
        return TaskPriority::First;
    }
    else if (TaskStructure_Priority_SECOND == priority){
        return TaskPriority::Second;
    }
    else if (TaskStructure_Priority_THIRD == priority){
        return TaskPriority::Third;
    }
    else {
        return TaskPriority::None;
    }

}

TaskStructure::Priority PriorityConvertor::tranferToProtoPriority(TaskPriority priority){
    if (TaskPriority::First == priority){
        return TaskStructure_Priority_FIRST;
    }
    else if (TaskPriority::Second == priority){
        return TaskStructure_Priority_SECOND;
    }
    else if (TaskPriority::Third == priority){
        return TaskStructure_Priority_THIRD;
    }
    else {
        return TaskStructure_Priority_NONE;
    }
}