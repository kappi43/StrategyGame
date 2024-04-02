#pragma once
struct EventMessageArrival : boost::statechart::event< EventMessageArrival >
{
	const zmq::message_t& msg;
	EventMessageArrival(const zmq::message_t& p_msg) :msg{ p_msg }
	{}
};