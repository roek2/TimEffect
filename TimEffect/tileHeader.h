#ifndef TILEHEADER
#define TILEHEADER

class Tile : public base
{
    private:
    //The tile type
    int type;

    public:
        
    SDL_Rect box;
    //Initializes the variables
    Tile( int x, int y, int height, int width, int tileType );

    //Shows the tile
    void show();

    //Get the tile type
    int get_type();

    //Get the collision box
    SDL_Rect get_box();
};

#endif 
