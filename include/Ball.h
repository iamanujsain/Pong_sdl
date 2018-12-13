#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "Game.h"

class Ball
{
    public:
        Ball(int x, int y, int w, int h);
        virtual ~Ball();

        void close();
        bool loadMedia(SDL_Renderer* renderer);
        void render(SDL_Renderer* renderer);
        void update(Game* game);

        int getX();
        int getY();
        int getWidth();
        int getHeight();

    private:
        SDL_Texture* _loadTexture(std::string path, SDL_Renderer* renderer);
        SDL_Texture* _gTexture;

        int _x;
        int _y;
        int _dx;
        int _dy;
        int _width;
        int _height;
};

#endif // BALL_H
