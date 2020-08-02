//
// Created by Илля on 02.08.2020.
//

#include <gtest/gtest.h>
#include "StorageByPrior.h"

const Task t1 = Task::create(
        Date::create(2020, 7, 31),
        "name1",
        "",
        Task::Priority::None);

const Task t2 = Task::create(
        Date::create(2020, 7, 31),
        "name2",
        "456578y&#&@)(#$?><</*-+fdg",
        Task::Priority::Second);


const Task t3 = Task::create(
        Date::create(1500, 2, 26),
        "name3",
        "label3",
        Task::Priority::Third);

const Task t4 = Task::create(
        Date::create(1500, 3, 4),
        "name4",
        "",
        Task::Priority::First);

const Task t5 = Task::create(
        Date::create(1500, 2, 28),
        "",
        "",
        Task::Priority::None);

class StorageByPriorTest : public ::testing::Test {
public:
    StorageByPrior storage;
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;
    std::shared_ptr<FullTask> sft5;

    StorageByPriorTest() {
        FullTask ft1 = FullTask::create(gen, t1);
        FullTask ft2 = FullTask::create(gen, t2);
        FullTask ft3 = FullTask::create(gen, t3);
        FullTask ft4 = FullTask::create(gen, t4);
        FullTask ft5 = FullTask::create(gen, t5);

        sft1 = std::make_shared<FullTask>(ft1);
        sft2 = std::make_shared<FullTask>(ft2);
        sft3 = std::make_shared<FullTask>(ft3);
        sft4 = std::make_shared<FullTask>(ft4);
        sft5 = std::make_shared<FullTask>(ft5);
    }

};

TEST_F(StorageByPriorTest, shoulPutFullTasksIntoRightPlace) {

    storage.putTaskInRightPlace(sft1);
    storage.putTaskInRightPlace(sft2);
    storage.putTaskInRightPlace(sft3);
    storage.putTaskInRightPlace(sft4);
    storage.putTaskInRightPlace(sft5);

    auto vecPriorFirst = storage.getVFirstPrior();
    auto vecPriorSecond = storage.getVSecondPrior();
    auto vecPriorThird = storage.getVThirdPrior();
    auto vecPriorNone = storage.getVNonePrior();

    ASSERT_EQ(1, vecPriorFirst.size());
    ASSERT_EQ(1, vecPriorSecond.size());
    ASSERT_EQ(1, vecPriorThird.size());
    ASSERT_EQ(2, vecPriorNone.size());

    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getDate().getMounth(), 3);
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getDate().getDay(), 4);
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getName(), "name4");
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getPrior(), Task::Priority::First);

    ASSERT_EQ(vecPriorSecond[0].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vecPriorSecond[0].lock()->getTask().getDate().getMounth(), 7);
    ASSERT_EQ(vecPriorSecond[0].lock()->getTask().getDate().getDay(), 31);
    ASSERT_EQ(vecPriorSecond[0].lock()->getTask().getName(), "name2");
    ASSERT_EQ(vecPriorSecond[0].lock()->getTask().getLabel(), "456578y&#&@)(#$?><</*-+fdg");
    ASSERT_EQ(vecPriorSecond[0].lock()->getTask().getPrior(), Task::Priority::Second);

    ASSERT_EQ(vecPriorThird[0].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vecPriorThird[0].lock()->getTask().getDate().getMounth(), 2);
    ASSERT_EQ(vecPriorThird[0].lock()->getTask().getDate().getDay(), 26);
    ASSERT_EQ(vecPriorThird[0].lock()->getTask().getName(), "name3");
    ASSERT_EQ(vecPriorThird[0].lock()->getTask().getLabel(), "label3");
    ASSERT_EQ(vecPriorThird[0].lock()->getTask().getPrior(), Task::Priority::Third);

    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getDate().getMounth(), 7);
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getDate().getDay(), 31);
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getName(), "name1");
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getPrior(), Task::Priority::None);

    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getDate().getMounth(), 2);
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getDate().getDay(), 28);
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getName(), "");
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getPrior(), Task::Priority::None);

}

TEST_F(StorageByPriorTest, shoulDeleteDanglingPointers) {

    storage.putTaskInRightPlace(sft1);
    storage.putTaskInRightPlace(sft2);
    storage.putTaskInRightPlace(sft3);
    storage.putTaskInRightPlace(sft4);
    storage.putTaskInRightPlace(sft5);

    sft2.reset();
    sft3.reset();
    storage.deleteDanglingPointers();

    auto vecPriorFirst = storage.getVFirstPrior();
    auto vecPriorSecond = storage.getVSecondPrior();
    auto vecPriorThird = storage.getVThirdPrior();
    auto vecPriorNone = storage.getVNonePrior();


    ASSERT_EQ(1, vecPriorFirst.size());
    ASSERT_EQ(0, vecPriorSecond.size());
    ASSERT_EQ(0, vecPriorThird.size());
    ASSERT_EQ(2, vecPriorNone.size());

    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getDate().getMounth(), 3);
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getDate().getDay(), 4);
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getName(), "name4");
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vecPriorFirst[0].lock()->getTask().getPrior(), Task::Priority::First);

    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getDate().getMounth(), 7);
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getDate().getDay(), 31);
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getName(), "name1");
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vecPriorNone[0].lock()->getTask().getPrior(), Task::Priority::None);

    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getDate().getMounth(), 2);
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getDate().getDay(), 28);
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getName(), "");
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vecPriorNone[1].lock()->getTask().getPrior(), Task::Priority::None);

}
