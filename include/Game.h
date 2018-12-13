#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

enum class GameState {PLAY, EXIT};

class Game
{
public:
    Game(const char* title,
                int width,
                int height,
                bool fullscreen);
    virtual ~Game();

    bool init();
    void run();

    bool gameOver;
    int getPaddleX();
    int getPaddleY();

private:
    SDL_Window* _gWindow;
    SDL_Renderer* _gRenderer;

    int _gScreenWidth;
    int _gScreenHeight;

    const int FPS = 200;
    const int frameDelay = 1000/FPS;
    int frameTime;
    Uint32 frameStart;

    bool _fullScreen;

    const char* _title;

    void clean();
    void _handleEvents();
    void _gameLoop();
    void _render();

    GameState _gameState;
};

#endif // GAME_H
