#pragma once
#include <SDL2/SDL.h>

class Game
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool m_isRunning;

    //Methods
    void eventHandler();
    void update();
    void render();

    void init();

public:
    Game(/* args */);
    ~Game();

    void run();
};