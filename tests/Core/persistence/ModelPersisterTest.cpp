//
// Created by ilya on 04.10.2020.
//

#include <gtest/gtest.h>
#include "Core/persistence/ModelPersister.h"
#include "Core/persistence/PriorityConvertor.h"
#include "Core/model/DataHolderCreator.h"

class ModelPersisterTest: public ::testing::Test {

};

TEST_F(ModelPersisterTest, shouldSave) {

    auto model = todo_list_model::createDataHolder();

    auto modelTask = ModelTaskDTO::create(TaskID::create(4),
                                          boost::gregorian::date(2000, 10, 10),
                                          "name",
                                          "label",
                                          TaskPriority::First,
                                          true);
    auto result = model->addTask(modelTask);
    auto subtask_result = model->addSubtask(result.id.value(), modelTask);
    model->addSubtask(subtask_result.id.value(), modelTask);
    std::fstream file("file1.txt", std::fstream::out);
    auto persister = std::make_unique<ModelPersister>(*model, file);
    EXPECT_TRUE(persister->save());

}

TEST_F(ModelPersisterTest, shouldLoad) {
    {
        auto model = todo_list_model::createDataHolder();

        auto modelTask = ModelTaskDTO::create(TaskID::create(4),
                                               boost::gregorian::date(2000, 10, 10),
                                               "name",
                                               "label",
                                               TaskPriority::First,
                                               true);
        auto result = model->addTask(modelTask);
        auto subtask_result = model->addSubtask(result.id.value(), modelTask);
        model->addSubtask(subtask_result.id.value(), modelTask);
        std::fstream file("file1.txt", std::fstream::out);
        auto persister = std::make_unique<ModelPersister>(*model, file);
        persister->save();
    }
    auto model = todo_list_model::createDataHolder();
    std::fstream file("file1.txt", std::fstream::in);
    auto persister = std::make_unique<ModelPersister>(*model, file);
    EXPECT_TRUE(persister->load());
    EXPECT_EQ(model->getAllTasks().size(), 3);
    EXPECT_TRUE(model->getAllTasks()[0].isCompleted());
}
