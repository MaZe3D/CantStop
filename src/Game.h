#pragma once
#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    bool m_isRunning;

    void eventHandler();
    void update();
    void render();

    void init();
};