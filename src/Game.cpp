#include "Game.h"
#include <stdio.h>
#include "Ball.h"
#include "Paddle.h"

Ball* ball = NULL;
Paddle* ai_paddle = NULL;
Paddle* human_paddle = NULL;

Game::Game(const char* title,
                int width,
                int height,
                bool fullscreen)
{
    gameOver = false;
    _title = title;
    _gameState = GameState::PLAY;
    _gScreenHeight = height;
    _gScreenWidth = width;
    _fullScreen = fullscreen;
    _gRenderer = NULL;
    _gWindow == NULL;

    ball = new Ball(width/2, height/2, 30, 30);
    ai_paddle = new Paddle(1);
    human_paddle = new Paddle(2);
}

Game::~Game()
{
    ball->close();
    clean();
}

int Game::getPaddleX()
{
    return human_paddle->getX();
}

int Game::getPaddleY()
{
    return human_paddle->getY();
}

bool Game::init()
{
    bool success = true;
    int flags = SDL_WINDOW_OPENGL;
    if (_fullScreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Could not initialize SDL. SDL_Error: %s", SDL_GetError());
        success = false;
    }
    else
    {
        _gWindow = SDL_CreateWindow(_title,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    _gScreenWidth,
                                    _gScreenHeight,
                                    flags);
        if (_gWindow == NULL)
        {
            printf("Could not create SDL window. SDL_Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            _gRenderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (_gRenderer == NULL)
            {
                printf("Could not create SDL_Renderer. SDL_Error: %s", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(_gRenderer, 0, 0, 152, 255);
                SDL_RenderClear(_gRenderer);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not be initialized! SDl_image error: %s\n",
                           IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

void Game::_handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_KEYDOWN:
            if (!gameOver)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    human_paddle->setDx(-1);
                    break;
                case SDLK_RIGHT:
                    human_paddle->setDx(1);
                    break;
                default:
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
}

void Game::_gameLoop()
{
    while (_gameState != GameState::EXIT)
    {
        frameStart = SDL_GetTicks();

        _handleEvents();
        if (!gameOver)
        {
            ball->update(this);
        }
        ai_paddle->update(ball);
        human_paddle->update(ball);
        _render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }
}

void Game::_render()
{
    SDL_SetRenderDrawColor(_gRenderer, 59, 89, 152, 255); // set the color of the renderer
	SDL_RenderClear(_gRenderer); // Clear the current rendering target with the drawing color.

	// Do the drawing here
	ball->render(_gRenderer);
	ai_paddle->render(_gRenderer);
	human_paddle->render(_gRenderer);

	SDL_RenderPresent(_gRenderer); // Update the screen.
}

void Game::run()
{
    if (init())
    {
        _gameLoop();
    }
    else
    {
        printf("Something is wrong! Never give up!");
        _gameState = GameState::EXIT;
    }
}

void Game::clean()
{
    if (_gameState == GameState::EXIT)
    {
        SDL_Quit();
        SDL_DestroyRenderer(_gRenderer);
        SDL_DestroyWindow(_gWindow);
        _gRenderer = NULL;
        _gWindow == NULL;
    }
}
