#include "Ball.h"

#define S_WIDTH 400
#define S_HEIGHT 600

#define PADDLE_HEIGHT 20
#define PADDLE_WIDTH 70

Ball::Ball(int x, int y, int w, int h)
{
    _gTexture = NULL;
    _x = x;
    _y = y;
    _dx = 1;
    _dy = 1;
    _width = w;
    _height = h;
}

Ball::~Ball()
{
}

int Ball::getX()
{
    return _x;
}

int Ball::getY()
{
    return _y;
}

int Ball::getWidth()
{
    return _width;
}

int Ball::getHeight()
{
    return _height;
}

SDL_Texture* Ball::_loadTexture(std::string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path.c_str(), IMG_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n",
                   path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool Ball::loadMedia(SDL_Renderer* renderer)
{
    bool success = true;
    _gTexture = _loadTexture("ball.png", renderer);
    if (_gTexture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    return success;
}

void Ball::render(SDL_Renderer* renderer)
{
    if (loadMedia(renderer))
    {
        SDL_Rect destR;

        destR.x = _x;
        destR.y = _y;
        destR.w = _width;
        destR.h = _height;

        SDL_RenderCopy(renderer, _gTexture, NULL, &destR);

        SDL_DestroyTexture(_gTexture);
        _gTexture = NULL;
        IMG_Quit();
    }
    else
    {
        printf("Could not load media!\n");
    }
}

void Ball::update(Game* game)
{
    _x += _dx;
    _y += _dy;

    int wi = _width;
    int hi = _height;

    if (_x<0 || _x+_width>S_WIDTH)
    {
        _dx *= -1;
    }

    if (_y < PADDLE_HEIGHT)
    {
        _dy *= -1;
    }


    if (_y + _height > game->getPaddleY())
    {
        if (_x > game->getPaddleX() && _x+_width < game->getPaddleX()+PADDLE_WIDTH)
        {
            _dy *= -1;
        }
    }


    if (_y + _height > S_HEIGHT)
    {
        game->gameOver = true;
    }
}

void Ball::close()
{
    SDL_DestroyTexture(_gTexture);
    _gTexture = NULL;
    IMG_Quit();
}
