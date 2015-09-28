#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "mtileHeader.h"
#include "turretHeader.h"
#include <fstream>
using namespace std;

extern int TOTAL_TILES;
extern int Solid_Tile;
extern int Push_Tile;
extern int left_turret;
extern int right_turret;
extern SDL_Surface *pixel;
extern SDL_Surface *screen;
extern SDL_Rect camera;
extern bool dead;
extern Mix_Chunk *alert;
extern bool countdown;

turret:: turret(int x, int y, int height, int width, int tileType)
    //applies the same variables as tiles
    :Tile(x, y, height, width, tileType) 
        {
        }
        
//goes through every tile and checks if the point collides with them        
bool turret::point2wall(Tile *tiles[], mTile *mtiles[])
{
     for( int t = 0; t < TOTAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( point_collision( test, tiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
        if( mtiles[ t ]->get_type() == Push_Tile ){
            if( point_collision( test, mtiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
    }
    return false;
}
        

bool turret:: survey( Tile *tiles[], mTile *mtiles[], Dot myDot)
{
    //determines where the points begin to come out of the turret    
    if(get_type() == left_turret)
    {
        test.x = box.x;
        test.y = box.y + 40;
    }
    
    if(get_type() == right_turret)
    {
        test.x = box.x + box.w;
        test.y = box.y + 40;
    }
    
    int i = 0;
    int z = 5;
    if(get_type() == left_turret)
    {
        //ten different lines of points are sent out at different angles to find the character
        for(int j = 0; j < 10; j++ )
        {
             //the line are 30 points long as long as they dont collide with a wall, then the lines end
            while(i < 30 && point2wall(tiles, mtiles) == false && countdown == false)
            {   
                //the gap between the points
                test.x -= 10;
                test.y += z;
                apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
                //if the turret sees the player, an alarm starts and a countdown begins
                if(point_collision(test, myDot.box))
                {
                    Mix_PlayChannel( -1, alert, 0 ); 
                    countdown = true;
                    //if the player is still is still detected when the countdown ends then the player dies
                    return true;
                }
                i++;
            }

        test.x = box.x;
        test.y = box.y + 40;
        //angle changes
        z -= 2;
        i = 0;
        }
    }
    
    // the same principles apply for right facing turrets aswell
    if(get_type() == right_turret)
    {
        for(int j = 0; j < 10; j++ )
        {
            while(i < 30 && point2wall(tiles, mtiles) == false && countdown == false)
            {     
                test.x += 10;
                test.y += z;
                apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
                if(point_collision(test, myDot.box))
                {
                    
                    Mix_PlayChannel( -1, alert, 0 ); 
                    countdown = true;
                    return true;
                }
                i++;
            }

        test.x = box.x + box.w;
        test.y = box.y + 40;
        z -= 2;
        i = 0;
        }
    }
    
    
    
    return false;
}


int turret:: shoot( int count)
{
    if(countdown == true)
    {
        //the countdown until the player dies
        count++;
        return count;
    }
}
