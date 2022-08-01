#include "MersenneTwister.h"

MersenneTwister::MersenneTwister(long long seed)
	: rand_gen(seed) {
}

MersenneTwister::MersenneTwister()
    : rand_gen(std::random_device()()) {
}

long long MersenneTwister::getRandomInt(long long min, long long max) {
	return rand_gen() % (max - min) + min;
}

long long MersenneTwister::getRandomInt(long long max) {
	return getRandomInt(0, max);
}