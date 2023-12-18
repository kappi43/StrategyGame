#include "GameEngineCore.hpp"
#include "boost/statechart/simple_state.hpp"
#include "glog/logging.h"
void GameEngineCore::init()
{
	this->initiate();
}
class Init : public boost::statechart::simple_state<Init, GameEngineCore>
{
public:
	Init()
	{
		LOG(INFO) << "Entering Init state";
	}
	~Init()
	{
		LOG(INFO) << "Exiting Init state";
	}
};