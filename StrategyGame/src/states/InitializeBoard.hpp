#pragma once
#include "boost/statechart/state.hpp"
#include "gameEngine/GameEngineCore.hpp"
#include <boost/statechart/custom_reaction.hpp>
#include <events/EventMessageArrival.hpp>
#include <events/EventCloseEngine.hpp>
#include <boost/mpl/list.hpp>
namespace GameEngine
{
	class ReqWrapper;
}
namespace Rng
{
	struct RngDevice;
}
class InitializeBoard : public boost::statechart::state<InitializeBoard, GameEngineCore>
{
	void setup_board(const GameEngine::ReqWrapper&);
public:
	InitializeBoard(my_context context);
	typedef boost::mpl::list<
		boost::statechart::custom_reaction< EventMessageArrival >,
		boost::statechart::custom_reaction< EventCloseEngine >
	> reactions;
	boost::statechart::result react(const EventMessageArrival&);
	boost::statechart::result react(const EventCloseEngine&);
	~InitializeBoard()
	{
	}
	
};
