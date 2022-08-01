#pragma once
#include <random>

class MersenneTwister {
public:
	MersenneTwister(long long seed);
	MersenneTwister();
	
	long long getRandomInt(long long min, long long max);
	long long getRandomInt(long long max);

private:
	std::mt19937_64 rand_gen;
};