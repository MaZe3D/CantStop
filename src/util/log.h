#ifdef NDEBUG

#define DEBUG_LOG(msg) ;

#else

#include <iostream>
#define DEBUG_LOG(msg) \
	std::cout << __FILE__ << ":" << __LINE__ << " - " <<  msg << std::endl;

#endif
