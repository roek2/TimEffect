/*This source code copyrighted by Lazy Foo' Productions (2004-2012)
and may not be redistributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <fstream>
#include "baseHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "timerHeader.h"
#include "setupHeader.h"
#include "mtileHeader.h"
#include "turretHeader.h"
#include "mapLoaderHeader.h"
#include "storyHeader.h"
#include <vector>
using namespace std;

//Used to determine when to blend the backgrounds
bool blending;

//stores mtile characteristics when the time is changed on a map
struct reload{
        int opX;    //original poistion of the mtile
        int opY;
        int thisLevel;  //]level number
        int currX;      //current position
        int currY;
};


//sttributes of the game screen
int SCREEN_WIDTH = 1366/2;
int SCREEN_HEIGHT = 768/2;
int SCREEN_BPP = 32;

//the amount rreload structs that can be stored on a map
const int TOTAL_MTILES = 5;

//determines how visible a surface is
int alpha = SDL_ALPHA_OPAQUE;           //SDL_ALPHA_OPAQUE = 255


//Game frame rate
const int FRAMES_PER_SECOND = 30;

//The dot dimensions
int DOT_WIDTH = 50;
int DOT_HEIGHT = 72;


//The dimensions of the first level
int LEVEL_WIDTH = 3440;
int LEVEL_HEIGHT = 640;

//The level the player is on.
int Level = 7  ;

//tt standing for text-time, determines the amoun   t of time dialogue appears on the screen
int tt = 0;                                                                                                                 ///*****

//Tile boundary characteristics
int TILE_WIDTH = 80;
int TILE_HEIGHT = 80;
int TOTAL_TILES = 344;

//The different types of tiles
int Win_Tile = 0;          //This tile is the goal of each level, touching it loads up the next level
int Invisible_Tile = 1;    //The entire map is made up of tiles, these tiles are see threw so you can see the background
int Death_Tile = 2;        //Touching this tile kills the player and causes him to respawn at the start of the level
int Solid_Tile = 3;        //This tile is like a wall, the player cant move threw it
int Push_Tile = 10;        // This tile, which has its own derived class, can be pushed and pulled by the player
int Gadget_Tile = 8;       // This tile unlocks the players ability to switch between times
int break_Tile = 16;       // If you stand on this tile it breaks underneath you and fall until it hits ground
int left_turret = 15;       //This tile is a turret that faces left
int right_turret = 18;      //This tile is a turret that faces left

//The surfaces
SDL_Surface *dot = NULL;        //The surface that represents athe character
SDL_Surface *pixel = NULL;      //shows the sight of a turret                                       (probably temporary)
SDL_Surface *screen = NULL;     //what is shown on the screen
SDL_Surface *tileSheet = NULL;      //The surface for each tile
SDL_Surface *tileSheet2 = NULL;
SDL_Surface *background = NULL;     //The background surface
SDL_Surface *background2 = NULL;
SDL_Surface *message = NULL;        //a surface to tell the player they are in the present
SDL_Surface *message2 = NULL;          //another for the past
SDL_Surface *message3 = NULL;
SDL_Surface *pauseMessage = NULL;
SDL_Surface *pauseMessage2 = NULL;
SDL_Surface *text = NULL;           //These three surfaces are for game dialogue such as tutorials.
SDL_Surface *text2 = NULL;
SDL_Surface *text3 = NULL;
//SDL_Surface *text[10];
bool dead = false;                  // A boolean to detrmine id the players alive
bool countdown = false;             //checks if a turret has seen you or not
bool pause = false;                 //determines if the game is paused
bool canChange = true;             //decides if the player can change to a different time or not

//For loading writing fonts
TTF_Font *font = NULL;

// The colour of the game text
SDL_Color textColor = { 200, 200, 200 };
SDL_Color textColor2 = { 150, 150, 150 };


//The different sound effects and music of the game
Mix_Chunk *win = NULL;
Mix_Chunk *lose = NULL;
Mix_Chunk *notime = NULL;
Mix_Chunk *alert = NULL;
Mix_Music *music = NULL;

timer fps;
int pull;

//The event structure
SDL_Event event;

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


void clean_up( Tile *tiles[], mTile *mtiles[], turret *turrets[] )
{
    //Free the surfaces
    SDL_FreeSurface( dot );
    SDL_FreeSurface( background);
    SDL_FreeSurface( background2 );
    SDL_FreeSurface( tileSheet );
    SDL_FreeSurface( tileSheet2 );
    SDL_FreeSurface( message );
    SDL_FreeSurface( message2 );
    SDL_FreeSurface( pauseMessage );
    SDL_FreeSurface( pauseMessage2 );
    SDL_FreeSurface( message2 );
    SDL_FreeSurface( pixel);
    SDL_FreeSurface( screen );
    SDL_FreeSurface( text );
    SDL_FreeSurface( text2 );
    SDL_FreeSurface( text3 );
    
    //Free music
    Mix_FreeChunk( win );
    Mix_FreeChunk( lose );
    Mix_FreeChunk( notime );
    Mix_FreeChunk( alert );
    Mix_FreeMusic( music );

    //Free the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete tiles[ t ];
    }
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete mtiles[ t ];
    }
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete turrets[ t ];
    }

    //Quit SDL
    SDL_Quit();
}

//When the player switches time all mtile variable are stored in structs
vector<reload> flux(vector<reload> active, mTile *mtiles[])
{
    int t = 0;
    //goes through every tile
    for(int i = 0; i < TOTAL_TILES; i++)
    { 
        //checks the tile type
        if( mtiles[ i ]->get_type() == Push_Tile)
        {
                active[t].opX = mtiles[ i ]->opX;                   //stores the mtile information
                active[t].opY = mtiles[ i ]->opY;
                active[t].currX = mtiles[ i ]->box.x;
                active[t].currY = mtiles[ i ]->box.y;
                t++;
        }
    }
    return active;
}

//When the player returns to a time, all mtiles that they moved retain their position
void capacitor(vector <reload> active, mTile *mtiles[])
{
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if( mtiles[ t ]->get_type() == Push_Tile)
        {
            for(int i = 0; i < TOTAL_MTILES; i++)
            {   
                //checks the original position of the mtiles stored in the structs
                if((active[i].opX == mtiles[ t ]->opX && active[i].opY == mtiles[ t ]->opY))
                {
                    mtiles[ t ]->box.x = active[i].currX;       //if the positions match, the mtiles on the map are
                    mtiles[ t ]->box.y = active[i].currY;       //assigned the current position of mtiles in the structs
                }
            }
        }
    }
}

//When the player moves something the past, this effects its position in the present but not vise versa
vector<reload> timeffect(vector<reload> active, vector <reload> active2 ,mTile *mtiles[])
{   
    //goes through each tile on the map
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if( mtiles[ t ]->get_type() == Push_Tile)
        {
            //goes through each tile in the struct array
            for(int i = 0; i < TOTAL_MTILES; i++)
            {           //compares the original positions of each
                if(active2[i].opX == mtiles[ t ]->opX && active2[i].opY == mtiles[ t ]->opY)
                {      //Checks if a change has been made in this timezone between loading the map and changing to another timezone
                    if(active2[i].currX != mtiles[ t ]->box.x || active2[i].currY != mtiles[ t ]->box.y)
                    {
                        for(int m = 0; m < TOTAL_MTILES; m++)
                        {       //then checks if there are structs for the present timezone that match the structs for the past timezone
                            if(active2[i].opX == active[m].opX && active2[i].opY == active[m].opY)
                            {
                                active[m].currX = mtiles[ t ]->box.x;       //the changes made in that timezone are applied to the other timezones structs
                                active[m].currY = mtiles[ t ]->box.y;          //when these structs are loaded up again, they have the new changes applied
                            }
                        }
                    }
                }
            }
        }
    }
    return active;
}


int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //The dot
    Dot myDot;
    
    //The class in charge with setting up many of the SDL basics
    Setup foo;
    
    //The base class
    base b;
    
    //The class in charge of looking after story based events
    story k;
    
    //loads each map
    mapLoader Fman;
    
    //The delay between a turret seeing the player and it killing the player
    int count = 0;
    
    //To highlight which option the player is on in the pause menu
    bool highlight = true; 
    
    // player cant change time until they acquire the time gadget.
    bool timeGadget = false;
    
    vector<reload> active (TOTAL_MTILES);       // a struct for storing information of mtiles in the present
    vector<reload> active2 (TOTAL_MTILES);      // a struct for storing information of mtiles in the past

    //The tiles that will be used
    Tile *tiles[ TOTAL_TILES ];
    
    //movable tiles
    mTile *mtiles[ TOTAL_TILES ];
    
    //turrets
    turret *turrets[ TOTAL_TILES ];

    //The frame rate regulator
 //   Timer fps;

    //Initialize
    if( foo.init() == false )
    { 
        
        return 1;
    }

    //Load the files
    if( foo.load_files() == false )
    {
        return 1;
    }
    
    message = TTF_RenderText_Solid( font, " PAST", textColor );                //messages to inform the player of their current state
    message2 = TTF_RenderText_Solid( font, " PRESENT", textColor );
    message3 = TTF_RenderText_Solid( font, " PAUSED", textColor );
    pauseMessage =  TTF_RenderText_Solid( font, "RESUME", textColor );
    pauseMessage2 =  TTF_RenderText_Solid( font, "EXIT", textColor2 );
    
                                                                            /////*************************
    //if the message fails the game ends
    if( message == NULL )
    {
        return 1;
    }

    //plays the music
    Mix_PlayMusic(music, -1);

    //sets where the player will respawn for that level
    myDot.set_respawn();
    //sets the attributes for that level
    myDot.set_clips();
    Fman.set_level();
    //sets the tiles for that level
    if( Fman.set_tiles( tiles , mtiles, turrets) == false )
    {
        return 1;
    }
    // the attributes for the mtiles are stored
    active2 = flux(active2, mtiles);
    active = flux(active, mtiles);
    
    
    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the dot
            myDot.handle_input();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //if the game is paused the character cant move
        if(!pause)
        {
            //moves the character
            myDot.move( tiles, mtiles, turrets );
        }
        
        if(Level == 2)
        {
            //if the player gets the item that allows him to travel between the 2 times, then he can travel between the 2 times.
            if(myDot.getTime(myDot.box, tiles, timeGadget))
                timeGadget = true;
        }
        //if the player dies...
        if(myDot.dies(tiles))
        {
            //the map is reset to what was before the player entered the room
            Fman.reset(mtiles, tiles, turrets);
            //all mtile structs are set to there original co ordinates.
            for( int t = 0; t < TOTAL_MTILES; t++ ){
                active[t].currX = active[t].opX;
                active[t].currY = active[t].opY;
                active2[t].currX = active2[t].opX;
                active2[t].currY = active2[t].opY;
            }
        }
        //if the player reaches the end of the level and its the last level the game ends               //fix?
        if(myDot.wins( tiles) == true && (Level == 16 || Level == 116))
        {
            // the game waits a second and then ends
            SDL_Delay(1500); 
            quit = true;
        }
        
        //in special story based circunmstances, if a level is completed the next level mightened be loaded up
        else if(myDot.wins( tiles) == true && (Level == 6 || Level == 106 || Level == 7 ))
        {
            if(Level == 6 || Level == 7)
                Level += 44;
            else if(Level == 106)
                Level += 44;
            myDot.set_respawn();
            Fman.set_level();
            Fman.set_tiles( tiles, mtiles, turrets);
            active2 = flux(active2, mtiles);
            active = flux(active, mtiles);
        }
         
         //if the player beats a level the next level is loaded       
        else if(myDot.wins( tiles) == true)
        {
            Level++;                //Level is increases
            myDot.set_respawn();       //The players respawn co ordinates are reasigned
            Fman.set_level();          //Set the attributes of the level
            Fman.set_tiles( tiles, mtiles, turrets);
            active2 = flux(active2, mtiles);    //structs for new level are set.
            active = flux(active, mtiles);
            Mix_PlayMusic(music, -1);
        }
        
        //keystates are loaded, which allow quick and easy key dtection without having to deal with events
        Uint8 *keystates = SDL_GetKeyState( NULL );
        
        //checks if t has been pressed and checks if the player is in present (any level below 100 is in present)
        if(keystates[ SDLK_t ] && Level < 100  && !pause && canChange == true)
        {
            //stores the map infor before changing
            active = flux(active, mtiles);
            Fman.set_tiles( tiles , mtiles, turrets);       //sets the new map
            blending = true;                                //blends the map for affect
            capacitor(active2, mtiles);                     //checks the structs for the map that has just been loaded up
            
            //checks if in the new map, if the player is colliding with anything
            if(myDot.touches_wall( myDot.box, tiles, mtiles, turrets )== true)
            {
                //if so then the game reloads the previous map
                Fman.set_tiles( tiles , mtiles, turrets);
                blending = false;
                capacitor(active, mtiles);
            }
            //stops the player from holding down and changing the time again and again
            canChange = false;
        }
        //same as before but in for the past
        else if(keystates[ SDLK_t ]  && Level > 100 && !pause && canChange == true )
        {
            active = timeffect(active, active2, mtiles);
            
            active2 = flux(active2, mtiles);
            Fman.set_tiles( tiles , mtiles, turrets);
            blending = false;
            capacitor(active, mtiles);
            if(myDot.touches_wall( myDot.box, tiles, mtiles, turrets )== true)
            {
            //    Mix_PlayChannel( -1, notime, 0 ); 
                Fman.set_tiles( tiles , mtiles, turrets);
                blending = true;
                capacitor(active2, mtiles);
            }
            canChange = false;
        }
        //once the player lets go of t he can change the time again
        if(!keystates[ SDLK_t ])
            canChange = true;
            
        //Set the camera
        myDot.set_camera();
        
        //used for effect when switching between times
        if( blending == false )
        {
            //If alpha is not at maximum
            if (alpha < SDL_ALPHA_OPAQUE )
            {
                alpha += 15;
            }
        }

        //If down is pressed
        if( blending == true )
        {
            //If alpha is not at minimum
            if( alpha > SDL_ALPHA_TRANSPARENT )
            {
                //Decrease alpha
                alpha -= 15;
            }
        }

        //Set surface alpha for blending
        SDL_SetAlpha( background, SDL_SRCALPHA, alpha );
        b.apply_surface(0, 0, background2, screen, &camera );
        b.apply_surface(0, 0, background, screen, &camera );




        //Goes through all the tiles, mtiles and turrets and shows them all
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            Fman.clip_tiles(tiles[ t ]->get_box());
            if( tiles[ t ]->get_type() != 1)
                tiles[ t ]->show();
        }
        
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            Fman.clip_tiles(mtiles[ t ]->get_box());
            if( mtiles[ t ]->get_type() != 1)
                mtiles[ t ]->show();
                mtiles[ t ]->moveTile(myDot, tiles, mtiles, turrets);
                mtiles[ t ]->moveTile(myDot, tiles, mtiles, turrets);
        }
        
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            Fman.clip_tiles(turrets[ t ]->get_box());
            if( turrets[ t ]->get_type() != 1)
                turrets[ t ]->show();
        }
        
        //Show the dot on the screen
        myDot.show();
        
        if(pause && k.director(myDot) == 0) {
        
           // The game is paused and the appropraied messages ares shown  
           b.apply_surface(SCREEN_WIDTH - 100, 0, message3, screen);
           b.apply_surface((SCREEN_WIDTH/2) - 70, SCREEN_HEIGHT/2, pauseMessage, screen);
           b.apply_surface((SCREEN_WIDTH/2) - 70, (SCREEN_HEIGHT/2) + 20, pauseMessage2, screen);
          
          
          //The player can choose from the pause menu to either resume the game of exit
           if(keystates[ SDLK_DOWN ])
           {
              pauseMessage =  TTF_RenderText_Solid( font, "RESUME", textColor2 );
              pauseMessage2 =  TTF_RenderText_Solid( font, "EXIT", textColor );
              highlight = false;
           }
              if(keystates[ SDLK_UP ])
           {
              pauseMessage =  TTF_RenderText_Solid( font, "RESUME", textColor );
              pauseMessage2 =  TTF_RenderText_Solid( font, "EXIT", textColor2 );
              highlight = true;
           }
           //if the player choose resume the game continues
           if(highlight == true && keystates[SDLK_RETURN])
           {
                         pause = !pause;
           }
           // if the player chooses exit then the game ends
           if(highlight == false && keystates[SDLK_RETURN])
           {
                    clean_up( tiles, mtiles, turrets );
                    return 0;             
           } 
              
        }
        
        
        
        if(Level < 100)
        //showing the past and present sign in the top corner
            b.apply_surface( 0, 0, message2, screen );
        else
            b.apply_surface( 0, 0, message, screen );
            
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            //checks if the tile is a turret
            if( ( turrets[ t ]->get_type() == left_turret || turrets[ t ]->get_type() == right_turret ) )  
            {
            //checks if the turret has spotted the player
                if( turrets[ t ]->survey(tiles, mtiles, myDot))
                {
                    //the turret counts down to shooting the player
                    countdown = true;
                }
                count = turrets[ t ]->shoot(count);
        
                if(count > 20)
                {
                    
                    count = 0; 
                    countdown = false;
                    if( turrets[ t ]->survey(tiles, mtiles, myDot))
                    {
                        //the player is shot by the turret
                        dead = true; 
                    }
                }
                    
                
            }
        }
        
        //The games cutscenes are loaded
        count = k.cutscene(k.textConverter(myDot), count, myDot);
        if(k.director(myDot) == 1)
        {   //if the player is in the air when a cutscene begins
            if(myDot.touches_ground(myDot.box, tiles, mtiles, turrets) == false)
                {
                    //the player is grounded
                    myDot.box.y += 8;
                }
        }
        //This is the cleanup of the story events
        k.end_story(myDot, Fman, tiles, mtiles, turrets);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }


    //Clean up
    clean_up( tiles ,mtiles, turrets );

    return 0;
}
