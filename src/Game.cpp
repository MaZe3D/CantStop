#include "Game.h"

void Game::eventHandler()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::update()
{

}

void Game::render()
{

}

void Game::init()
{

}

Game::Game()
{
    init();
}

void Game::run()
{
    init();
    m_isRunning = true;
    while (m_isRunning)
    {
        eventHandler();
        update();
        render();
    }
}