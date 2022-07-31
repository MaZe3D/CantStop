#ifdef NDEBUG

#define DEBUG_LOG(msg) ;
#define DEBUG_LOG_NO_NL(msg) ;

#else

#include <iostream>
#define DEBUG_LOG(msg)       std::cout << __FILE__ << ":" << __LINE__ << " - " <<  msg << std::endl;
#define DEBUG_LOG_NO_NL(msg) std::cout <<  msg;

#endif
