#include <stdexcept>
#include <string>

#define SDL_CALL(call) \
	SDL_ClearError(); \
	if ((call) != 0) \
		throw std::runtime_error(__FILE__ ":" + std::to_string(__LINE__) + " - failed SDL call:\n" + #call + "\n" + SDL_GetError());

#define SDL_CALL_INV(call) SDL_CALL(!(call))
