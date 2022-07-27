#include "Game.h"

void Game::eventHandler() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type) {
        case SDL_QUIT:
            m_gameState = GameState::EXIT;
            break;
        default:
            break;
        }
    }
}

void Game::render() {

}

void Game::init(char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized" << std::endl;
        m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(m_window)
        {
            std::cout << "Window created" << std::endl;
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);
            if(m_renderer)
            {
                std::cout << "Renderer created" << std::endl;
                SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                m_gameState = GameState::MENU;
            }
            else
            {
                std::cout << "Renderer failed to create!" << std::endl;
                m_gameState = GameState::EXIT;
            }
        }
        else {
            std::cout << "Window failed to create!" << std::endl;
            m_gameState = GameState::EXIT;
        }
    }
}

Game::~Game() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

Game::Game(char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    const int minimalWindowWidth = 800;
    const int minimalWindowHeight = 600;
    if (width < minimalWindowWidth) {
        throw std::invalid_argument("Width must be greater than " + std::to_string(minimalWindowWidth) + "px");
    }

    if(height < minimalWindowHeight) {
        throw std::invalid_argument("Height must be greater than " + std::to_string(minimalWindowHeight) + "px");
    }

    init(title, xpos, ypos, width, height, fullscreen);
}

void Game::run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameTime;
    while (m_gameState != GameState::EXIT) {
        frameStart = SDL_GetTicks();

        eventHandler();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        std::cout << "Loop time: " << frameTime << "ms" << std::endl;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}