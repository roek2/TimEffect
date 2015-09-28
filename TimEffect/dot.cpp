#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "dotHeader.h"
#include "tileHeader.h"
#include "mtileHeader.h"
#include "turretHeader.h"
#include "timerHeader.h"
#include <fstream>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int DOT_WIDTH;
extern int DOT_HEIGHT;

extern SDL_Surface *dot;
extern SDL_Surface *screen;

extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int TOTAL_TILES;

extern int Win_Tile;
extern int Death_Tile;
extern int Solid_Tile;
extern int Push_Tile;
extern int Gadget_Tile;
extern int left_turret;
extern int right_turret;
extern int break_Tile;

extern SDL_Event event;

extern Mix_Chunk *win;
extern Mix_Chunk *lose;

extern SDL_Rect camera;
extern bool dead;
extern int Level;
extern bool pause;

extern timer fps;
extern int pull;

SDL_Rect clip[30];

int frame;
int numFrames = 15;
int direction;


Dot::Dot()
{
    //Initialize the offsets
    box.x = 80;
    box.y = 400;
    box.w = DOT_WIDTH;
    box.h = DOT_HEIGHT;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;
    
    //set the character respan point
    respawnX = 80;
    respawnY = 500;
    
    //sets the player as not on ground
    onGround = false;
    
    frame = 0;
    direction = 0;
}

void Dot::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            //if the player presses escape
            case SDLK_ESCAPE: togglePause(); break;
            //if the player presses left, the character's velocity becomes negative
            case SDLK_LEFT: xVel -= DOT_WIDTH / 5; break;
            //if the player presses right, the character's velocity increases
            case SDLK_RIGHT: xVel += DOT_WIDTH / 5; break;
            //if the player presses space then the player jumps
            case SDLK_SPACE: makeJump(); break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            //when the player lets go of left or right the velocity returns to 0
            case SDLK_LEFT: xVel += DOT_WIDTH / 5; break;
            case SDLK_RIGHT: xVel -= DOT_WIDTH / 5; break;
        }
    }
}

void Dot::set_clips() 
{
     clip[0].x = 0;
     clip[0].y = 0;
     clip[0].w = DOT_WIDTH;
     clip[0].h = DOT_HEIGHT + 8;
     
     clip[1].x = DOT_WIDTH;
     clip[1].y = 0;
     clip[1].w = DOT_WIDTH;
     clip[1].h = DOT_HEIGHT + 8;
     
     clip[2].x = DOT_WIDTH * 2;
     clip[2].y = 0;
     clip[2].w = DOT_WIDTH;
     clip[2].h = DOT_HEIGHT + 8;  
     
     clip[3].x = DOT_WIDTH * 3;
     clip[3].y = 0;
     clip[3].w = DOT_WIDTH;
     clip[3].h = DOT_HEIGHT + 8;
     
     clip[4].x = DOT_WIDTH * 4;
     clip[4].y = 0;
     clip[4].w = DOT_WIDTH;
     clip[4].h = DOT_HEIGHT + 8;
     
     clip[5].x = DOT_WIDTH * 5;
     clip[5].y = 0;
     clip[5].w = DOT_WIDTH;
     clip[5].h = DOT_HEIGHT + 8;
     
     clip[6].x = DOT_WIDTH * 6;
     clip[6].y = 0;
     clip[6].w = DOT_WIDTH;
     clip[6].h = DOT_HEIGHT + 8;  
     
     clip[7].x = DOT_WIDTH * 7;
     clip[7].y = 0;
     clip[7].w = DOT_WIDTH;
     clip[7].h = DOT_HEIGHT + 8;
      
     clip[8].x = DOT_WIDTH * 8;
     clip[8].y = 0;
     clip[8].w = DOT_WIDTH;
     clip[8].h = DOT_HEIGHT + 8;
     
     clip[9].x = DOT_WIDTH * 9;
     clip[9].y = 0;
     clip[9].w = DOT_WIDTH;
     clip[9].h = DOT_HEIGHT + 8;
     
     clip[10].x = DOT_WIDTH * 10;
     clip[10].y = 0;
     clip[10].w = DOT_WIDTH;
     clip[10].h = DOT_HEIGHT + 8;  
     
     clip[11].x = DOT_WIDTH * 11;
     clip[11].y = 0;
     clip[11].w = DOT_WIDTH;
     clip[11].h = DOT_HEIGHT + 8; 
     
     clip[12].x = DOT_WIDTH * 12;
     clip[12].y = 0;
     clip[12].w = DOT_WIDTH;
     clip[12].h = DOT_HEIGHT + 8;  
     
     clip[13].x = DOT_WIDTH * 13;
     clip[13].y = 0;
     clip[13].w = DOT_WIDTH;
     clip[13].h = DOT_HEIGHT + 8;
     
     clip[14].x = DOT_WIDTH * 14;
     clip[14].y = 0;
     clip[14].w = DOT_WIDTH;
     clip[14].h = DOT_HEIGHT + 8;
     
     clip[15].x = 0;
     clip[15].y = DOT_HEIGHT + 8;
     clip[15].w = DOT_WIDTH;
     clip[15].h = DOT_HEIGHT + 8;
     
     clip[16].x = DOT_WIDTH;
     clip[16].y = DOT_HEIGHT + 8;
     clip[16].w = DOT_WIDTH;
     clip[16].h = DOT_HEIGHT + 8;
     
     clip[17].x = DOT_WIDTH * 2;
     clip[17].y = DOT_HEIGHT + 8;
     clip[17].w = DOT_WIDTH;
     clip[17].h = DOT_HEIGHT + 8;  
     
     clip[18].x = DOT_WIDTH * 3;
     clip[18].y = DOT_HEIGHT + 8;
     clip[18].w = DOT_WIDTH;
     clip[18].h = DOT_HEIGHT + 8;
     
     clip[19].x = DOT_WIDTH * 4;
     clip[19].y = DOT_HEIGHT + 8;
     clip[19].w = DOT_WIDTH;
     clip[19].h = DOT_HEIGHT + 8;
     
     clip[20].x = DOT_WIDTH * 5;
     clip[20].y = DOT_HEIGHT + 8;
     clip[20].w = DOT_WIDTH;
     clip[20].h = DOT_HEIGHT + 8;
     
     clip[21].x = DOT_WIDTH * 6;
     clip[21].y = DOT_HEIGHT + 8;
     clip[21].w = DOT_WIDTH;
     clip[21].h = DOT_HEIGHT + 8;  
     
     clip[22].x = DOT_WIDTH * 7;
     clip[22].y = DOT_HEIGHT + 8;
     clip[22].w = DOT_WIDTH;
     clip[22].h = DOT_HEIGHT + 8;
      
     clip[23].x = DOT_WIDTH * 8;
     clip[23].y = 0;
     clip[23].w = DOT_WIDTH;
     clip[23].h = DOT_HEIGHT;
     
     clip[24].x = DOT_WIDTH * 9;
     clip[24].y = DOT_HEIGHT + 8;
     clip[24].w = DOT_WIDTH;
     clip[24].h = DOT_HEIGHT + 8;
     
     clip[25].x = DOT_WIDTH * 10;
     clip[25].y = DOT_HEIGHT + 8;
     clip[25].w = DOT_WIDTH;
     clip[25].h = DOT_HEIGHT + 8;  
     
     clip[26].x = DOT_WIDTH * 11;
     clip[26].y = DOT_HEIGHT + 8;
     clip[26].w = DOT_WIDTH;
     clip[26].h = DOT_HEIGHT + 8; 
     
     clip[27].x = DOT_WIDTH * 12;
     clip[27].y = DOT_HEIGHT + 8;
     clip[27].w = DOT_WIDTH;
     clip[27].h = DOT_HEIGHT + 8;  
     
     clip[28].x = DOT_WIDTH * 13;
     clip[28].y = DOT_HEIGHT + 8;
     clip[28].w = DOT_WIDTH;
     clip[28].h = DOT_HEIGHT + 8;
     
     clip[29].x = DOT_WIDTH * 14;
     clip[29].y = DOT_HEIGHT + 8;
     clip[29].w = DOT_WIDTH;
     clip[29].h = DOT_HEIGHT + 8;
}


bool Dot::touches_wall( SDL_Rect box, Tile *tiles[], mTile *mtiles[], turret *turrets[] )
{
    
    Uint8 *keystates = SDL_GetKeyState( NULL );
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ]->get_type() == Solid_Tile ) )  
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        //if an mtile and is not pressing x (x to push brick)     or     if its an break-away mtile that has yet to touch the ground
        if((mtiles[ t ]->get_type() == Push_Tile && !keystates[ SDLK_x ]) || ((mtiles[ t ]->get_type() == break_Tile && mtiles[ t ]->wall2ground(tiles, mtiles) == false))) 
        {
            //if the player collides with these then they are stopped
            if( check_collision( box, mtiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        //if an mtile and is and toucing a wall then its cant be pushed into that direction     or      the mtile has nothing underneath it    or the player is not touching the ground
        if (mtiles[ t ]->get_type() == Push_Tile && (mtiles[ t ]->wall2wall(tiles, mtiles, turrets) == true || mtiles[ t ]->wall2ground(tiles, mtiles) == false || touches_ground(box ,tiles, mtiles, turrets) == false))  // brick
        {
            //if the player collides with these then they are stopped
            if( check_collision( box, mtiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        
        if (mtiles[ t ]->get_type() == Push_Tile && mtiles[ t ]->ground_collision( box, mtiles[ t ]->get_box() ) == true)
        {
            if( check_collision( box, mtiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        //if the player collides with a turret then he is stopped
        if (turrets[ t ]->get_type() == left_turret || turrets[ t ]->get_type() == right_turret)
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

bool Dot::touches_ground(SDL_Rect box, Tile *tiles[], mTile *mtiles[], turret *turrets[])
{
    
    //goes through each tile and if the player is on top of a tile, mtile or turret then it returns true
     for( int t = 0; t < TOTAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( ground_collision( box, tiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
        if( mtiles[ t ]->get_type() == Push_Tile || mtiles[ t ]->get_type() == break_Tile ){
            if( ground_collision( box, mtiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
        if ((turrets[ t ]->get_type() == left_turret || turrets[ t ]->get_type() == right_turret) && turrets[ t ]->ground_collision( box, turrets[ t ]->get_box() ) == true)
        {
            if( ground_collision( box, turrets[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
        
    }
    return false;
}

bool Dot::touches_roof(SDL_Rect box, Tile *tiles[], mTile *mtiles[])
{
    
    //goes through each tile and if the top of the player hits off the bottom of a tile or mtile then it returns true
     for( int t = 0; t < TOTAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile){
            if( roof_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
        if( mtiles[ t ]->get_type() == Push_Tile ){
            if( roof_collision( box, mtiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
     }
     return false;
}

bool Dot::touches_death( SDL_Rect box, Tile *tiles[] )
{
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a death type tile
        if( ( tiles[ t ]->get_type() == Death_Tile ))
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }
    return false;
}




void Dot::move( Tile *tiles[], mTile *mtiles[], turret *turrets[])
{
    //Move the dot left or right
    box.x += xVel;
    Uint8 *keystates = SDL_GetKeyState( NULL );
    
    if(fps.nextFrame()) {
        if(pull != 0 && !keystates[ SDLK_x ]) {
                pull = 0;
        }
        
        if(xVel == 0)
                frame = direction;
        
        if(xVel > 0 && pull == 0) {
                direction = 0;
                frame = frame + 1;
                if(frame >= 9)
                         frame = 1;
        }                  
        if(xVel < 0 && pull == 0) {
                direction = numFrames;
                frame = frame + 1;
                if(frame >= 23 || frame <= 16)
                         frame = 16;
        }
        if(pull == -1 && xVel > 0) {
                if(frame < 9 || frame > 11)
                         frame = 9;
                else
                    frame++;
        }
        if(pull == -1 && xVel < 0) {
                if(frame < 9 || frame > 12)
                         frame = 12;
                else
                    frame--;
        }
        if(pull == 1 && xVel < 0) {
                if(frame < 24 || frame > 26)
                         frame = 24;
                else
                    frame++;
        }
        if(pull == 1 && xVel > 0) {
                if(frame < 25 || frame > 27)
                         frame = 27;
                else
                    frame--;
        }
        
        
    }

    //If the dot went too far to the left or right or touched a wall
    if( ( box.x < 0 ) || ( box.x + DOT_WIDTH > LEVEL_WIDTH ) || touches_wall( box, tiles, mtiles, turrets ) )
    {
        //move back
        box.x -= xVel;
    }

    //Move the dot up or down
    box.y += yVel;
    
    if(!(touches_ground(box, tiles, mtiles, turrets)) && yVel < 0)
            frame = 13 + direction;
    if(!(touches_ground(box, tiles, mtiles, turrets))&& yVel > 0)
            frame = 14 + direction;

    //If the dot went too far up or down or touched a wall
    if( ( box.y < 0 ) || ( box.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touches_wall( box, tiles, mtiles, turrets ) )
    {
        //move back
        box.y -= yVel;
    }
    
    //if the player is touches the ground then it is onGround
    if( touches_ground( box, tiles, mtiles, turrets) )
    {
         onGround = true;
    }
    else 
    {
         onGround = false;
    }
    
    //if the character is not jumping and is not touching the ground      or       the character hits the roof
    if((!(touches_ground(box, tiles, mtiles, turrets)) && !jump) || touches_roof(box, tiles, mtiles) == true)
    {
                //the player will fall
                  yVel = 8;      
    }
    

    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //if the character collides with a mtile and tries to pull that block left but there is something in the way of that block.
        if(left_collision2(box, mtiles[ t ]->get_box()) == true && mtiles[ t ]->get_type() == Push_Tile && keystates[ SDLK_x ] && mtiles[ t ]->wall2left(tiles, mtiles, turrets) && onGround == true)
        {
            //then the player is stopped
            box.x += xVel;
        }
        //same is applied to the right
        if(right_collision2(box, mtiles[ t ]->get_box()) == true && mtiles[ t ]->get_type() == Push_Tile && keystates[ SDLK_x ] && mtiles[ t ]->wall2right(tiles, mtiles, turrets) && onGround == true)
        {
            box.x += xVel;
        }
        
    }
    
    //when the player jumps and is holding space the player looses momentum slower and can as a result jump higher
    if(jump && yVel < 8 && keystates[ SDLK_SPACE ] )
    {
            yVel++;
    }
    
    //when the player jumps, the y velocity reduces the momentum of the jump and pulls the player back down
    else if(jump && yVel < 8)
    {
         yVel = yVel + 2;
    }
         
    
    else
         jump = false;
         
    
}

bool Dot::touches_win( Tile *tiles[] )
{
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a win type tile
        if( ( tiles[ t ]->get_type() == Win_Tile ))
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }
    return false;
}

//checks if the player had beaten a level
bool Dot:: wins(Tile *tiles[])
{
    if(touches_win(tiles) == true){
                     return true;
    }
}

//checks if the player has touched a killer block
bool Dot:: dies(Tile *tiles[])
{
    if(touches_death(box, tiles) == true || dead == true){
        Mix_PlayChannel( -1, lose, 0 );  
        //the player is reset to their respawn position
        box.x = respawnX;
        box.y = respawnY;
        dead = false;
    }
}

void Dot:: makeJump()
{
    //if the player jumps their y velocity becomes negative, sending the player in the air.
     if(onGround && !jump){   
            jump = true;
            onGround = false;
            yVel =- 14;
     }
}

//checks if the player has acquired the time change gadget
bool Dot:: getTime(SDL_Rect box, Tile *tiles[], bool timeGadget)
{
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a time type tile
        if( ( tiles[ t ]->get_type() == Gadget_Tile ))
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }
    return false;
}
 
 //depending on what level the player is in, the player is assigned a different respawn point
void Dot :: set_respawn()
{
    if(Level == 2 || Level == 102)
    {
        respawnX = 90;
        respawnY = 100;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 3 || Level == 103)
    {
        respawnX = 10;
        respawnY = 100;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 4 || Level == 104)
    {
        respawnX = 1200;
        respawnY = 200;
        box.x = respawnX;
        box.y = respawnY;
    }
        
    if(Level == 5 || Level == 105)
    {
        respawnX = 700;
        respawnY = 200;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 6 || Level == 106)
    {
        respawnX = 90;
        respawnY = 600;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 7 || Level == 107)
    {
        respawnX = 710;
        respawnY = 40;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 9 || Level == 109)
    {
        respawnX = 0;
        respawnY = 750;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 10 || Level == 110)
    {
        respawnX = 10;
        respawnY = 600;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 8 || Level == 108)
    {
        respawnX = 90;
        respawnY = 1300;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 11 || Level == 111)
    {
        respawnX = 90;
        respawnY = 500;
        box.x = respawnX;
        box.y = respawnY;
    }
    if(Level == 12 || Level == 112)                                 
    {
        respawnX = 90;
        respawnY = 300;
        box.x = respawnX;
        box.y = respawnY;
    }
    if(Level == 13 || Level == 113)                         //////could be better
    {
        respawnX = 120;
        respawnY = 500;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 14 || Level == 114)               
    {
        respawnX = 120;
        respawnY = 500;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 15 || Level == 115)               
    {
        respawnX = 120;
        respawnY = 500;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 16 || Level == 116)
    {
        respawnX = 90;
        respawnY = 1300;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 50 || Level == 150)               
    {
        respawnX = 10;
        respawnY = 200;
        box.x = respawnX;
        box.y = respawnY;
    }
    
    if(Level == 51 || Level == 151)               
    {
        respawnX = 3200;
        respawnY = 190;
        box.x = respawnX;
        box.y = respawnY;
    }
    
}            

void Dot::show()
{
    //Show the dot
    apply_surface( box.x - camera.x, box.y - camera.y, dot, screen, &clip[frame] );
}

void Dot::set_camera()
{
    //Center the camera over the dot
    camera.x = ( box.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( box.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void Dot::togglePause() 
{
    //the player cant move when the game is paused
     pause = !pause;
}

