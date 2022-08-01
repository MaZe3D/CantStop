#include "MersenneTwister.h"
#include "util/log.h"
#include <stdexcept>

MersenneTwister::MersenneTwister(long long seed)
	: rand_gen(seed) {
}

MersenneTwister::MersenneTwister()
    : rand_gen(std::random_device()()) {
}

long long MersenneTwister::getRandomInt(long long min, long long max) {

    if (min > max + 1)
        throw std::invalid_argument("Mersenne Twister: min must be less than max + 1");
    
    const long long rand = rand_gen() % (max + 1 - min) + min;
    return rand;
}

long long MersenneTwister::getRandomInt(long long max) {
	return getRandomInt(0, max);
}