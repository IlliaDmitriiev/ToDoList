//
// Created by hp on 08.09.2020.
//

#ifndef TESTCLI_COMMANDS_H
#define TESTCLI_COMMANDS_H

#include "CommandState.h"
#include <iostream>

/*
 *  Stateless object which has
 *  ability to execute defined commands
 *
 *  @author: Ilya Dmitriev
 */
class Commands {

public:
    /*
     * Executed needed request
     *
     * @param: [CommandState::Type] detects needed function
     * @param: [Context] transfer TaskService to functions
     *
     */
    static void execute(CommandState::Type, Context&);

private:
    static void addTask(Context&);
    static void addSubtask(Context&);
    static void deleteTask(Context&);
    static void completeTask(Context&);
    static void postponeTask(Context&);
    static void editTask(Context&);
    static void viewTask(Context&);
    static void showAllTasks(Context&);
    static void showAllForToday(Context&);
    static void showAllForWeek(Context&);

};


#endif //TESTCLI_COMMANDS_H
