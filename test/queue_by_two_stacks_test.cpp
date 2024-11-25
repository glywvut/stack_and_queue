#include "stack_and_queue.h"
#include <gtest.h>

TEST(Queue_by_two_Stacks, can_create_Queue)
{
    ASSERT_NO_THROW(Queue_by_two_Stacks<int> q);
}

TEST(Queue_by_two_Stacks, can_check_for_empty)
{
    Queue_by_two_Stacks<int> q;

    EXPECT_TRUE(q.IsEmpty());
}

TEST(Queue_by_two_Stacks, can_check_for_full)
{
    Queue_by_two_Stacks<int> q;

    EXPECT_FALSE(q.IsFull());
}

TEST(Queue_by_two_Stacks, can_get_size)
{
    Queue_by_two_Stacks<int> q;
    q.push(1);
    q.push(2);

    EXPECT_EQ(2, q.size());
}

TEST(Queue_by_two_Stacks, can_push)
{
    Queue_by_two_Stacks<int> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(1, q.front());
}

TEST(Queue_by_two_Stacks, can_push_correct)
{
    Queue_by_two_Stacks<int> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(2, q.size());
}

TEST(Queue_by_two_Stacks, can_pop)
{
    Queue_by_two_Stacks<int> q;
    q.push(1);
    q.push(2);
    q.pop();

    EXPECT_EQ(2, q.front());
}

TEST(Queue_by_two_Stacks, can_pop_correct)
{
    Queue_by_two_Stacks<int> q;
    q.push(1);
    q.push(2);
    q.pop();

    EXPECT_EQ(1, q.size());
}

TEST(Queue_by_two_Stacks, can_get_front)
{
    Queue_by_two_Stacks<int> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(1, q.front());
}

TEST(Queue_by_two_Stacks, can_get_back)
{
    Queue_by_two_Stacks<int> q;
    q.push(1);
    q.push(2);

    EXPECT_EQ(2, q.back());
}