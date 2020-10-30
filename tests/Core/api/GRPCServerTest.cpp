//
// Created by ilya on 28.10.2020.
//

#include <gtest/gtest.h>
#include "Mock/ModelMock.h"
#include "Core/api/GRPCServer.h"

using ::testing::Return;

class GRPCServerTest : public ::testing::Test {
public:
    std::unique_ptr<TaskStructure> task1;
    std::unique_ptr<TaskStructure> task2;
    void SetUp() override{
        task1 = std::make_unique<TaskStructure>();
        task1->set_name("name1");
        task1->set_label("label1");
        task1->set_prior(TaskStructure::NONE);
        task1->set_date(boost::gregorian::day_clock::local_day().day_number());
        task1->set_completed(false);

        task2 = std::make_unique<TaskStructure>();
        task2->set_name("name2");
        task2->set_label("label2");
        task2->set_prior(TaskStructure::FIRST);
        task2->set_date(boost::gregorian::date(2000,10,20).day_number());
        task2->set_completed(true);
    }
};

TEST_F(GRPCServerTest, shouldAddTaskSuccessfully) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedSuccessful(TaskID::create(5))));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response = std::make_unique<AddTaskResponse>();
    auto result = service->addTask(nullptr, task1.get(), response.get());

    EXPECT_TRUE(response->success());
    EXPECT_EQ(response->created_id().id(),5);
}

TEST_F(GRPCServerTest, shouldAddTaskUnsuccessfully1) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedUnsuccessful("magic")));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response = std::make_unique<AddTaskResponse>();

    auto result = service->addTask(nullptr, task1.get(), response.get());
    EXPECT_EQ(response->success(), false);
    EXPECT_EQ(response->error_message(), "magic");
}

TEST_F(GRPCServerTest, shouldFailAddSubtask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addSubtask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedUnsuccessful("magic")));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response = std::make_unique<AddTaskResponse>();
    auto subtask_request = std::make_unique<AddSubTaskRequest>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(5);
    subtask_request->set_allocated_task(task1.release());
    subtask_request->set_allocated_parent(id.release());

    auto result = service->addSubtask(nullptr, subtask_request.get(), response.get());

    EXPECT_EQ(response->success(), false);
    EXPECT_EQ(response->error_message(), "magic");
}

TEST_F(GRPCServerTest, shouldAddSubtaskSuccessfully) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addSubtask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedSuccessful(TaskID::create(4))));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response = std::make_unique<AddTaskResponse>();
    auto subtask_request = std::make_unique<AddSubTaskRequest>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(3);
    subtask_request->set_allocated_task(task1.release());
    subtask_request->set_allocated_parent(id.release());

    auto result = service->addSubtask(nullptr, subtask_request.get(), response.get());

    EXPECT_EQ(response->success(), true);
    EXPECT_EQ(response->created_id().id(), 4);
}

TEST_F(GRPCServerTest, shouldGetAllTasksByPriority1) {
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    std::vector<ModelTaskDTO> model_tasks{task,task,task};
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getAllTasksByPriority)
            .Times(1)
            .WillOnce(Return(model_tasks));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response = std::make_unique<GetTasksResponse>();
    auto no_params =std::make_unique<EmptyRequest>();

    auto result = service->getAllTasksByPriority(nullptr, no_params.get(), response.get());

    EXPECT_EQ(response->tasks_size(), 3);
}


TEST_F(GRPCServerTest, shouldFailDeletingTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, deleteTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(4);


    auto result = service->deleteTask(nullptr, id.get(), response.get());
    EXPECT_EQ(response->error_message(),"error");
}


TEST_F(GRPCServerTest, shouldDeleteTaskSuccessfully) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, deleteTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto id= std::make_unique<TaskIDRequest>();
    id->set_id(4);

    auto result = service->deleteTask(nullptr, id.get(), response.get());
    EXPECT_EQ(response->success(), true);
}


TEST_F(GRPCServerTest, shouldCompleteTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, complete)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto id= std::make_unique<TaskIDRequest>();
    id->set_id(4);


    auto result = service->complete(nullptr, id.get(), response.get());
    EXPECT_EQ(response->success(), true);
}

TEST_F(GRPCServerTest, shouldFailCompleteTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, complete)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto id= std::make_unique<TaskIDRequest>();
    id->set_id(4);

    auto result = service->complete(nullptr, id.get(), response.get());
    EXPECT_EQ(response->success(), false);
}

TEST_F(GRPCServerTest, shouldFailPostponeTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, editTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    EXPECT_CALL(*data_mock, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));

    auto postponeRequest=  std::make_unique<PostponeRequest>();
    auto response= std::make_unique<RequstTaskResponse>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(3);
    postponeRequest->set_allocated_id(id.release());
    postponeRequest->set_date(boost::gregorian::day_clock::local_day().day_number());
    auto result = service->postponeTask(nullptr, postponeRequest.get(), response.get());
    EXPECT_EQ(response->success(), false);
}

TEST_F(GRPCServerTest, shouldPostponeTask) {
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, editTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));
    EXPECT_CALL(*data_mock, getTask)
            .Times(1)
            .WillOnce(Return(task));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto postponeRequest=  std::make_unique<PostponeRequest>();
    auto response= std::make_unique<RequstTaskResponse>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(3);
    postponeRequest->set_allocated_id(id.release());
    postponeRequest->set_date(boost::gregorian::day_clock::local_day().day_number());
    auto result = service->postponeTask(nullptr, postponeRequest.get(), response.get());
    EXPECT_EQ(response->success(), true);
}

TEST_F(GRPCServerTest, shouldNotEditTask) {

    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, editTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto editRequest = std::make_unique<EditRequest>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(3);
    editRequest->set_allocated_id(id.release());
    editRequest->set_allocated_task(task2.release());
    auto result = service->editTask(nullptr, editRequest.get(), response.get());
    EXPECT_EQ(response->success(), false);
}

TEST_F(GRPCServerTest, shouldEditTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, editTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto editRequest= std::make_unique<EditRequest>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(3);
    editRequest->set_allocated_id(id.release());
    editRequest->set_allocated_task(task2.release());
    auto result = service->editTask(nullptr, editRequest.get(), response.get());
    EXPECT_EQ(response->success(), true);
}

TEST_F(GRPCServerTest, shouldGetSubtasks) {
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    std::vector<ModelTaskDTO> model_tasks{task, task, task, task};
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getSubtasks)
            .Times(1)
            .WillOnce(Return(model_tasks));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<GetTasksResponse>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(5);

    auto result = service->getSubtasks(nullptr, id.get(), response.get());
    EXPECT_EQ(response->tasks_size(), 4);
}

TEST_F(GRPCServerTest, shouldGetTaskForToday) {
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    std::vector<ModelTaskDTO> model_tasks{task};
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getTasksForToday)
            .Times(1)
            .WillOnce(Return(model_tasks));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<GetTasksResponse>();
    auto no_params = std::make_unique<EmptyRequest>();

    auto result = service->getTasksForToday(nullptr, no_params.get(), response.get());
    EXPECT_EQ(response->tasks_size(),1);
}

TEST_F(GRPCServerTest, shouldGetEmptyVectorOfTaskForToday) {

    std::vector<ModelTaskDTO> model_tasks{};
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getTasksForToday)
            .Times(1)
            .WillOnce(Return(model_tasks));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<GetTasksResponse>();
    auto no_params = std::make_unique<EmptyRequest>();

    auto result = service->getTasksForToday(nullptr, no_params.get(), response.get());
    EXPECT_EQ(response->tasks_size(), 0);
}


TEST_F(GRPCServerTest, shouldGetTaskForWeek) {
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    std::vector<ModelTaskDTO> model_tasks{task,task,task};
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getTasksForWeek)
            .Times(1)
            .WillOnce(Return(model_tasks));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<GetTasksResponse>();
    auto no_params = std::make_unique<EmptyRequest>();

    auto result = service->getTasksForWeek(nullptr, no_params.get(), response.get());
    EXPECT_EQ(response->tasks_size(),3);
}


TEST_F(GRPCServerTest, shouldNotGetTask) {

    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response = std::make_unique<GetTaskByIDResponse>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(5);

    auto result = service->getTaskByID(nullptr, id.get(), response.get());
    EXPECT_EQ(result.ok() , false);
}

TEST_F(GRPCServerTest, shouldGetTask) {
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getTask)
            .Times(1)
            .WillOnce(Return(task));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response = std::make_unique<GetTaskByIDResponse>();
    auto id = std::make_unique<TaskIDRequest>();
    id->set_id(5);

    auto result = service->getTaskByID(nullptr, id.get(), response.get());
    EXPECT_EQ(result.ok() , true);
}

TEST_F(GRPCServerTest, shouldSave) {
    auto data_mock =  std::make_unique<DataMock>();
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    std::vector<ModelTaskDTO> model_tasks{task,task,task};
    std::vector<ModelTaskDTO> empty;
    EXPECT_CALL(*data_mock, getAllTasks)
            .Times(1)
            .WillOnce(Return(model_tasks));
    EXPECT_CALL(*data_mock, getParent)
            .Times(3)
            .WillRepeatedly(Return(std::nullopt));
    EXPECT_CALL(*data_mock, getSubtasks)
            .Times(3)
            .WillRepeatedly(Return(empty));
    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto persistentRequest = std::make_unique<PersistentRequest>();
    persistentRequest->set_filename("test.txt");
    auto result = service->save(nullptr, persistentRequest.get(), response.get());
    EXPECT_EQ(response->success(), true);
}

TEST_F(GRPCServerTest, shouldLoad) {
    auto data_mock =  std::make_unique<DataMock>();
    auto task = ModelTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    std::vector<ModelTaskDTO> model_tasks{task,task,task};
    std::vector<ModelTaskDTO> empty;
    EXPECT_CALL(*data_mock, getAllTasks)
            .Times(1)
            .WillOnce(Return(model_tasks));
    EXPECT_CALL(*data_mock, getParent)
            .Times(3)
            .WillRepeatedly(Return(std::nullopt));
    EXPECT_CALL(*data_mock, getSubtasks)
            .Times(3)
            .WillRepeatedly(Return(empty));

    auto service = std::make_unique<GRPCServer>(std::move(data_mock));
    auto response= std::make_unique<RequstTaskResponse>();
    auto persistentRequest = std::make_unique<PersistentRequest>();
    persistentRequest->set_filename("test.txt");
    auto result = service->save(nullptr, persistentRequest.get(), response.get());
    EXPECT_EQ(response->success(), true);

    service->load(nullptr, persistentRequest.get(), response.get());
    EXPECT_EQ(response->success(), true);

    auto tasks= std::make_unique<GetTasksResponse>();
    auto no_params= std::make_unique<EmptyRequest>();
    service->getAllTasksByPriority(nullptr, no_params.get(), tasks.get());
    EXPECT_EQ(tasks->tasks_size(), 3);
}
