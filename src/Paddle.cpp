#include "Paddle.h"
#include <stdio.h>

#define S_WIDTH 400
#define S_HEIGHT 600

Paddle::Paddle(int type)
{
    _type = type;
    _width = 70;
    _height = 20;

    switch(type)
    {
    case 1:
        _x = S_WIDTH/2 - _width;
        _y = 0;
        break;
    case 2:
        _x = S_WIDTH/2 - _width;
        _y = S_HEIGHT - _height;
        _dx = 0;
        break;
    default:
        printf("Invalid paddle type!\n");
        break;
    }

    rect.w = _width;
    rect.h = _height;
    rect.x = _x;
    rect.y = _y;
}

Paddle::~Paddle()
{
}

void Paddle::setDx(int x)
{
    _dx = x;
}

int Paddle::getX()
{
    return _x;
}

int Paddle::getY()
{
    return _y;
}

void Paddle::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &rect);
}

void Paddle::update(Ball *b)
{
    switch (_type)
    {
    case 1:
        _x = b->getX()+(b->getWidth()/2) - (_width/2);
        break;
    case 2:
        _x += _dx;
        break;
    default:
        break;
    }

    if (_x < 0)
    {
        _x = 0;
    }
    else if (_x+_width > S_WIDTH)
    {
        _x = S_WIDTH-_width;
    }

    rect.x = _x;
}
