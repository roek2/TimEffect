#include "SDL.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "tileHeader.h"
#include <fstream>

extern int TILE_WIDTH;
extern int TILE_HEIGHT;

extern bool blending;
extern int alpha;

extern SDL_Surface *screen;
extern SDL_Surface *tileSheet;
extern SDL_Surface *tileSheet2;

extern SDL_Rect clips[];

extern SDL_Rect camera;

Tile::Tile( int x, int y, int height, int width, int tileType )
{
    //Get the offsets
    box.x = x;
    box.y = y;

    //Set the collision box
    box.w = width;
    box.h = height;

    //Get the tile type
    type = tileType;
    
}


void Tile::show()
{
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
        //used for blending the image for the present tiles with the images foe the past tiles
            SDL_SetAlpha( tileSheet2, SDL_SRCALPHA, alpha );
            apply_surface( box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[ type ] );
            apply_surface( box.x - camera.x, box.y - camera.y, tileSheet2, screen, &clips[ type ] );
    }
}

//return the type of the tile
int Tile::get_type()
{
    return type;
}

//returns the sedl rect of that tile
SDL_Rect Tile::get_box()
{
    return box;
}
