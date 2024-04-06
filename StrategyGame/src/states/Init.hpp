#pragma once
#include "boost/statechart/state.hpp"
#include <boost/statechart/event.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <zmq.hpp>
#include "glog/logging.h"
#include "gameEngine/GameEngineCore.hpp"
#include <boost/mpl/list.hpp>
#include "events/EventCloseEngine.hpp"

struct EventMessageArrival;
struct EventCloseEngine;
class Init : public boost::statechart::state<Init, GameEngineCore>
{
	zmq::send_result_t sendFromEngine(zmq::message_t& msg)
	{
		return outermost_context().sendBack(msg);
	}

	void synchronize();

public:
	Init(my_context context);

	typedef boost::mpl::list<
		boost::statechart::custom_reaction< EventMessageArrival>,
		boost::statechart::custom_reaction< EventCloseEngine >
	> reactions;

	boost::statechart::result react(const EventMessageArrival&);
	boost::statechart::result react(const EventCloseEngine&);

	~Init()
	{
		LOG(INFO) << "Exiting Init state";
	}
};
