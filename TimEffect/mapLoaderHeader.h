#include "SDL.h"
#ifndef MAPLOADERHEADER
#define MAPLOADERHEADER

class Tile;
class mTile;
class turret;

class mapLoader : public Setup
{
    public:
        //clip the art for the tiles
        void clip_tiles(SDL_Rect box);
        //set the tiles in their positions
        bool set_tiles( Tile *tiles[], mTile *mtiles[], turret *turrets[] );
        //reset the tiles to their original position
        void reset(mTile *mtiles[], Tile *tiles[], turret *turrets[]);
        //load the map art, music and reshape the map to its appropriate shap
        void set_level();
};

#endif
