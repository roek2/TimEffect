#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include <fstream>
#include "setupHeader.h"
#include "baseHeader.h"
#include "tileHeader.h"
#include "turretHeader.h"
#include "mtileHeader.h"
#include "mapLoaderHeader.h"
using namespace std;

extern int Level;

const int TILE_SPRITES = 12;

extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int TOTAL_TILES;

extern int Win_Tile;
extern int Invisible_Tile;
extern int Death_Tile;
extern int Solid_Tile;
extern int Push_Tile;
extern int Gadget_Tile;
extern int left_turret;
extern int right_turret;
extern int break_Tile;
    
extern SDL_Surface *tileSheet;
extern SDL_Surface *tileSheet2;
extern SDL_Surface *background;
extern SDL_Surface *background2;
extern Mix_Music *music;

extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int TOTAL_TILES;
extern int LEVEL_WIDTH;


SDL_Rect clips[TILE_SPRITES];

void mapLoader :: clip_tiles(SDL_Rect box)
{
    //Clip the sprite sheet and assign the different sprites to the tiles
    clips[ Win_Tile ].x = 0;
    clips[ Win_Tile ].y = 0;
    clips[ Win_Tile ].w = box.w;
    clips[ Win_Tile ].h = box.h;

    clips[ Invisible_Tile ].x = 0;
    clips[ Invisible_Tile ].y = 80;
    clips[ Invisible_Tile ].w = box.w;
    clips[ Invisible_Tile ].h = box.h;

    clips[ Death_Tile ].x = 320;
    clips[ Death_Tile ].y = 0;
    clips[ Death_Tile].w = box.w;
    clips[ Death_Tile ].h = box.h;
    
    clips[ Push_Tile ].x = 160;
    clips[ Push_Tile ].y = 0;
    clips[ Push_Tile ].w = box.w;
    clips[ Push_Tile ].h = box.h;

    clips[ Solid_Tile ].x = 0;
    clips[ Solid_Tile ].y = 0;
    clips[ Solid_Tile ].w = box.w;
    clips[ Solid_Tile ].h = box.h;
    
    clips[ left_turret ].x = 480;
    clips[ left_turret ].y = 80;
    clips[ left_turret ].w = box.w;
    clips[ left_turret ].h = box.h;
    
    
    clips[ right_turret ].x = 560;
    clips[ right_turret ].y = 0;
    clips[ right_turret ].w = box.w;
    clips[ right_turret ].h = box.h;
    
    clips[ break_Tile ].x = 0;
    clips[ break_Tile ].y = 0;
    clips[ break_Tile ].w = box.w;
    clips[ break_Tile ].h = box.h;
    
    clips[ Gadget_Tile ].x = 0;
    clips[ Gadget_Tile ].y = 80;
    clips[ Gadget_Tile ].w = box.w;
    clips[ Gadget_Tile ].h = box.h;
    

}

bool mapLoader :: set_tiles( Tile *tiles[], mTile *mtiles[], turret *turrets[] )
{
   // load the maps
    int x = 0, y = 0;
    
    ifstream map( "Lazy1.map");
    ifstream map101( "Lazy2.map");
    ifstream map2( "Lazy3.map");
    ifstream map102( "Lazy4.map");
    ifstream map3( "Lazy5.map");
    ifstream map103( "Lazy6.map");
    ifstream map4( "Lazy7.map");
    ifstream map104( "Lazy8.map");
    ifstream map5( "Lazy9.map");
    ifstream map105( "Lazy10.map");
    ifstream map6( "Lazy11.map");
    ifstream map106( "Lazy12.map");
    ifstream map7( "Lazy13.map");
    ifstream map107( "Lazy14.map");
    ifstream map8( "Lazy15.map");
    ifstream map108( "Lazy16.map");
    ifstream map9( "Lazy31.map");
    ifstream map109( "Lazy32.map");
    ifstream map10( "Lazy19.map");
    ifstream map110( "Lazy20.map");
    ifstream map11( "Lazy21.map");
    ifstream map111( "Lazy22.map");
    ifstream map12( "Lazy23.map");
    ifstream map112( "Lazy24.map");
    ifstream map13( "Lazy25.map");
    ifstream map113( "Lazy26.map");
    ifstream map14( "Lazy27.map");
    ifstream map114( "Lazy28.map");
    ifstream map15( "Lazy17.map");
    ifstream map115( "Lazy18.map");
    ifstream map50( "Lazy29.map");
    ifstream map150( "Lazy30.map");
    ifstream map51( "hidden.map");
    ifstream map151( "hidden2.map");
    

    if( map == NULL )
    {
        return false;
    }
    Uint8 *keystates = SDL_GetKeyState( NULL );

    //if the player has pressed t and is in the present
    if(keystates[ SDLK_t ] && Level < 100)
    {
        //then send him to the past
        Level = Level + 100;
    }
    //if the player has pressed t and is in the past
    else if( keystates[ SDLK_t ] && Level > 100)
    {
        //then send him to the present
        Level = Level - 100;
    }
    //Initialize the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Determines what kind of tile and size of tile that will be made
        int tileType = -1;
        int mappedwidth = -1;
        int mappedheight = -1;
        char bracket;
        
    if(Level == 1){
        map >> bracket;
        map >> tileType;
        map >> mappedwidth;
        map >> mappedheight;
        map >> bracket;
    }
    
    if(Level == 101){
        map101 >> bracket;
        map101 >> tileType;
        map101 >> mappedwidth;
        map101 >> mappedheight;
        map101 >> bracket;
    }
    
    if(Level == 2){
        map2 >> bracket;
        map2 >> tileType;
        map2 >> mappedwidth;
        map2 >> mappedheight;
        map2 >> bracket;
    }
    if(Level == 102){
        map102 >> bracket;
        map102 >> tileType;
        map102 >> mappedwidth;
        map102 >> mappedheight;
        map102 >> bracket;
    }
    
    if(Level == 3){
        map3 >> bracket;
        map3 >> tileType;
        map3 >> mappedwidth;
        map3 >> mappedheight;
        map3 >> bracket;
    }
    if(Level == 103){
        map103 >> bracket;
        map103 >> tileType;
        map103 >> mappedwidth;
        map103 >> mappedheight;
        map103 >> bracket;
    }
    
    if(Level == 4){
        map4 >> bracket;
        map4 >> tileType;
        map4 >> mappedwidth;
        map4 >> mappedheight;
        map4 >> bracket;
    }
    if(Level == 104){
        map104 >> bracket;
        map104 >> tileType;
        map104 >> mappedwidth;
        map104 >> mappedheight;
        map104 >> bracket;
    }
    
    if(Level == 5){
        map5 >> bracket;
        map5 >> tileType;
        map5 >> mappedwidth;
        map5 >> mappedheight;
        map5 >> bracket;
    }
    if(Level == 105){
        map105 >> bracket;
        map105 >> tileType;
        map105 >> mappedwidth;
        map105 >> mappedheight;
        map105 >> bracket;
    }
    
    if(Level == 6){
        map4 >> bracket;
        map4 >> tileType;
        map4 >> mappedwidth;
        map4 >> mappedheight;
        map4 >> bracket;
    }
    
    if(Level == 106){
        map104 >> bracket;
        map104 >> tileType;
        map104 >> mappedwidth;
        map104 >> mappedheight;
        map104 >> bracket;
    }
    
    if(Level == 7){
        map6 >> bracket;
        map6 >> tileType;
        map6 >> mappedwidth;
        map6 >> mappedheight;
        map6 >> bracket;
    }
    
    if(Level == 107){
        map106 >> bracket;
        map106 >> tileType;
        map106 >> mappedwidth;
        map106 >> mappedheight;
        map106 >> bracket;
    }
    
    if(Level == 9){
        map7 >> bracket;
        map7 >> tileType;
        map7 >> mappedwidth;
        map7 >> mappedheight;
        map7 >> bracket;
    }
    
    if(Level == 109){
        map107 >> bracket;
        map107 >> tileType;
        map107 >> mappedwidth;
        map107 >> mappedheight;
        map107 >> bracket;
    }
    
    if(Level == 10){
        map8 >> bracket;
        map8 >> tileType;
        map8 >> mappedwidth;
        map8 >> mappedheight;
        map8 >> bracket;
    }
    
    if(Level == 110){
        map108 >> bracket;
        map108 >> tileType;
        map108 >> mappedwidth;
        map108 >> mappedheight;
        map108 >> bracket;
    }
    
    if(Level == 8){
        map9 >> bracket;
        map9 >> tileType;
        map9 >> mappedwidth;
        map9 >> mappedheight;
        map9 >> bracket;
    }
    
    if(Level == 108){
        map109 >> bracket;
        map109 >> tileType;
        map109 >> mappedwidth;
        map109 >> mappedheight;
        map109 >> bracket;
    }
    
    if(Level == 11){
        map10 >> bracket;
        map10 >> tileType;
        map10 >> mappedwidth;
        map10 >> mappedheight;
        map10 >> bracket;
    }
    
    if(Level == 111){
        map110 >> bracket;
        map110 >> tileType;
        map110 >> mappedwidth;
        map110 >> mappedheight;
        map110 >> bracket;
    }
    if(Level == 12){
        map11 >> bracket;
        map11 >> tileType;
        map11 >> mappedwidth;
        map11 >> mappedheight;
        map11 >> bracket;
    }
    
    if(Level == 112){
        map111 >> bracket;
        map111 >> tileType;
        map111 >> mappedwidth;
        map111 >> mappedheight;
        map111 >> bracket;
    }
    
    if(Level == 13){
        map12 >> bracket;
        map12 >> tileType;
        map12 >> mappedwidth;
        map12 >> mappedheight;
        map12 >> bracket;
    }
    
    if(Level == 113){
        map112 >> bracket;
        map112 >> tileType;
        map112 >> mappedwidth;
        map112 >> mappedheight;
        map112 >> bracket;
    }
    
    if(Level == 14){
        map13 >> bracket;
        map13 >> tileType;
        map13 >> mappedwidth;
        map13 >> mappedheight;
        map13 >> bracket;
    }
    
    if(Level == 114){
        map113 >> bracket;
        map113 >> tileType;
        map113 >> mappedwidth;
        map113 >> mappedheight;
        map113 >> bracket;
    }
    
    if(Level == 15){
        map14 >> bracket;
        map14 >> tileType;
        map14 >> mappedwidth;
        map14 >> mappedheight;
        map14 >> bracket;
    }
    
    if(Level == 115){
        map114 >> bracket;
        map114 >> tileType;
        map114 >> mappedwidth;
        map114 >> mappedheight;
        map114 >> bracket;
    }
    
    if(Level == 16){
        map15 >> bracket;
        map15 >> tileType;
        map15 >> mappedwidth;
        map15 >> mappedheight;
        map15 >> bracket;
    }
    
    if(Level == 116){
        map115 >> bracket;
        map115 >> tileType;
        map115 >> mappedwidth;
        map115 >> mappedheight;
        map115 >> bracket;
    }
    
    if(Level == 50){
        map50 >> bracket;
        map50 >> tileType;
        map50 >> mappedwidth;
        map50 >> mappedheight;
        map50 >> bracket;
    }
    
    if(Level == 150){
        map150 >> bracket;
        map150 >> tileType;
        map150 >> mappedwidth;
        map150 >> mappedheight;
        map150 >> bracket;
    }
    
    if(Level == 51){
        map51 >> bracket;
        map51 >> tileType;
        map51 >> mappedwidth;
        map51 >> mappedheight;
        map51 >> bracket;
    }
    
    if(Level == 151){
        map151 >> bracket;
        map151 >> tileType;
        map151 >> mappedwidth;
        map151 >> mappedheight;
        map151 >> bracket;
    }
    

        //If the was a problem in reading the map
        if( map.fail() == true )
        {
            //Stop loading map
            map.close();
            return false;
        }

        //go through each map input and assign them to a tile, mtile or turret
        if( ( tileType >= 0 ) && ( tileType < 10 ) )
        {
            tiles[ t ] = new Tile( x, y, mappedwidth, mappedheight,tileType );
            mtiles[ t ] = new mTile( 0,0,0,0,0);
            turrets[ t ] = new turret(0,0,0,0,0);
        }
        
        else if( tileType == Push_Tile  || tileType == break_Tile)
        {
            tiles[ t ] = new Tile( 0,0,0,0,0);
            mtiles[ t ] = new mTile( x, y, mappedwidth, mappedheight, tileType);
            turrets[ t ] = new turret(0,0,0,0,0);
                                                    ///fix
        }
        
        else if( tileType == left_turret || tileType == right_turret)
        {
            tiles[ t ] = new Tile( 0,0,0,0,0);  
            mtiles[ t ] = new mTile( 0,0,0,0,0);
            turrets[ t ] = new turret( x, y, mappedwidth, mappedheight, tileType);                                       ///fix
        }
        
        //If we don't recognize the tile type
        else
        {
            //Stop loading map
            map.close();
            map101.close();
            map2.close();
            map102.close();
            map3.close();
            map103.close();
            map4.close();
            map104.close(); 
            map5.close();
            map105.close();
            return false;
        }

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }
    //If the map was loaded fine
    map.close();
    map101.close();
    map2.close();
    map102.close();
    map3.close();
    map103.close(); 
    map4.close();
    map104.close(); 
    map5.close();
    map105.close(); 
    return true;
}

void mapLoader :: reset(mTile *mtiles[], Tile *tiles[], turret *turrets[])
{
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if( mtiles[ t ]->get_type() == Push_Tile )
        {
            //reset all previously moved tiles to their original positions
           mtiles[ t ]->box.x = mtiles[ t ]->opX;
           mtiles[ t ]->box.y = mtiles[ t ]->opY;
        }
    }
        //change to the other time
    if(Level > 100)
    {
        Level -= 100;
    }
    else
    {
        Level += 100;
    }
    
    set_tiles(tiles, mtiles, turrets );
     //reset the tiles to their orignal positions again   
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if( mtiles[ t ]->get_type() == Push_Tile )
        {
           mtiles[ t ]->box.x = mtiles[ t ]->opX;
           mtiles[ t ]->box.y = mtiles[ t ]->opY;
        }
    }
    if(Level > 100)
    {
        Level -= 100;
    }
    else
    {
        Level += 100;
    }
    set_tiles(tiles, mtiles, turrets );
}

//based on the level, the game loads up the appropraite tiles, background and music
void mapLoader :: set_level()
{
    if(Level == 1 || Level == 101)
    {
        background = load_image( "present.png" );
        background2 = load_image( "present.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );

    }
    
    if(Level  == 2 || Level == 102)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1120;                             //the game also reshapes the maps of each level
        LEVEL_HEIGHT = 960;
        TOTAL_TILES = 168;
    }
    
    if(Level  == 3 || Level == 103)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
       // music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 4 || Level == 104)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
      //  music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 5 || Level == 105)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 800;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 130;
    }
    
    if(Level  == 6 || Level == 106)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 7 || Level == 107)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1360;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 221;
    }
    
    if(Level  == 9 || Level == 109)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 10|| Level == 110)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 8|| Level == 108)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 800;
        LEVEL_HEIGHT = 1600;
        TOTAL_TILES = 200;
    }
    
    if(Level  == 11 || Level == 111)
    {
        background = load_image( "lab3.png" );
        background2 = load_image( "lab.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 12 || Level == 112)
    {
        background = load_image( "lab.png" );
        background2 = load_image( "lab.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 13 || Level == 113)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1600;
        LEVEL_HEIGHT = 800;
        TOTAL_TILES = 200;
    }
    
    if(Level  == 14 || Level == 114)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1600;
        LEVEL_HEIGHT = 800;
        TOTAL_TILES = 200;
    }
    
    if(Level  == 15 || Level == 115)
    {
        background = load_image( "lab2.png" );
        background2 = load_image( "lab2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1600;
        LEVEL_HEIGHT = 800;
        TOTAL_TILES = 200;
    }
    
    if(Level  == 16|| Level == 116)
    {
        background = load_image( "goo2.png" );
        background2 = load_image( "goo2.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 800;
        LEVEL_HEIGHT = 1600;
        TOTAL_TILES = 200;
    }
    
    if(Level  == 50 || Level == 150)
    {
        background = load_image( "goo.png" );
        background2 = load_image( "little.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
    //    music = Mix_LoadMUS( "keogh.wav" );
        LEVEL_WIDTH = 1280;
        LEVEL_HEIGHT = 1040;
        TOTAL_TILES = 208;
    }
    
    if(Level  == 51 || Level == 151)
    {
        background = load_image( "capture.png" );
        background2 = load_image( "capture.png" );
        tileSheet = load_image( "tiles.png" );
        tileSheet2 = load_image( "tiles2.png" );
        music = Mix_LoadMUS( "hiddenmusic.wav" );
        Mix_PlayMusic(music, -1);
        LEVEL_WIDTH = 3280;
        LEVEL_HEIGHT = 480;
        TOTAL_TILES = 246;
    }
    
}
