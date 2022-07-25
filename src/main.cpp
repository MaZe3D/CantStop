#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#else

#include "doctest/doctest.h"
#include <iostream>

int main() {
	std::cout << "Hello World!!" << std::endl;
	std::cin.get();
	return 0;
}

#endif

TEST_CASE("sanity check") {
	REQUIRE(1 < 2);
	CHECK('a' != 'b');
	WARN('a'+1 == 'b');
}
