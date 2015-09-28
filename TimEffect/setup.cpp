#include "SDL.h"
#include <fstream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
//#include "tileHeader.h"
#include "setupHeader.h"
using namespace std;

extern SDL_Surface *dot;
extern SDL_Surface *pixel;
extern SDL_Surface *tileSheet;
extern SDL_Surface *tileSheet2;
extern SDL_Surface *screen;
extern SDL_Surface *background;
extern SDL_Surface *background2;

extern Mix_Chunk *win;
extern Mix_Chunk *lose;
extern Mix_Chunk *notime;
extern Mix_Chunk *alert;
extern Mix_Music *music;

extern int TOTAL_TILES;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;

extern TTF_Font *font;


bool Setup:: init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //if loading the font fails then game closes
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //if loading the game music and sound effects fails, then the game closes
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Super K-Dawg", NULL );

    //If everything initialized fine
    return true;
}



SDL_Surface* Setup:: load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0 ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}



bool Setup:: load_files()
{
    //Load the dot image
    dot = load_image( "main_final.png" );
    SDL_SetColorKey( dot, SDL_SRCCOLORKEY, SDL_MapRGB( dot->format, 0, 0xFF, 0 ) );
    pixel = load_image( "pixel.png" );

    //If there was a problem in loading the dot
    if( dot == NULL )
    {
        return false;
    }

    //loads the different sound effects
    win = Mix_LoadWAV( "fanfare.wav" );
    lose = Mix_LoadWAV( "dead.wav" );
    notime = Mix_LoadWAV( "yoshi.wav" );
    alert = Mix_LoadWAV( "turret.wav" );
    //sets appropriate volues for the sound effects
    alert->volume = 10;
    win->volume = 10;
    lose->volume = 10;
    
    if( ( win == NULL ) || ( lose == NULL ))
    {
        return false;
    }
    
    //loads the music for the game
    music = Mix_LoadMUS( "keogh.wav" );

    //If there was a problem loading the music
    if( music == NULL )
    {
        return false;
    }
    
    //loads the background image
    background = load_image( "present.png" );
    background2 = load_image( "present.png" );
    
    //Load the tile sheet
    tileSheet = load_image( "tiles.png" );
    tileSheet2 = load_image( "tiles2.png" );

    //If there was a problem in loading the tiles
    if( tileSheet == NULL )
    {
        return false;
    }
    
    //loads the font
    font = TTF_OpenFont( "ultra.ttf", 20 );

    //If everything loaded fine
    return true;
}

