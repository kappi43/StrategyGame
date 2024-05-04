#pragma once
#include <random>
namespace Rng
{
	struct RngDevice
	{
		virtual int getRandomInt(int from, int to) const
		{
			std::random_device r;
			std::default_random_engine e1(r());
			std::uniform_int_distribution<int> uniform_dist(from, to);
			return uniform_dist(e1);
		}
	};
}
