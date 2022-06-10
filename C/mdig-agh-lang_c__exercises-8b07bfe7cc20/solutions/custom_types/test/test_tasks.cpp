//#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" {
#include "tasks.h"
}

TEST(TasksTest, ChooseMoreImportantTask) {
    Task t1 = {1, LOW};
    Task t2 = {2, MEDIUM};

    const Task* important_task = choose_more_important_task(&t1, &t2);
    EXPECT_EQ(important_task, &t2);

    t1.priority = HIGH;
    important_task = choose_more_important_task(&t1, &t2);
    EXPECT_EQ(important_task, &t1);
}

TEST(TasksTest, LastTwoBits) {
    Task t = {3, LOW};
    transform_task(&t, increase_priority);
    EXPECT_EQ(t.priority, HIGH);

    t.priority = MEDIUM;
    transform_task(&t, increase_priority);
    EXPECT_EQ(t.priority, HIGH);
}
