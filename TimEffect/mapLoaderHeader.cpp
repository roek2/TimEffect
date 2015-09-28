#include "SDL.h"
#ifndef MAPLOADERHEADER
#define MAPLOADERHEADER

class Tile;
class mTile;

class mapLoader
{
    public:
        void clip_tiles(SDL_Rect box);
        bool set_tiles( Tile *tiles[], mTile *mtiles[] );
}
