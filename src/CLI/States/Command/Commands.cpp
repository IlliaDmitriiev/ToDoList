//
// Created by hp on 08.09.2020.
//

#include "Commands.h"
#include "GraphCreator.h"

void Commands::execute(CommandState::Type command, Context& context){

    if  (     command == CommandState::Type::AddTask)             {Commands::addTask(context);}
    else if  (command == CommandState::Type::AddSubtask)          {Commands::addSubtask(context);}
    else if  (command == CommandState::Type::DeleteTask)          {Commands::deleteTask(context);}
    else if  (command == CommandState::Type::CompleteTask)        {Commands::completeTask(context);}
    else if  (command == CommandState::Type::PostponeTask)        {Commands::postponeTask(context);}
    else if  (command == CommandState::Type::ShowAllTasks)        {Commands::showAllTasks(context);}
    else if  (command == CommandState::Type::ShowAllTasksForToday){Commands::showAllForToday(context);}
    else if  (command == CommandState::Type::ShowAllTasksForWeek) {Commands::showAllForWeek(context);}
    else if  (command == CommandState::Type::View)                {Commands::viewTask(context);}
    else if  (command == CommandState::Type::Edit)                {Commands::editTask(context);}

}

void Commands::addTask(Context& context){
    auto links = transitions_graph::add_task::create();
    Buffer buffer;
    auto io = std::make_unique<ConsoleIO>();

    ParseMachine pm(*io, buffer, Parser::Type::Name, links);
    pm.run();

    auto &service = context.getService();
    auto result = service.addTask(
            TaskDTO::create(buffer.buf_.date_, buffer.buf_.name_, buffer.buf_.label_, buffer.buf_.priority_));

    if (result.result == ResultType::FAILURE) {
        io->output(result.error_message + "\n");
        return;
    }
    io->output("Task added successfully\n");

}

void Commands::addSubtask(Context& context){
    auto links = transitions_graph::add_subtask::create();
    Buffer buffer;
    auto io = std::make_unique<ConsoleIO>();

    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();

    auto &service = context.getService();
    auto &tasks = context.getTaskList();

    if (tasks.size() < buffer.buf_.id_){
        io->output("There isn't root task with such id!\n");
        return;
    }
    auto result = service.addSubtask(tasks[buffer.buf_.id_ - 1].getId(),
                                TaskDTO::create(buffer.buf_.date_, buffer.buf_.name_,
                                                buffer.buf_.label_, buffer.buf_.priority_));
    if (result.result == ResultType::FAILURE) {
        io->output(result.error_message + "\n");
        return;
    }
    io->output("Subtask added successfully\n");

}

void Commands::deleteTask(Context& context) {
    auto links = transitions_graph::delete_task::create();
    Buffer buffer;
    auto io = std::make_unique<ConsoleIO>();

    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();
    auto &service = context.getService();
    auto &tasks = context.getTaskList();

    if (tasks.size() < buffer.buf_.id_) {
        io->output("There isn't task with such id!\n");
        return;
    }
    auto result = service.deleteTask(tasks[buffer.buf_.id_ - 1].getId());
    if (result.result == ResultType::FAILURE) {
        io->output(result.error_message + "\n");
        return;
    }
    io->output("Task deleted successfully\n");
}

void Commands::completeTask(Context& context) {
    auto links = transitions_graph::postpone_task::create();
    Buffer buffer;
    auto io = std::make_unique<ConsoleIO>();

    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();
    auto &service = context.getService();
    auto &tasks = context.getTaskList();

    if (tasks.size() < buffer.buf_.id_) {
        io->output("There isn't task with such id!\n");
        return;
    }
    auto result = service.complete(tasks[buffer.buf_.id_ - 1].getId());
    if (result.result == ResultType::FAILURE) {
        io->output(result.error_message + "\n");
        return;
    }
    io->output("Task completed successfully\n");
}

void Commands::editTask(Context& context){
    auto links = transitions_graph::add_subtask::create();
    Buffer buffer;
    auto io = std::make_unique<ConsoleIO>();
    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();
    auto &service = context.getService();
    auto &tasks = context.getTaskList();

    if (tasks.size() < buffer.buf_.id_){
        io->output("There isn't task with such id!\n");
        return;
    }
    auto result = service.editTask(
            tasks[buffer.buf_.id_ - 1].getId(),
            TaskDTO::create(buffer.buf_.date_, buffer.buf_.name_, buffer.buf_.label_, buffer.buf_.priority_));

    if (result.result == ResultType::FAILURE) {
        io->output(result.error_message + "\n");
        return;
    }
    io->output("Task edited successfully\n");

}

void Commands::viewTask(Context& context){
    auto links = transitions_graph::complete_task::create();
    Buffer buffer;
    auto io = std::make_unique<ConsoleIO>();
    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();
    auto &service = context.getService();
    auto &tasks = context.getTaskList();

    if (tasks.size() < buffer.buf_.id_){
        io->output("There isn't task with such id!\n");
        return;
    }
    auto task = tasks[buffer.buf_.id_ - 1];
    io->output("Task: (\n"
               "    Name: [" + task.getName()+ "]\n"
               "    Label: [" + task.getLabel()+"]\n"
               "    Date: [" + to_simple_string(task.getDate())+"]\n"
               "    Priority: [" + std::to_string((int)task.getPriority()) + "]\n"
               "    Completed: [" + (task.isCompleted()?"True":"False") +"]);\n");

    auto vector = service.getSubtasks(tasks[buffer.buf_.id_ - 1].getId());
    for (int i = 0; i<vector.size(); ++i){
        io->output("Subtask: { Name: [" + vector[i].getName() + "] Date: ["
                   + to_simple_string(vector[i].getDate()) + "] }\n");
    }

}

void Commands::postponeTask(Context& context){
    auto links = transitions_graph::postpone_task::create();
    Buffer buffer;
    auto io = std::make_unique<ConsoleIO>();
    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();
    auto &service = context.getService();
    auto &tasks = context.getTaskList();

    if (tasks.size() < buffer.buf_.id_){
        io->output("There isn't task with such id!\n");
        return;
    }
    auto result = service.postponeTask(tasks[buffer.buf_.id_ - 1].getId(), buffer.buf_.date_);
    if (result.result == ResultType::FAILURE) {
        io->output(result.error_message + "\n");
        return;
    }
    io->output("Task postponed successfully\n");
}

void Commands::showAllTasks(Context& context){
    auto &service = context.getService();
    auto &vector = context.getTaskList();

    vector = service.getAllTasksByPriority();
    auto io = std::make_unique<ConsoleIO>();

    io->output("All tasks:\n");
    for (int i = 0; i<vector.size(); ++i){
        io->output("{ Number: ["+std::to_string(i + 1) + "] Name: [" +
                   vector[i].getName() + "] Date: ["
                   + to_simple_string(vector[i].getDate()) + "] }\n");
    }
}

void Commands::showAllForToday(Context& context){
    auto &service = context.getService();
    auto &vector = context.getTaskList();

    vector = service.getTasksForToday();
    auto io = std::make_unique<ConsoleIO>();

    io->output("Tasks for today:\n");
    for (int i = 0; i<vector.size(); ++i){
        io->output("{ Number: ["+std::to_string(i + 1) + "] Name: [" +
                   vector[i].getName() + "] Date: ["
                   + to_simple_string(vector[i].getDate()) + "] }\n");
    }
}

void Commands::showAllForWeek(Context& context){
    auto &service = context.getService();
    auto &vector = context.getTaskList();

    vector = service.getTasksForWeek();
    auto io = std::make_unique<ConsoleIO>();

    io->output("Tasks for this week:\n");
    for (int i = 0; i<vector.size(); ++i){
        io->output("{ Number: ["+std::to_string(i + 1) + "] Name: [" +
                vector[i].getName() + "] Date: ["
                + to_simple_string(vector[i].getDate()) + "] }\n");
    }
}