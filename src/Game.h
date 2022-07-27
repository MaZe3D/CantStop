#pragma once
#include <SDL2/SDL.h>

class Game
{
public:
    Game(/* args */);
    ~Game();

    void run();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool m_isRunning;

    //Methods
    void eventHandler();
    void update();
    void render();

    void init();
};