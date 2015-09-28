#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include<iostream>
#include<string>
using namespace std;
#ifndef STORYHEADER
#define STORYHEADER
class Dot;
class Tile;
class mTile;
class mapLoader;
class turret;

class story : public base
{
    private:
    //these are for events that should only happen once
    bool event1;
    bool event2;
    public:
    story();
    //for loading text for events 
    string textConverter(Dot myDot);
    //determines when an event happens
    int director(Dot myDot);
    //acts out the events
    int cutscene(string Filename, int count, Dot myDot);
    //alligns text appropriately
    void lineup(string Filename);
    //ends event
    void end_story(Dot myDot, mapLoader Fman, Tile* tiles[], mTile* mtiles[], turret *turrets[]);
};

#endif
