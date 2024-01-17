#include <gtest/gtest.h>
#include "MessageQueue.hpp"
#include <thread>
#include "zmq.hpp"

class MessageQueueTestsFixture : public testing::Test
{
protected:
	MessageQueueTestsFixture() : sut{}
	{}
	MessageQueue sut;
};

TEST_F(MessageQueueTestsFixture, canSimultaneuslyReadAndWrite)
{
	std::thread writer{ [&]() {
		for (int i = 0; i <= 100000; ++i)
		{
			sut.push_msg(zmq::message_t{ "Hello" , 5});
		}
		} };
	std::thread reader{ [&]() {
		zmq::message_t m{};
		for (int i = 0; i <= 100000; ++i)
		{
			m.move(sut.get_msg());
			ASSERT_TRUE(m.size() > 0);
		}
		} };
	writer.join();
	reader.join();
}