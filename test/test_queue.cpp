#include "stack_and_queue.h"
#include <gtest.h>

TEST(Queue, can_create_queue) {
	ASSERT_NO_THROW(Queue<int> queue);
}

TEST(Queue, can_check_for_empty)
{
    Queue<int> q;

    EXPECT_TRUE(q.IsEmpty());
}

TEST(Queue, can_check_for_full)
{
    Queue<int> q;
    
    EXPECT_FALSE(q.IsFull());
}

TEST(Queue, can_get_size)
{
    Queue<int> q;
    q.push(1);
    q.push(2);

    EXPECT_EQ(2, q.size());
}

TEST(Queue, can_get_capacity)
{
    Queue<int> q;

    ASSERT_NO_THROW(q.getcapacity());
}

TEST(Queue, can_push)
{
    Queue<int> q;
    q.push(1);
    q.push(2);

    EXPECT_EQ(2, q.getBack());
}

TEST(Queue, can_pop)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.pop();

    EXPECT_EQ(2, q.getBack());
}

TEST(qQueue, throws_when_pop_empty_Queue)
{
    Queue<int> q;

    ASSERT_ANY_THROW(q.pop());
}

TEST(Queue, can_get_back_element)
{
    Queue<int> q;
    q.push(1); 
    q.push(2);

    EXPECT_EQ(2, q.getBack());
}

TEST(Queue, can_get_front)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(1, q.getFront());
}