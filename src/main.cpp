#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#else

#include <doctest.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int32_t windowWidth = 800;
int32_t windowHeight = 600;

void bakeFont(SDL_Renderer* renderer, TTF_Font* font, SDL_Surface** surface, SDL_Texture** texture) {
	if (*texture) SDL_DestroyTexture(*texture);
	if (*surface) SDL_FreeSurface(*surface);
	*surface = TTF_RenderText_Blended_Wrapped(font, "Welcome to this absolutely spectacular\nTEST WINDOW!", { 127, 64, 0 }, windowWidth);
	*texture = SDL_CreateTextureFromSurface(renderer, *surface);
}

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = SDL_CreateWindow("SDL2 - TEST WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	TTF_Font* font = TTF_OpenFont("res/beyond-wonderland.regular.ttf", 80);
	TTF_SetFontWrappedAlign(font, TTF_WRAPPED_ALIGN_CENTER);
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	bakeFont(renderer, font, &surface, &texture);
	int textureWidth, textureHeight;
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	SDL_Rect rect { 0, 0, textureWidth, textureHeight };

	SDL_Surface* img_surface = IMG_Load("res/git-logo.png");
	SDL_Texture* img_texture = SDL_CreateTextureFromSurface(renderer, img_surface);
	int img_textureWidth, img_textureHeight;
	SDL_QueryTexture(img_texture, NULL, NULL, &img_textureWidth, &img_textureHeight);
	SDL_Rect img_rect { 0, 0, img_textureWidth, img_textureHeight };

	bool moveTowardCenter = false;
	bool running = true;
	uint32_t timeA = 0, timeB = 0;
	SDL_Event event;
	while (running) {
		timeB = SDL_GetTicks();
		if (timeB-timeA >= 16) {
			timeA = timeB;
			SDL_RenderClear(renderer);
			SDL_Rect r { rect.x, rect.y + (windowHeight-textureHeight)/2, rect.w, rect.h };
			SDL_RenderCopy(renderer, texture, NULL, &r);
			SDL_RenderCopy(renderer, img_texture, NULL, &img_rect);
			SDL_RenderPresent(renderer);


			if (moveTowardCenter) {
				rect.x *= 0.9;
				rect.y *= 0.9;
			}
		}
		else {
			SDL_WaitEventTimeout(&event, timeB-timeA);
			switch (event.type) {
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_ENTER) moveTowardCenter = false;
					if (event.window.event == SDL_WINDOWEVENT_LEAVE) moveTowardCenter = true;
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						windowWidth = event.window.data1;
						windowHeight = event.window.data2;
						bakeFont(renderer, font, &surface, &texture);
						SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
						rect = { 0, (windowWidth-textureHeight)/2, textureWidth, textureHeight };
					}
					break;
				case SDL_MOUSEMOTION:
					rect.x = (event.motion.x-windowWidth/2)/5;
					rect.y = (event.motion.y-windowHeight/2)/5;
					break;
				case SDL_QUIT:
					running = false;
					break;
			}
		}
	}

	SDL_DestroyTexture(img_texture);
	SDL_FreeSurface(img_surface);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

#endif

TEST_CASE("sanity check") {
	REQUIRE(1 < 2);
	CHECK('a' != 'b');
	WARN('a'+1 == 'b');
}
