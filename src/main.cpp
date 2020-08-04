
#include "TaskService.h"

int main() {
    TaskService ts;
    ts.addTask(Date::create(2020,7,30),
            "name1", "label1", Task::Priority::First);
    ts.addTask(Date::create(2020,7,31),
            "name2", "label2", Task::Priority::Third);
    ts.addSubtask(TaskID::create(1), Date::create(2020,8,1),
               "name3", "label3", Task::Priority::Second);
    ts.getTasksForWeek();
    return 0;
}
