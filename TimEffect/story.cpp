#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;
#include "baseHeader.h"
#include "tileHeader.h"
#include "turretHeader.h"
#include "setupHeader.h"
#include "mapLoaderHeader.h"
#include "dotHeader.h"
#include "mtileHeader.h"
#include "storyHeader.h"

extern int tt;
extern SDL_Surface *text;
extern SDL_Surface *text2;
extern SDL_Surface *text3;
extern SDL_Surface *screen;
extern SDL_Surface *background;
extern TTF_Font *font;
extern SDL_Color textColor;
extern int Level;
extern bool pause;
extern int alpha2;

//events are loaded
story :: story()
{
    event1 = true;
    event2 = true;
}

int story :: cutscene(string Filename, int count, Dot myDot)
{
        //when a particular event is triggered
        if((director(myDot) == 1 && event1) || (director(myDot) == 5 && event2) )
        {
            //the player is paused
            pause = true;
            if(count > 2)
            {
                //the text is lined up properly
                lineup(Filename);
                count = 0;
                tt++;
            }

            //the text is applied
            apply_surface(100 ,120 , text, screen);
            apply_surface(100 ,150 , text2, screen);
            apply_surface(100 ,180 , text3, screen);
            count++;
        }
        //this another type of event where the player is not paused
        if(director(myDot) == 2|| director(myDot) == 3 || director(myDot) == 4 || director(myDot) > 5)
        {
            if(count > 2)
            {
                lineup(Filename);
                count = 0;
            }
            apply_surface(100 ,120 , text, screen);
            apply_surface(100 ,150 , text2, screen);
            apply_surface(100 ,180 , text3, screen);
            count++;
        }
        return count;
}

void story :: lineup(string Filename)
{

        
    if(tt < 120)
    {
        string temp = Filename;
        string temp2 = Filename;
        string temp3 = Filename;
        //if the text is longer than 40 chars the end of the text is shaved off for the first line
        if(temp2.size() > 40)
        {
            temp.erase(40, temp.size());
        }
        //if the text is longer than 80 chars the end of the text is shaved off for the second line
        if(temp2.size() > 80)
        {
            temp2.erase(80, temp2.size());
        }
        //if the text is longer than 120 chars the end of the text is shaved off for the third line
        if(temp3.size() > 120)
        {
            temp3.erase(120, temp3.size());
        }
        //on the first line the text is taken from the beginning
        text = TTF_RenderText_Solid(font, &temp[0], textColor);
        if(Filename.size() > 40)
            text2 = TTF_RenderText_Solid(font, &temp2[40], textColor);          //on the second the text is taken from the 40th character
        if(Filename.size() > 80)
            text3 = TTF_RenderText_Solid(font, &temp3[80], textColor);          //on the third the text is taken from the 80th character
    }
  //  else
  //  {
  //      text = TTF_RenderText_Solid(font, &Filename[120], textColor);
  //      text2 = TTF_RenderText_Solid(font, &Filename[160], textColor);
  //      text3 = TTF_RenderText_Solid(font, &Filename[200], textColor);
  //  }
}

//the text is chasen based on what event occurs
string story :: textConverter(Dot myDot)
{
    string FileMeasure;
    if(director(myDot) == 1)
    {
        FileMeasure="Warning Escaped prisoner on the loose!! He is considered very dangerous         Initialising turrets!!";
    }
    if(director(myDot) == 2)
    {
        FileMeasure= "Press <- to move left                   Press -> to move right";
    }
    
    if(director(myDot) == 3)
    {
        FileMeasure= "Press Space to jump                     Hold space to jump higher";
    }
    
    if(director(myDot) == 4)
    {
        FileMeasure= "Press X to push and pull parts of the   enviroment";
    }

    if(director(myDot) == 5)
    {
        FileMeasure= "You have acquired the timEffect press T to switch between times";
    }
    
    if(director(myDot) == 6)
    {
        FileMeasure= "Gone for bearing point/deloitte lunch   with karl~dawg and fatboy, back later   ~Alan";
    }
    
    if(director(myDot) == 7)
    {
        FileMeasure= "PLAYING  LOL  DO NOT DISTURB            wait got to study.....FUUUUUUUUUUUUUUUCK~Jinn";
    }
    
    if(director(myDot) == 8)
    {
        FileMeasure= "Be in around 12, we'll get some lunch,  pop across to spar and then get cracking~Dave (FatBoy)";
    }
    
    if(director(myDot) == 9)
    {
        FileMeasure= "Got to go gymnastics, im leaving my     computer on but dont fucking frape me    ~Jack";
    }
    
    if(director(myDot) == 10)
    {
        FileMeasure= "Look it scan, im out getting more tweed The brazillian beures love the tweed    ~Big Dave  ";
    }
    
    if(director(myDot) == 11)
    {
        FileMeasure= "TARANTINO MARATHON!!!                   Pick up a few Big Kahuna burgers and    Come on in    ~Donn";
    }
    
    if(director(myDot) == 12)
    {
        FileMeasure= "BILL                                    IS                                      GAY";
    }
    
    if(director(myDot) == 13)
    {
        FileMeasure= "MISSING : Robert Lis                     Last seen incredibly drunk and fully    bearded";
    }
    
    if(director(myDot) == 14)
    {
        FileMeasure= "Gone to Tarantino maranthon ~~~~~~~>    Couldn't resist                                       ~Feargal";
    }
    
    if(director(myDot) == 15)
    {
        FileMeasure= "Kicking people in the head for medals   be back in time for man food            ~Keogh";
    }
    
    if(director(myDot) == 16)
    {
        FileMeasure= "Gone out for the shift, staying in max'sCome back in the morning, bring BK      ~Krys";
    }
    
    return FileMeasure;
}

//a list of wjhat can trigger event
int story :: director(Dot myDot)
{
    //they are based around a level and a position the player passes
    if(Level == 150 && myDot.box.x > 700 && myDot.box.y <  300 && myDot.box.x < 800 && event1)
    {
        return 1;
    }
    
    if(Level == 1 && myDot.box.x > 80 && myDot.box.x < 500 )
    {
        return 2;
    }
    
    if(Level == 1 && myDot.box.x > 750 && myDot.box.x < 1700)
    {
        return 3;
    }
    
    if(Level == 1 && myDot.box.x > 2000 && myDot.box.x < 2400)
    {
        return 4;
    }
    
    if(Level == 2 && myDot.box.x > 190 && myDot.box.x < 210 && myDot.box.y > 800 && event2)
    {
        return 5;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 3050 && myDot.box.x < 3150)
    {
        return 6;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 2770 && myDot.box.x < 2870 )
    {
        return 7;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 2490 && myDot.box.x < 2590 )
    {
        return 8;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 2210 && myDot.box.x < 2310 )
    {
        return 9;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 1930 && myDot.box.x < 2030 )
    {
        return 10;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 1650 && myDot.box.x < 1750 )
    {
        return 11;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 1380 && myDot.box.x < 1490 )
    {
        return 12;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 1110 && myDot.box.x < 1220 )
    {
        return 13;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 840 && myDot.box.x < 940 )
    {
        return 14;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 570 && myDot.box.x < 670 )
    {
        return 15;
    }
    
    if((Level == 51 || Level == 151) && myDot.box.x > 300 && myDot.box.x < 400 )
    {
        return 16;
    }
    
    return 0;
}
//cleaning up after the event
void story :: end_story(Dot myDot , mapLoader Fman , Tile* tiles[], mTile* mtiles[], turret *turrets[])
{
    if(director(myDot) == 1 && tt > 60)
    {
        //event1 becoming false means that the evnt cant occur again
        event1 = false;
        tt = 0;
        Level = 107;
        Fman.set_level();
        Fman.set_tiles( tiles, mtiles, turrets);
        //the game is unpaused
        if(pause)
        {
            pause = false;
        }
    }
    
    if(director(myDot) == 2)
    {
        if(pause)
        {
            pause = false;
        }
    }
    
    if(director(myDot) == 3)
    {


        if(pause)
        {
            pause = false;
        }
    }
    
    if(director(myDot) == 5 && tt > 30)
    {
        event2 = false;
        tt = 0;
        if(pause)
        {
            pause = false;
        }
    }
    
    
}
