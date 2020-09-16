//
// Created by hp on 06.09.2020.
//

#ifndef TESTCLI_COMMANDSTATE_H
#define TESTCLI_COMMANDSTATE_H

#include "CLI/Model/Context.h"
#include "CLI/Utils/ConsoleIO.h"
#include <memory>

/*
 *  State that defines behavior
 *  following command classes.
 *
 *  @author: Ilya Dmitriev
 */
class CommandState{

public:
    enum class Type{
        AddTask,
        AddSubtask,
        DeleteTask,
        CompleteTask,
        PostponeTask,
        ShowAllTasks,
        ShowAllTasksForToday,
        ShowAllTasksForWeek,
        Option,
        Submenu,
        View,
        Edit,
        Exit,
        Skip,
        Error
    };

public:
    /*
     * Reads user input and make strict type on it.
     *
     * @param: [IO] inputs param.
     *
     * @return [CommandState::Type] strict type which was based on user input.
     */
    virtual CommandState::Type read(IO&) = 0;
    /*
     * Prints basic rules to console
     * in order to user can simply understand what to do.
     *
     * @param: [IO] outputs param.
     *
     */
    virtual void print(IO&) = 0;
    /*
     * Process needed request
     *
     * @param: [IO] outputs param.
     * @param: [Context] gives access to service.
     *
     */
    virtual void execute(IO&, Context&) = 0;
    /*
     * Returns next command state
     *
     * @param: [CommandState::Type] to make a decision
     * what state will be returned.
     *
     * @return [std::unique_ptr<CommandState>] next state.
     */
    virtual std::unique_ptr<CommandState> change(CommandState::Type) = 0;

    virtual ~CommandState() = default;

};

#endif //TESTCLI_COMMANDSTATE_H
