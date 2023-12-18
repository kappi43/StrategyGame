#pragma once
#include "boost/statechart/state_machine.hpp"
class Init;
class GameEngineCore : public boost::statechart::state_machine<GameEngineCore, Init>
{
public:
	void init(); // wrapper for state_machine.initiate() to avoid undefined class error. 
};