#ifndef PADDLE_H
#define PADDLE_H

#include "Ball.h"

#include <SDL2/SDL.h>

class Paddle
{
    public:
        Paddle(int type);
        virtual ~Paddle();

        void render(SDL_Renderer* renderer);
        void update(Ball* b);
        void setDx(int x);

        int getX();
        int getY();

    private:
        int _x;
        int _y;
        int _width;
        int _height;
        int _dx;
        int _type;

        SDL_Rect rect;
};

#endif // PADDLE_H
