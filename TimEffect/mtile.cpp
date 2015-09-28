#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "mtileHeader.h"
#include "turretHeader.h"
#include <fstream>

extern int Push_Tile;
extern int TILE_WIDTH;
extern int TOTAL_TILES;
extern int Solid_Tile;
extern int Level;
extern int left_turret;
extern int right_turret;
extern int break_Tile;
extern int pull;

//mtile constuctor
mTile:: mTile(int x, int y, int height, int width, int tileType)
    :Tile(x, y, height, width, tileType)
{    
    
    xVel = 0;
    yVel = 0;
    opX = x;
    opY = y;
    trap = false;
    
}
//if the player pushes against a movable tile then that tile will move
void mTile:: moveTile(Dot myDot , Tile *tiles[], mTile *mtiles[], turret *turrets[] ){
    Uint8 *keystates = SDL_GetKeyState( NULL );
    
    //if both the player and the block is on the ground
    if(myDot.touches_ground(myDot.box ,tiles, mtiles, turrets) == true && wall2ground(tiles, mtiles)== true)
    {
        //if the player presses x then the movement of the mtile is mapped to the player
        if(left_collision2(myDot.box, box)== true && get_type() == Push_Tile && keystates[ SDLK_x ])
        {   
             box.x = myDot.box.x + 50;
             pull = -1;
        }
        //this applies to both right and left collision
        else if(right_collision2(myDot.box, box)== true && get_type() == Push_Tile && keystates[ SDLK_x ])
        {  
             box.x = myDot.box.x - 80;
             pull = 1;
        }
    }
    // the break-away tile
    if( get_type() == break_Tile )
    {
        if(wall2ground(tiles, mtiles)== false && ground_collision(myDot.box, box))
        {
            trap = true;
        }
        //checks if the tile is not toucing the ground and the player colliding with it
        if(trap && wall2ground(tiles, mtiles)== false)
        {
            //if the so the tile falls until it hits the ground
            box.y += 10;    
        }
    }
    //if there is nothing under a mtile it will fall
    else if(wall2ground(tiles, mtiles)== false)
    {
        box.y += 10;
    }

}

bool mTile::wall2wall(Tile *tiles[], mTile *mtiles[], turret *turrets[])
{
    
    Uint8 *keystates = SDL_GetKeyState( NULL );
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a wall type, mtile or turret
        if( ( tiles[ t ]->get_type() == Solid_Tile) )  
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        if( ( mtiles[ t ]->get_type() == Push_Tile) && !(mtiles[ t ]->opX == opX && mtiles[ t ]->opY == opY ) )  
        {
            if( check_collision( box, mtiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        if( ( turrets[ t ]->get_type() == left_turret || turrets[ t ]->get_type() == right_turret) )  
        {
            if( check_collision( box, turrets[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        
    }

    //If no wall tiles were touched
    return false;
}

bool mTile::wall2ground(Tile *tiles[], mTile *mtiles[])
{
    
    Uint8 *keystates = SDL_GetKeyState( NULL );
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a wall tile or a turret tile
        if( ( tiles[ t ]->get_type() == Solid_Tile ) )  
        {
            //If the collision box touches the wall tile
            if( ground_collision( box, tiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        if( ( mtiles[ t ]->get_type() == Push_Tile ) )  
        {
            //If the collision box touches the wall tile
            if( ground_collision( box, mtiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

bool mTile::wall2right(Tile *tiles[], mTile *mtiles[], turret *turrets[])
{
    
    Uint8 *keystates = SDL_GetKeyState( NULL );
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //same as the wall2wall but specifies that it is a right wall that it is colliding with
        if( ( tiles[ t ]->get_type() == Solid_Tile) )  
        {
            //If the collision box touches the wall tile
            if( left_collision( box, tiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        if( ( mtiles[ t ]->get_type() == Push_Tile) && !(mtiles[ t ]->opX == opX && mtiles[ t ]->opY == opY ) )  
        {
            //If the collision box touches the wall tile
            if( left_collision( box, mtiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        if( ( turrets[ t ]->get_type() == left_turret || turrets[ t ]->get_type() == right_turret) )  
        {
            //If the collision box touches the wall tile
            if( left_collision( box, turrets[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        
    }

    //If no wall tiles were touched
    return false;
}

bool mTile::wall2left(Tile *tiles[], mTile *mtiles[], turret *turrets[])
{
    
    Uint8 *keystates = SDL_GetKeyState( NULL );
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //same as the wall2wall but specifies that it is a left wall that it is colliding with
        if( ( tiles[ t ]->get_type() == Solid_Tile) )  
        {
            //If the collision box touches the wall tile
            if( right_collision( box, tiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        if( ( mtiles[ t ]->get_type() == Push_Tile) && !(mtiles[ t ]->opX == opX && mtiles[ t ]->opY == opY ) )  
        {
            //If the collision box touches the wall tile
            if( right_collision( box, mtiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        if( ( turrets[ t ]->get_type() ==  left_turret  || turrets[ t ]->get_type() ==  right_turret) )  
        {
            //If the collision box touches the wall tile
            if( right_collision( box, turrets[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        
    }

    //If no wall tiles were touched
    return false;
}
