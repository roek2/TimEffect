#include "SDL.h"
#ifndef MTILEHEADER
#define MTILEHEADER

//mtiles are tiles that can be pushed and pulled by the player
class mTile: public Tile
{
    //the attributes of the movable tile
    public:
    int xVel;
    int yVel;
    int opX;
    int opY;
    //used for the break_tiles
    bool trap;
    //mtile constructor
    mTile(int x, int y, int height, int width, int tileType);
    
    //if the player pushes against a mtile, then that mtile will move.
    void moveTile(Dot myDot, Tile *tiles[], mTile *mtiles[], turret *turrets[]);
    //if an mtile is pushed against a wall then that mtile will not move
    bool wall2wall(Tile *tiles[], mTile *mtiles[], turret *turrets[]);
    //detects if an mtile collides with a tile from the left
    bool wall2left(Tile *tiles[], mTile *mtiles[], turret *turrets[]);
    //detects if an mtile collides with a tile from the left
    bool wall2right(Tile *tiles[], mTile *mtiles[], turret *turrets[]);
    //checks if the mtile is on the ground
    bool wall2ground(Tile *tiles[], mTile *mtiles[] );
};

#endif
