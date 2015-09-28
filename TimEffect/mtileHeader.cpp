#include "SDL.h"
#ifndef MTILEHEADER
#define MTILEHEADER

class mTile: public Tile
{
    public:
    int xVel;
    int yVel;
    mTile(int x, int y, int tileType, int xVel, int yVel);
    void moveTile(SDL_Rect b);
};

#endif
