#pragma once
#include "boost/statechart/state_machine.hpp"
#include <memory>
#include "IMessageGetter.h"
class Init;
class GameEngineCore : public boost::statechart::state_machine<GameEngineCore, Init>
{
public:
	GameEngineCore(std::shared_ptr<IMessageGetter>);
	void init(); // wrapper for state_machine.initiate() to avoid undefined class error. 
private:
	std::shared_ptr<IMessageGetter> messageGetter;
};