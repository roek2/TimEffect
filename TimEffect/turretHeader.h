#include "SDL.h"
#ifndef TURRETHEADER
#define TURRETHEADER

class mTile;
class Dot;

class turret : public Tile
{
    public:
    //a point that shows what the turret sees
    point test;
    //turret attributes loaded
    turret(int x, int y, int height, int width, int tileType);
    //checks if the turrets sight has collided with a wall
    bool point2wall( Tile *tiles[], mTile *mtiles[]);
    //detects the player
    bool survey( Tile *tiles[], mTile *mtiles[], Dot myDot);
    //counts up until kiiling the player
    int shoot( int count);
};

#endif
