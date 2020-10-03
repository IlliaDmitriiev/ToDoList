//
// Created by illia on 14.08.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Core/api/TaskService.h"

using ::testing::Return;

class TaskServiceTest : public ::testing::Test {
public:
  
    void SetUp() override{
         
    }
};

class DataMock : public DataInterface {

public:
    MOCK_METHOD(AddTaskResult, addTask,(const ModelTaskDTO &taskDto), (override));
    MOCK_METHOD(AddTaskResult, addSubtask,(TaskID taskID, const ModelTaskDTO &subtask), (override));
    MOCK_METHOD(RequstTaskResult, deleteTask,(TaskID id), (override));
    MOCK_METHOD(RequstTaskResult, complete,(TaskID id), (override));
    MOCK_METHOD(RequstTaskResult, editTask,(TaskID id, const ModelTaskDTO &subtask), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getSubtasks,(TaskID id), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getAllTasks,(), (override));
    MOCK_METHOD(std::optional<ModelTaskDTO>, getTask,(TaskID id), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getAllTasksByPriority,(), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksForToday,(), (override));
    MOCK_METHOD(std::vector<ModelTaskDTO>, getTasksForWeek,(), (override));
    MOCK_METHOD(bool, removeTask, (const std::weak_ptr<FullTask> &task), (override));
};

TEST_F(TaskServiceTest, shouldAddTaskSuccessfully) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedSuccessful(TaskID::create(5))));
    auto service = std::make_unique<TaskService>(std::move(data_mock));
    auto task = ServiceTaskDTO::create(TaskID::create(147),
                                       boost::gregorian::date(2020,10,10),
                                       "name",
                                       "label",
                                       TaskPriority::Second,
                                       true);
    auto result = service->addTask(task);
    EXPECT_EQ(result.result, ResultType::SUCCESS);
    EXPECT_EQ(result.id.value().getId(),5);
}

TEST_F(TaskServiceTest, shouldAddTaskUnsuccessfully1) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedUnsuccessful("magic")));
    auto service = std::make_unique<TaskService>(std::move(data_mock));
    auto task = ServiceTaskDTO::create(TaskID::create(147),
                                       boost::gregorian::date(2020,10,10),
                                       "name",
                                       "label",
                                       TaskPriority::Second,
                                       true);
    auto result = service->addTask(task);
    EXPECT_EQ(result.result, ResultType::FAILURE);
    EXPECT_EQ(result.error_message, "magic");
}

TEST_F(TaskServiceTest, shouldFailAddSubtask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addSubtask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedUnsuccessful("magic")));
    auto service = std::make_unique<TaskService>(std::move(data_mock));
    auto task = ServiceTaskDTO::create(TaskID::create(147),
                                       boost::gregorian::date(2020,10,10),
                                       "name",
                                       "label",
                                       TaskPriority::Second,
                                       true);
    auto result = service->addSubtask(TaskID::create(11545080), task);
    EXPECT_EQ(result.result, ResultType::FAILURE);
    EXPECT_EQ(result.error_message, "magic");
}

TEST_F(TaskServiceTest, shouldAddSubtaskSuccessfully) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, addSubtask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedSuccessful(TaskID::create(4))));
    auto service = std::make_unique<TaskService>(std::move(data_mock));
    auto task = ServiceTaskDTO::create(TaskID::create(147),
                                       boost::gregorian::date(2020,10,10),
                                       "name",
                                       "label",
                                       TaskPriority::Second,
                                       true);
    auto result = service->addSubtask(TaskID::create(11545080), task);
    EXPECT_EQ(result.result, ResultType::SUCCESS);
    EXPECT_EQ(result.id.value().getId(), 4);
}

TEST_F(TaskServiceTest, shouldGetAllTasksByPriority1) {
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
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->getAllTasksByPriority();
    EXPECT_EQ(result.size(), 3);
}


TEST_F(TaskServiceTest, shouldFailDeletingTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, deleteTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->deleteTask(TaskID::create(4));
    EXPECT_EQ(result.error_message,"error");
}


TEST_F(TaskServiceTest, shouldDeleteTaskSuccessfully) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, deleteTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->deleteTask(TaskID::create(4));
    EXPECT_EQ(result.result, ResultType::SUCCESS);
}


TEST_F(TaskServiceTest, shouldCompleteTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, deleteTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->deleteTask(TaskID::create(4));
    EXPECT_EQ(result.result, ResultType::SUCCESS);
}

TEST_F(TaskServiceTest, shouldFailCompleteTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, complete)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->complete(TaskID::create(4));
    EXPECT_EQ(result.result, ResultType::FAILURE);
}

TEST_F(TaskServiceTest, shouldFailPostponeTask) {
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, editTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    EXPECT_CALL(*data_mock, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->postponeTask(TaskID::create(4),  boost::gregorian::date(2020,10,10));
    EXPECT_EQ(result.result, ResultType::FAILURE);
}

TEST_F(TaskServiceTest, shouldPostponeTask) {
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
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->postponeTask(TaskID::create(4),  boost::gregorian::date(2020,10,10));
    EXPECT_EQ(result.result, ResultType::SUCCESS);
}

TEST_F(TaskServiceTest, shouldNotEditTask) {
    auto task = ServiceTaskDTO::create(TaskID::create(147),
                                     boost::gregorian::date(2020,10,10),
                                     "name",
                                     "label",
                                     TaskPriority::Second,
                                     true);
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, editTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedUnsuccessful("error")));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->editTask(TaskID::create(4), task);
    EXPECT_EQ(result.result, ResultType::FAILURE);
}

TEST_F(TaskServiceTest, shouldEditTask) {
    auto task = ServiceTaskDTO::create(TaskID::create(147),
                                       boost::gregorian::date(2020,10,10),
                                       "name",
                                       "label",
                                       TaskPriority::Second,
                                       true);
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, editTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->editTask(TaskID::create(4), task);
    EXPECT_EQ(result.result, ResultType::SUCCESS);
}

TEST_F(TaskServiceTest, shouldGetSubtasks) {
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
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->getSubtasks(TaskID::create(5));
    EXPECT_EQ(result.size(), 4);
}

TEST_F(TaskServiceTest, shouldGetTaskForToday) {
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
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->getTasksForToday();
    EXPECT_EQ(result.size(), 1);
}

TEST_F(TaskServiceTest, shouldGetEmptyVectorOfTaskForToday) {

    std::vector<ModelTaskDTO> model_tasks{};
    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getTasksForToday)
            .Times(1)
            .WillOnce(Return(model_tasks));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->getTasksForToday();
    EXPECT_TRUE(result.empty());
}


TEST_F(TaskServiceTest, shouldGetTaskForWeek) {
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
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->getTasksForWeek();
    EXPECT_EQ(result.size(), 3);
}


TEST_F(TaskServiceTest, shouldNotGetTask) {

    auto data_mock =  std::make_unique<DataMock>();
    EXPECT_CALL(*data_mock, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->getTask(TaskID::create(1));
    EXPECT_FALSE(result.has_value());
}

TEST_F(TaskServiceTest, shouldGetTask) {
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
    auto service = std::make_unique<TaskService>(std::move(data_mock));

    auto result = service->getTask(TaskID::create(4));
    EXPECT_TRUE(result.has_value());
}
